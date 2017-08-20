/******************************************************************************
 * Copyright (c) 2017 . All rights reserved.
 *
 *
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
 *  Email:zheng_fasheng@qq.com
 *
 *  Date:2017/7/25 21:56
 *
 *  Summary:Declares the commontools class
 *  
 ******************************************************************************/
#pragma once

#include "cocos2d.h"

template<class T>
std::string toString(const T& data)
{
	std::stringstream os;
	os << data;
	return os.str();
}

/**
* @brief	Splits.
*
* @param	src				待切分字符串.
* @param	token			做切割的token
* @param [in,out]	vect	切分完成后的字符串
*/

void split(std::string src, const char* token, std::vector<std::string>& vect);

cocos2d::Texture2D* getTextureForKey(const std::string& key);