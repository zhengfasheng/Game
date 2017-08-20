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
 *  Date:2017/8/19 2:32
 *
 *  Summary:开始场景资源加载
 *  
 ******************************************************************************/
#pragma once
#include "ResourceCommand.h"

class StartSceneResourceCommand : public ResourceCommand
{
public:
	StartSceneResourceCommand(ResourceDelegate* pDelegate);
	virtual ~StartSceneResourceCommand();

	virtual void onLoading(Texture2D* pTexture, const char* szResourceName) override;

	virtual void unloadResourceStart() override;
	virtual void loadResourceStart() override;

private:

	//当前进度数
	int m_nCurrentFinish;

	std::vector<std::string> m_resources;
};