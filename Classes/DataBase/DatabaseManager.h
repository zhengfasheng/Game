/******************************************************************************
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  Author:Zheng Fasheng
 *
 *  Email:zheng_fasheng@outlook.com
 *
 *  Date:2016/7/29 23:39
 *
 *  Summary:数据库详细实现
 *  
 ******************************************************************************/
#pragma once
#include "common.h"
#include "DataBaseDefine.h"
#include "TableDefine.h"
#include "Table.h"
#include "TableStructure.h"


/** @brief	Manager for databases. This class cannot be inherited. */
class DatabaseManager final 
{
public:
	~DatabaseManager();
	IMPLEMENT_SINGLETON(DatabaseManager);

	virtual void init() ;
	virtual void release() ;

	/**
	 * @brief	Gets a table.
	 *
	 * @param	tID	The identifier.
	 *
	 * @return	null if it fails, else the table.
	 */

	DBC::CTable* getTable(DBC::UINT tableID);

	/**
	 * @brief	得到指定表中第一列 等于 nID 的表项数据 
	 *
	 * @param	tableID	表id
	 * @param	nID	   	要查找的值，表第一列的值
	 *
	 * @return	null if it fails, else the table data.
	 */
	template<class T> const T* getTableData( DBC::UINT tableID , DBC::INT nID )
	{
		auto pTable = getTable(tableID);
		if ( pTable )
		{
			return (const T*)pTable->searchWithValue(nID);
		}
		else
		{
			return nullptr;
		}
	}

	/**
	 * @brief	迭代遍历，.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param	tbID		Identifier for the terabytes.
	 * @param	callback	The callback.
	 */

	template<class T> void foreach( DBC::UINT tbID , std::function<void(const T* pOutData)> callback)
	{
		auto pTable = getTable(tbID);
		if ( !pTable ) return ;
		for ( auto it = pTable->cbegin() ; it != pTable->cend() ; ++it )
		{
			if ( callback )
			{
				callback((const T*)it->second);
			}
		}
	}

private:

	/** @brief	Opens this database. */
	void open();

	/** @brief	Closes this database. */
	void close();
	
private:

	DatabaseManager();

	std::map<DBC::UINT, DBC::CTable*> m_tableMap;
	
};
