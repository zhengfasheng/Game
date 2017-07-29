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
 *  Date:2016/7/30 18:30
 *
 *  Summary:万能数据类型
 *  
 ******************************************************************************/
#pragma once
#include <string>
using namespace std;

class GValue final
{
public:

	static const GValue Null;

	GValue();

	enum class Type
	{
		NONE,//无类型
		INT, //整形
		STRING,//字符串
		FLOAT,//float
		DOUBLE,
		PVOID,//void*万能形
		BOOL,
		INT64,//long long
	};

	GValue(int nValue);

	GValue(float fValue);

	GValue(double fValue);

	GValue(bool bValue);

	GValue(void* pVoidValue);

	GValue(const string& szValue);

	GValue(const char* szValue);

	GValue(long long lValue);

	GValue(const GValue& value);

	GValue(GValue&& value);

	~GValue();

	GValue& operator=(int nValue);

	GValue& operator=(float fValue);

	GValue& operator=(double dValue);

	GValue& operator=(bool bValue);

	GValue& operator=(void* pVoidValue);

	GValue& operator=(const string& szValue);

	GValue& operator=(const char* szValue);

	GValue& operator=(long long lValue);

	GValue& operator=(const GValue& other);

	GValue& operator=(GValue&& other);

	bool operator==(const GValue& other);

	bool operator==(const GValue& other) const;

	bool operator!=(const GValue& other);

	bool operator!=(const GValue& other) const;

	Type getType() const { return m_type; }

	const int asInt() const;

	const long long asInt64() const;

	const float asFloat() const;

	const double asDouble() const;

	const bool asBool() const ;

	const string asString() const;

	const char* asCString() const;

	const void* asPointer() const ;

	/**
	 * @brief	根据当前类型返回一个格式字符串，如float %s
	 *
	 * @return	格式字符串
	 */

	string getFormatString() const;

	/**
	 * @brief	设置格式串，支持连调
	 *
	 * @param	szFormat	Describes the format to use.
	 *
	 * @return	A reference to a GValue.
	 */

	GValue& setFormatString(const string& szFormat);

	const bool isNull() const { return m_type == Type::NONE; }

private:

	/**
	 * @brief	检查格式串是否有效
	 *
	 * @param	szFormat	格式串
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	bool checkFormat(const string& szFormat);

	void clear();

	void reset(Type type);

	union Data
	{
		int        nValue;
		float      fValue;
		double     dValue;
		bool       bValue;
		void*      pVoid;
		long long  lValue;
		string*    pStringValue;
	};

	Data m_data;

	Type m_type;


	/** @brief 为不扩大类大小，不要用string，  
	/** 这个变量只是在浮点时重新指定默认的格式串，浮点默认%f,  
	/** 当需要重新指定精度时才会分配内存 */
	string* m_pFormat;
};

