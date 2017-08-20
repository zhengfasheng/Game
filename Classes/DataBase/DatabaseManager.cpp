#include "DatabaseManager.h"
#include "DataBaseDefine.h"
#include "TableDefine.h"
#include "Table.h"
#include "cocos2d.h"

USING_NS_CC;

DatabaseManager::DatabaseManager()
{

}

DatabaseManager::~DatabaseManager()
{

}

void DatabaseManager::open()
{
	USING_DBC;
	int nTotalDataFile = sizeof(g_tableConfig) / sizeof(TableConfig);
	for (int i = 0; i < nTotalDataFile; i++ )
	{
		TableConfig config = g_tableConfig[i];
		auto pTable = new CTable(config);
		if ( !pTable ) continue;
		if ( !pTable->open() )
		{
			CCLOG("open %s error!", config.szName);
		}
		if ( m_tableMap.find(config.uID) != m_tableMap.end() )
		{
			CCLOG("DB id Repeat define %s", config.szName);
		}
		m_tableMap[config.uID] = pTable;
	}
}

void DatabaseManager::close()
{
	for (auto it = m_tableMap.begin(); it != m_tableMap.end(); ++it )
	{
		auto& pDataFile = it->second;
		if ( pDataFile )
		{
			delete pDataFile;
			pDataFile = nullptr;
		}
	}
	m_tableMap.clear();
}

DBC::CTable* DatabaseManager::getTable(DBC::UINT tableID)
{
	auto it = m_tableMap.find(tableID);
	if ( it != m_tableMap.end() )
	{
		return it->second;
	}
	return nullptr;
}

void DatabaseManager::init()
{
	open();
}

void DatabaseManager::release()
{
	close();
}

