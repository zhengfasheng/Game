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
 *  Date:2017/8/27 16:38
 *
 *  Summary:游戏地图
 *  
 ******************************************************************************/
#pragma once

#include "GameView.h"

class GameMapView : public GameView
{
	GameMapView();

	enum class ZOder
	{
		Sky = 1,//天空
		Map,//地图
	};

public:
	virtual ~GameMapView();

	virtual bool init(UIViewControllerDelegate* pUIViewControllerDelegate) override;

	IMPLEMENT_CREATE_VIEW(GameMapView);

private:

	bool createContent();

	void clear();

	//创建天空和地图的滚动动作
	Action* createMoveAction(bool bIsSky = true);

	//监听天空层与地图层的移动
	//这个方法主要是为了当在移动过程中，还没有调用结束回调
	//但天空层或地图层已经到达位置时的处理
	void onSkyAndMapMoving(float dt);

	//天空移动结束回调
	void onMoveSkyEnd();

	//地图移动结束回调
	void onMoveMapEnd();

private:

	//用两张图来实现滚动效果
	Sprite* m_pBackSkySprite[2];
	//同上
	TMXTiledMap* m_pGameMap[2];
};