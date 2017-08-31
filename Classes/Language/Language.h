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
 *  Date:2016/7/30 15:35
 *
 *  Summary:语言包管理器
 *  
 ******************************************************************************/
#pragma once

#include "common.h"
#include "cocos2d.h"
#include "GValue.h"

USING_NS_CC;
class Language final 
{
public:
	~Language();
	IMPLEMENT_SINGLETON(Language);

	virtual void init() ;

	virtual void release();

	/**
	 * @brief	通过key得到语言包的配置
	 *
	 * @param	key			 	The key.
	 * @param	defaultString	(Optional) 如没找到，返回的默认值
	 *
	 * @return	配置信息
	 */

	string getString(const string& key , string defaultString = "" );

	/**
	* @brief	当有需要在描述中写入参数时，会根据传入的参数拼写出最终字符串
	* 			如:aaaa{%any}bbbb{%any}cccc{%any}ddddd
	* 			调用getStringWithParam("com.title",{"add",23,45.6}) -> aaaaaddbbbb23cccc45.6ddddd;
	* 			是按照顺序进行赋值,如果要设置精度，可在创建GValue对象后调用setFormatString来设置
	*
	* @param	key   	The key.
	* @param	params	参数列表 注：会根据传入的参数类型生成一个格式串
	* 					如{"",""}->%s%s {"",22.3}->%s%f
	*
	* @return	The string.
	*/

	string getStringWithParam(
		const string& key, 
		const vector<GValue>& params, 
		string defaultString = "");

	string getStringWithParam(
		const string& key,
		const GValue& param1 = GValue::Null,
		const GValue& param2 = GValue::Null,
		const GValue& param3 = GValue::Null,
		const GValue& param4 = GValue::Null,
		const GValue& param5 = GValue::Null,
		const GValue& param6 = GValue::Null,
		const GValue& param7 = GValue::Null,
		const GValue& param8 = GValue::Null,
		const GValue& param9 = GValue::Null,
		const GValue& param10 = GValue::Null,
		string defaultString = "");


	/**
	 * @brief	当有需要在描述中写入参数时，会根据传入的参数拼写出最终字符串 
	 * 			如:aaaa{%any}bbbb{%any}cccc{%any}ddddd
	 *			调用formatString(aaaa{%any}bbbb{%any}cccc{%any}ddddd,{"add",23,45.6}) -> aaaaaddbbbb23cccc45.6ddddd;
	 *
	 * @param [in,out]	szFormat	待格式字符串
	 * @param	params			 	参数列表 注：会根据传入的参数类型生成一个格式串 如{"",""}->%s%s {"",22.3}->%s%f.
	 *
	 * @return	A string.
	 */

	string formatString(string szFormat, const vector<GValue>& params);
	string formatString(
		string szFormat,
		const GValue& param1 = GValue::Null,
		const GValue& param2 = GValue::Null,
		const GValue& param3 = GValue::Null,
		const GValue& param4 = GValue::Null,
		const GValue& param5 = GValue::Null,
		const GValue& param6 = GValue::Null,
		const GValue& param7 = GValue::Null,
		const GValue& param8 = GValue::Null,
		const GValue& param9 = GValue::Null,
		const GValue& param10 = GValue::Null);

	/**
	 * @brief	通过key得到语言包的配置数组文字
	 *
	 * @param	key	The key.
	 *
	 * @return	配置数组文字
	 */

	vector<string> getVector(const string& key);

	string getLocalFont();

	string getBitmapFont();

	string getArial14Font();

private:

	Language();

	/**
	 * @brief	Searches for the first string.
	 *
	 * @param	keys	The keys.
	 *
	 * @return	The found string.
	 */

	string findString(const vector<string>& keys , string defaultString );

	/**
	 * @brief	Searches for the first vector.
	 *
	 * @param	keys		 	The keys.
	 * @param	defaultString	The default string.
	 *
	 * @return	The found vector.
	 */

	vector<string> findVector(const vector<string>& keys);

	/**
	 * @brief	Check key.
	 *
	 * @param	key	The key.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	bool checkKey(const string& key , vector<string>& keys );

	/**
	 * @brief	Splits.
	 *
	 * @param	src				待切分字符串.
	 * @param [in,out]	vect	切分完成后的字符串.
	 * @param	values			切割值.
	 */

	void splitWithParam(string src,vector<string>& vect,vector<GValue> values);

	/**
	 * @brief	Creates split tokens.
	 *
	 * @param [in,out]	values	The values.
	 * @param [in,out]	tokens	The tokens.
	 */

	void createSplitTokens(vector<GValue>& values, vector<string>& tokens);

private:

	__Dictionary* m_pLanguage;
};