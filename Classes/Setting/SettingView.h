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
 *  Date:2017/8/23 21:31
 *
 *  Summary:设置
 *  
 ******************************************************************************/
#pragma once

#include "UIView.h"

USING_UI;

class SettingView : public UIView
{
	SettingView();
public:
	virtual ~SettingView();

	virtual bool init(UIViewControllerDelegate* pDelegate) override;

	IMPLEMENT_CREATE_VIEW(SettingView);

private:

	//返回
	void onGoBack(Ref* pSender);

	//设置背景音乐回调
	void onSettingBackMusic(Ref* pSender);

	//设置音效回调
	void onSettingAudio(Ref* pSender);
};