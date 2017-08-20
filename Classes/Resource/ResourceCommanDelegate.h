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
 *  Date:2017/8/19 2:13
 *
 *  Summary:资源加载指令代理
 *  
 ******************************************************************************/
#pragma once

class ResourceCommanDelegate
{
public:
	ResourceCommanDelegate(){}
	virtual ~ResourceCommanDelegate(){}

	virtual void unloadResourceStart() = 0;
	virtual void unloadResourceComplete() = 0;
	virtual void loadResourceStart() = 0;
	virtual void loadResourceComplete() = 0;
	virtual void loadResourceProgress(unsigned int nLoaded, unsigned int nTotal) = 0;
};