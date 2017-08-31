#include "Language.h"
#include "commontools.h"
#include "Resource.h"

Language::Language()
	:m_pLanguage(nullptr)
{

}

Language::~Language()
{
	release();
}

void Language::init()
{
	auto languageType = Application::getInstance()->getCurrentLanguage();
	switch (languageType)
	{
	/*case cocos2d::LanguageType::ENGLISH:
		m_pLanguage = __Dictionary::createWithContentsOfFile("Language/EN_Languge.plist");
		break;*/
	case cocos2d::LanguageType::CHINESE:
		m_pLanguage = __Dictionary::createWithContentsOfFile("Language/ZN_Languge.plist");
		break;
		//以下语言暂不考虑支持
	/*case cocos2d::LanguageType::FRENCH:
		break;
	case cocos2d::LanguageType::ITALIAN:
		break;
	case cocos2d::LanguageType::GERMAN:
		break;
	case cocos2d::LanguageType::SPANISH:
		break;
	case cocos2d::LanguageType::DUTCH:
		break;
	case cocos2d::LanguageType::RUSSIAN:
		break;
	case cocos2d::LanguageType::KOREAN:
		break;
	case cocos2d::LanguageType::JAPANESE:
		break;
	case cocos2d::LanguageType::HUNGARIAN:
		break;
	case cocos2d::LanguageType::PORTUGUESE:
		break;
	case cocos2d::LanguageType::ARABIC:
		break;
	case cocos2d::LanguageType::NORWEGIAN:
		break;
	case cocos2d::LanguageType::POLISH:
		break;
	case cocos2d::LanguageType::TURKISH:
		break;
	case cocos2d::LanguageType::UKRAINIAN:
		break;
	case cocos2d::LanguageType::ROMANIAN:
		break;
	case cocos2d::LanguageType::BULGARIAN:
		break;*/
	default:
		m_pLanguage = __Dictionary::createWithContentsOfFile("Language/ZN_Languge.plist");
		break;
	}

	if ( m_pLanguage )
	{
		m_pLanguage->retain();
	}
}

void Language::release()
{
	CC_SAFE_RELEASE_NULL(m_pLanguage);
}

std::string Language::getString(const string& key , string defaultString /* = "" */ )
{
	vector<string> vRet;
	if ( checkKey(key,vRet) )
	{
		//找出对应的字符串
		return findString(vRet, defaultString);
	}
	return defaultString;
}

std::string Language::getStringWithParam(const string& key, const vector<GValue>& params, string defaultString /*= ""*/)
{
	vector<string> vRet;
	if (checkKey(key, vRet))
	{
		auto outString = findString(vRet, defaultString);
		if (outString.empty())
		{
			return defaultString;
		}
		else
		{
			return formatString(outString, params);
		}
	}
	return defaultString;
}

std::string Language::getStringWithParam(
	const string& key, 
	const GValue& param1 /*= GValue::Null*/, 
	const GValue& param2 /*= GValue::Null*/, 
	const GValue& param3 /*= GValue::Null*/, 
	const GValue& param4 /*= GValue::Null*/, 
	const GValue& param5 /*= GValue::Null*/, 
	const GValue& param6 /*= GValue::Null*/, 
	const GValue& param7 /*= GValue::Null*/, 
	const GValue& param8 /*= GValue::Null*/, 
	const GValue& param9 /*= GValue::Null*/, 
	const GValue& param10 /*= GValue::Null*/, 
	string defaultString /*= ""*/)
{
	return getStringWithParam(key, { param1, param2, param3, param4, param5, param6, param7, param8, param9, param10 }, defaultString);
}


std::string Language::findString(const vector<string>& keys , string defaultString )
{
	auto pFind = m_pLanguage;
	size_t i = 0;
	string outString = defaultString;
	Ref* pPrev = m_pLanguage;
	while (true)
	{
		pPrev = pFind->objectForKey(keys[i]);
		pFind = dynamic_cast<__Dictionary*>(pPrev);
		if ( !pFind )
		{
			//尝试转换成String
			auto pOutString = dynamic_cast<__String*>(pPrev);
			if ( pOutString )
			{
				outString = pOutString->getCString();
			}
			break;
		}
		i++;
	}
	return outString;
}

vector<string> Language::getVector(const string& key)
{
	vector<string> vRet;
	if ( checkKey(key,vRet) )
	{
		return findVector(vRet);
	}
	return vRet;
}

vector<string> Language::findVector(const vector<string>& keys)
{
	auto pFind = m_pLanguage;
	size_t i = 0;
	Ref* pPrev = m_pLanguage;
	vector<string> outVec;
	while (true)
	{
		pPrev = pFind->objectForKey(keys[i]);
		pFind = dynamic_cast<__Dictionary*>(pPrev);
		if (!pFind)
		{
			//尝试转换成String
			auto pOutVec = dynamic_cast<__Array*>(pPrev);
			if (pOutVec)
			{
				for (ssize_t i = 0; i < pOutVec->count(); i++)
				{
					auto pString = dynamic_cast<__String*>(pOutVec->getObjectAtIndex(i));
					if ( pString )
					{
						outVec.push_back(pString->getCString());
					}
				}
			}
			break;
		}
		i++;
	}
	return outVec;
}

bool Language::checkKey(const string& key , vector<string>& keys )
{
	if (!m_pLanguage)
	{
		CCLOG("language not init");
		return false;
	}
	//检测key的有效性
	auto pos = key.find(".");
	if (pos == string::npos)
	{
		CCLOG("key invaild , key : %s", key.data());
		return false;
	}

	//切分
	split(key, ".", keys);
	//强制必须是xx.xx形式
	if (keys.size() < 2)
	{
		CCLOG("key invaild , you key must such as xx.xx key : %s", key.data());
		keys.clear();
		return false;
	}

	return true;
}

string Language::formatString(string szFormat, const vector<GValue>& params)
{
	//xx%sxx%dxx%fxx
	if (params.size() == 0)
	{
		return szFormat;
	}

	vector<string> vRet;
	splitWithParam(szFormat, vRet, params);
	if (vRet.empty())
	{
		return szFormat;
	}
	szFormat = "";
	for (size_t i = 0; i < vRet.size(); i++)
	{
		szFormat += vRet[i];
	}

	return szFormat;
}

std::string Language::formatString(
	string szFormat,
	const GValue& param1 /*= GValue::Null*/,
	const GValue& param2 /*= GValue::Null*/,
	const GValue& param3 /*= GValue::Null*/,
	const GValue& param4 /*= GValue::Null*/,
	const GValue& param5 /*= GValue::Null*/,
	const GValue& param6 /*= GValue::Null*/,
	const GValue& param7 /*= GValue::Null*/,
	const GValue& param8 /*= GValue::Null*/,
	const GValue& param9 /*= GValue::Null*/,
	const GValue& param10 /*= GValue::Null*/)
{
	return formatString(szFormat, { param1, param2, param3, param4, param5, param6, param7, param8, param9, param10 });
}

void Language::createSplitTokens(vector<GValue>& values, vector<string>& tokens)
{
	tokens.clear();
	for (auto it = values.begin(); it != values.end(); it++)
	{
		if (it->isNull())
		{
			break;
		}
		tokens.push_back("{%any}");
	}
}


void Language::splitWithParam(string src, vector<string>& vect, vector<GValue> values)
{
	vect.clear();
	if (values.size() == 0 )
	{
		return;
	}
	auto it = values.begin();
	vector<string> tokens;
	createSplitTokens(values, tokens);
	if ( tokens.empty() )
	{
		return;
	}
	vect.clear();
	size_t nend = 0;
	size_t nbegin = 0;
	string strTemp = "";
	size_t nCurToken = 0;
	const char* token = nullptr;
	while (nend != string::npos && nend != src.size() )
	{
		if ( nCurToken < tokens.size() )
		{
			token = tokens[nCurToken].data();
			nend = src.find(token, nbegin);
		}
		else
		{
			nend = src.size();
		}
		if (nend == string::npos)
		{
			strTemp = src.substr(nbegin, src.length() - nbegin);
			if (!strTemp.empty())
			{
				vect.push_back(strTemp);
			}
		}
		else
		{
			strTemp = src.substr(nbegin, nend - nbegin);
			if (!strTemp.empty())
			{
				vect.push_back(strTemp);
			}
			if (it != values.end() && !it->isNull() )
			{
				vect.push_back(it->asString());
				it++;
			}
		}
		nCurToken++;
		nbegin = nend + strlen(token);
	}
}

std::string Language::getLocalFont()
{
	return "";
}

std::string Language::getBitmapFont()
{
	return s_font;
}

std::string Language::getArial14Font()
{
	return s_arial14_fnt;
}



