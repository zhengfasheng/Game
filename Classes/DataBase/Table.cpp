#include "Table.h"
#include "CCFileUtils.h"
#include "cocos2d.h"
#include "commontools.h"

using namespace cocos2d;

DBC_BEGIN
CTable::CTable(TableConfig config)
: m_config(config)
, m_nRow(0)
, m_nCol(0)
{

}

CTable::~CTable()
{
	close();
}

void CTable::close()
{
	for (UINT i = 0; i < m_vDataBuf.size();)
	{
		for (UINT j = 0; j < m_tpye.size(); j++)
		{
			if (m_tpye[j] == DataType::PINT64)
			{
				delete m_vDataBuf[i].pValue64;
			}
			else if ( m_tpye[j] == DataType::STRING )
			{
				delete[] m_vDataBuf[i].pStringValue;
			}
			i++;
		}
	}
	m_vDataBuf.clear();
}

BOOL CTable::open()
{
	//读入内存
	if ( !m_config.szName || !m_config.szPath )
	{
		return false;
	}
	STRING strPath = m_config.szPath;
	strPath += "/";
	strPath += m_config.szName;
	auto szContent = FileUtils::getInstance()->getStringFromFile(strPath);
	auto pRet = readText(szContent);
	return pRet;
}

BOOL CTable::readText(STRING& szContent )
{
	vector<STRING> contentVec;
	UINT nIndex = 0;
	splitStringToVector(szContent, contentVec);
	if ( contentVec.empty() )
	{
		return false;
	}
	//取表头
	//分割出来的都带有\r,要去掉这个标识
	vector<STRING> vRet;
	split(contentVec[nIndex++], "\t", vRet);
	if (vRet.empty())
	{
		return false;
	}

	//生成字段数据
	vector<DataType> vType;
	vType.resize(vRet.size());

	for (UINT i = 0; i < vRet.size(); i++)
	{
		if (vRet[i].find("INT64") != STRING::npos)
		{
			vType[i] = DataType::PINT64;
		}
		else if ( vRet[i].find("INT") != STRING::npos )
		{
			vType[i] = DataType::INT;
		}
		else if (vRet[i].find("FLOAT") != STRING::npos )
		{
			vType[i] = DataType::FLOAT;
		}
		else if (vRet[i].find("STRING") != STRING::npos )
		{
			vType[i] = DataType::STRING;
		}
		else
		{
			return false;
		}
	}

	//--------------------------------------------------------------
	//初始化
	UINT nRecordsNum = 0;
	UINT nFieldsNum = vType.size();

	//临时字符串区
	vector<pair<string, int>> vStringBuf;

	//--------------------------------------------------------------
	//开始读取

	UINT nStringBufSize = 0;
	for (; nIndex < contentVec.size(); nIndex++)
	{
		//读取一行
		auto szLine = contentVec[nIndex];

		//是否是注释行
		if (szLine[0] == '#') continue;

		//分解
		split(szLine,"\t",vRet);

		//列数不对
		if (vRet.empty()) continue;
		if (vRet.size() != nFieldsNum)
		{
			//补上空格
			if (vRet.size() < nFieldsNum)
			{
				auto nSubNum = nFieldsNum - vRet.size();
				for (UINT i = 0; i < nSubNum; i++)
				{
					vRet.push_back("");
				}
			}
		}

		//第一列不能为空
		if (vRet[0].empty()) continue;

		for (register UINT i = 0; i < nFieldsNum; i++)
		{
			Data newField;
			switch (vType[i])
			{
			case DataType::INT:
			{
#ifdef _IOS
#if defined(_ARM_ARCH_7)
				newField.nValue = atoi(vRet[i].c_str());
#else
				newField.nValue = atoll(vRet[i].c_str());
#endif

#else
				newField.nValue = atoi(vRet[i].c_str());
#endif
				m_vDataBuf.push_back(newField);
				break;
			}
			case DataType::PINT64:
			{
				PINT64 pValue = new INT64;
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
				*pValue = _atoi64(vRet[i].c_str());
#else
				*pValue = atoll(vRet[i].c_str());
#endif;
				newField.pValue64 = pValue;
				m_vDataBuf.push_back(newField);
				break;
			}

			case DataType::FLOAT:
			{
				newField.fValue = (FLOAT)atof(vRet[i].c_str());
				m_vDataBuf.push_back(newField);
				break;
			}
			case DataType::STRING:
				if (vRet[i].empty())
				{
					newField.pStringValue = new char[1];
					newField.pStringValue[0] = '\0';
				}
				else
				{
					UINT nLen = strlen(vRet[i].c_str()) + 1;
					newField.pStringValue = new char[nLen];
					memset(newField.pStringValue,0,nLen);
					memcpy(newField.pStringValue,vRet[i].data(),vRet[i].size());
				}

				m_vDataBuf.push_back(newField);
				break;
			}
		}

		nRecordsNum++;
	}


	//--------------------------------------------------------
	//生成正式数据库
	m_nRow = nRecordsNum;
	m_nCol = nFieldsNum;
	// Create Field Types
	m_tpye = vType;
	
	//生成索引列
	createIndex();

	return true;
}

void CTable::createIndex()
{
	m_table.clear();

	for (UINT i = 0; i < m_nRow; i++)
	{
		Data* p = &(m_vDataBuf[i*m_nCol]);

		auto itFind = m_table.find(p->nValue);
		if (itFind != m_table.end())
		{
			CCLOG("ErrorLog****: the txt = %s is repeat data the id = %d  please check !", m_config.szName, p->nValue);
			continue;
		}
		m_table.insert(std::make_pair(p->nValue, p));
	}
}

void CTable::splitStringToVector(STRING& szContent,vector<STRING>& outVec)
{
	split(szContent, "\r\n", outVec);
}

const Data* CTable::searchWithValue(INT nValue)
{
	auto itFind = m_table.find(nValue);
	if (itFind == m_table.end())
		return nullptr;

	return itFind->second;
}

const Data* CTable::searchWithRow(UINT nRow)
{
	if (nRow < 0|| nRow >= m_table.size() )
		return nullptr;
	auto nCurRow = 0;
	for (auto it = m_table.begin(); it != m_table.end(); it++ , nCurRow++)
	{
		if ( nRow == nCurRow )
		{
			return it->second;
		}
	}
	return nullptr;
}

TableMap::const_iterator CTable::cbegin()
{
	return m_table.cbegin();
}

TableMap::const_iterator CTable::cend()
{
	return m_table.cend();
}


DBC_END