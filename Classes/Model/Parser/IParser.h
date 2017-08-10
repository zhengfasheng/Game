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
 *  Date:2017/8/9 22:28
 *
 *  Summary:数据解析类,主要用于php的http请求的解析
 *  
 ******************************************************************************/
#pragma once
#include "common.h"

class IParser
{
public:
	IParser();
	virtual ~IParser();

	virtual bool decode(const std::string& strMsg);

	virtual bool encode(const std::string& strMsg);

};