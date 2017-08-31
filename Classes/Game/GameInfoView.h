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
 *  Date:2017/8/27 18:24
 *
 *  Summary: 游戏信息（剩余血量，分数等）
 *  
 ******************************************************************************/
#pragma once

#include "GameView.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
class GameInfoView : public GameView
{
	GameInfoView();

public:
	virtual ~GameInfoView();

	virtual bool init(UIViewControllerDelegate* pUIViewControllerDelegate) override;

	IMPLEMENT_CREATE_VIEW(GameInfoView);

	virtual void decreaseRebornTimes( int nLife );

	virtual void setScore(int nScore);

private:

	void onGamePause(Ref* pSender);



private:

	//分数标签
	TextBMFont* m_pScoreText;

	//生命次数
	std::vector<Sprite*> m_pLifeCountSpriteVec;
};