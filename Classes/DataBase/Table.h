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
 *  Date:2016/7/24 21:57
 *
 *  Summary:Declares the file class
 *  
 ******************************************************************************/
#pragma once
#include "DataBaseDefine.h"

DBC_BEGIN
/** @brief	数据表，建议不要在外面修改表数据 */
class CTable
{
public:
	CTable(TableConfig);
	virtual ~CTable();

	/**
	* @brief	得到数据库行数.
	*
	* @return	行数
	*/

	virtual const UINT getRow() const { return m_nRow; };

	/**
	* @brief	得到数据库列数
	*
	* @return	列数
	*/

	virtual const UINT getColumn() const { return m_nCol;};

	/**
	* @brief	Searches for the first with value.
	*
	* @param	nValue	The value.
	*
	* @return	null if it fails, else the found with value.
	*/

	virtual const Data* searchWithValue(INT nValue);
	template<class T> const T* searchWithValue(UINT nRow)
	{
		auto pOut = searchWithValue(nRow);
		if ( pOut )
		{
			return (const T*)pOut;
		}
		else
		{
			return nullptr;
		}
	}
	/**
	* @brief	按行查找，这个效率非常低
	*
	* @param	nRow	The row.
	*
	* @return	null if it fails, else the found with row.
	*/

	virtual const Data* searchWithRow(UINT nRow);

	/**
	 * @brief	得到表头
	 *
	 * @return	表开始
	 */

	TableMap::const_iterator cbegin();

	/**
	 * @brief	得到表尾
	 *
	 * @return	表结束
	 */

	TableMap::const_iterator cend();

	/** @brief	Opens this table. */
	virtual BOOL open();

private:

	/** @brief	Closes this table. */
	virtual void close();

	/**
	 * @brief	读取文件格式内容
	 *
	 * @param [in,out]	szContent	文件内容
	 * @param	filePath		 	文件路径 
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	BOOL readText(STRING& szContent );
	//读取内存中一行数据(按照换行符)
	void splitStringToVector(STRING& szContent, vector<STRING>& outVec);

	//生成索引 
	void createIndex( );

private:
	//数据区
	std::vector<Data>		m_vDataBuf;

	//行数
	UINT m_nRow;

	//列数
	UINT m_nCol;

	//文件格式
	vector< DataType > m_tpye;

	//索引表
	TableMap m_table;

	//配置信息
	TableConfig m_config;

};
DBC_END