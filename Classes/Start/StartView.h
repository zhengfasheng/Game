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
 *  Date:2017/8/20 18:59
 *
 *  Summary:开始界面视图
 *  
 ******************************************************************************/
#pragma once
#include "UIView.h"

USING_UI;
class StartView : public UIView
{
	StartView();
public:
	virtual ~StartView();

	enum class SpriteLayout
	{
		Plane = 100,//在上面游走的小飞机
		Logo,//logo
		Menu,//菜单
	};

	virtual bool init(UIViewControllerDelegate* pDelegate) override;

	IMPLEMENT_CREATE_VIEW(StartView);

private:

	//新游戏
	void onNewGame(Ref* pSender);

	//关于游戏 
	void onAbout(Ref* pSender);

	//游戏设置
	void onSetting(Ref* pSender);

	//小飞机动作结束回调
	void flyEndCallback();

	//监听小飞机的坐标位置
	void onFlying(float dt);

private:

	Sprite* m_pFlyPlane;//在界面上随机位置飞行的小飞机
};