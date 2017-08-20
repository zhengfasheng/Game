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
 *  Date:2016/7/29 23:18
 *
 *  Summary:数据库文件格式定义
 *  
 ******************************************************************************/
#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#define DBC_BEGIN                     namespace DBC {
#define DBC_END                       }
#define USING_DBC                     using namespace DBC

DBC_BEGIN
using namespace std;

//数据库数据类型定义
#ifdef _IOS
#if defined(_ARM_ARCH_7)
typedef int	INT;
typedef float FLOAT;
#else
typedef long long	INT;
typedef double FLOAT;
#endif

#else
typedef int	INT;
typedef float FLOAT;
#endif

typedef char CHAR, *PCHAR;
typedef long long INT64, *PINT64;
typedef bool BOOL;
typedef unsigned int UINT;
typedef string STRING;

/** @brief	数据类型 */
enum class DataType
{
	INT,   //整形
	FLOAT, //浮点
	STRING,//字符串
	PINT64,//大整形,以指针形式存储
};

/** @brief	数据 */
union Data
{
	PCHAR   pStringValue;
	INT     nValue;
	FLOAT   fValue;
	PINT64  pValue64;

	Data(){ memset(this, 0, sizeof(Data)); }
	~Data(){}
	Data(INT value){ nValue = value; }
	Data(FLOAT value){ fValue = value; }
	Data(PINT64 value){ pValue64 = value; }
	Data(PCHAR value){ pStringValue = value; }
};

/** @brief	数据表配置 */
struct TableConfig
{
	TableConfig(UINT id, PCHAR name = nullptr , PCHAR path = nullptr ) : uID(id), szName(name), szPath(path){}
	/** @brief	表id. */
	UINT  uID;
	/** @brief	表名 */
	PCHAR szName;
	/** @brief	表路径 */
	PCHAR szPath;
};

//数据表
typedef std::unordered_map<INT, const Data*> TableMap;

//数据库空类型
const static std::string Null = "NULL";

DBC_END