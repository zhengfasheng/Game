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
 *  Summary:����Ϸ��ʾ��ͼ�������ж������ͼ
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
		Map,//��ͼ
		Op,//������
		Info,//��Ϸ��Ϣ��
		Pause,//��ͣ
	};

	virtual ~GameMainView();

	virtual bool init(UIViewControllerDelegate* pDelegate) override;

	IMPLEMENT_CREATE_VIEW(GameMainView);

	virtual GameInfoView* getGameInfoView();
	virtual GameOpView* getGameOpView();

	/** @brief	��ʾ��ͣ��ͼ */
	virtual void showGamePauseView();

	virtual void Show() override;

private:

	/** @brief	��ͼ */
	GameMapView* m_pMapView;

	/** @brief	��Ϸ��Ϣ */
	GameInfoView* m_pGameInfoView;

	/** @brief	��Ҳ����� */
	GameOpView* m_pGameOpView;

};