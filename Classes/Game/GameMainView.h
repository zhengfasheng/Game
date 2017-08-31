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
 *  Date:2017/8/27 16:47
 *
 *  Summary:主游戏显示视图，里面有多个字视图
 *  
 ******************************************************************************/
#pragma once

#include "UIView.h"
#include "GameEvent.h"

USING_UI;
class GameMapView;
class GameInfoView;
class GameOpView;
class Bullet;
class GameMainView : public UIView
{
	GameMainView();
public:
	enum class ZOder
	{
		Map,//地图
		Op,//操作层
		Info,//游戏信息层
		Pause,//暂停
	};

	virtual ~GameMainView();

	virtual bool init(UIViewControllerDelegate* pDelegate) override;

	IMPLEMENT_CREATE_VIEW(GameMainView);

	virtual GameInfoView* getGameInfoView();
	virtual GameOpView* getGameOpView();

	/** @brief	显示暂停视图 */
	virtual void showGamePauseView();

	virtual void Show() override;

private:

	/** @brief	地图 */
	GameMapView* m_pMapView;

	/** @brief	游戏信息 */
	GameInfoView* m_pGameInfoView;

	/** @brief	玩家操作层 */
	GameOpView* m_pGameOpView;

};