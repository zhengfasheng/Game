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
 *  Date:2017/8/20 1:15
 *
 *  Summary:资源命令工厂
 *  
 ******************************************************************************/
#pragma once
#include "common.h"
#include "SceneType.h"
#include "ResourceDelegate.h"

class ResourceCommand;
class ResourceCommandFactory final
{
	ResourceCommandFactory();
	~ResourceCommandFactory();

	IMPLEMENT_SINGLETON(ResourceCommandFactory);

	ResourceCommand* create(ResourceDelegate* pDelegate , SceneType type);
};