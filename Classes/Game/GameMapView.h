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
 *  Summary:��Ϸ��ͼ
 *  
 ******************************************************************************/
#pragma once

#include "GameView.h"

class GameMapView : public GameView
{
	GameMapView();

	enum class ZOder
	{
		Sky = 1,//���
		Map,//��ͼ
	};

public:
	virtual ~GameMapView();

	virtual bool init(UIViewControllerDelegate* pUIViewControllerDelegate) override;

	IMPLEMENT_CREATE_VIEW(GameMapView);

private:

	bool createContent();

	void clear();

	//������պ͵�ͼ�Ĺ�������
	Action* createMoveAction(bool bIsSky = true);

	//������ղ����ͼ����ƶ�
	//���������Ҫ��Ϊ�˵����ƶ������У���û�е��ý����ص�
	//����ղ���ͼ���Ѿ�����λ��ʱ�Ĵ���
	void onSkyAndMapMoving(float dt);

	//����ƶ������ص�
	void onMoveSkyEnd();

	//��ͼ�ƶ������ص�
	void onMoveMapEnd();

private:

	//������ͼ��ʵ�ֹ���Ч��
	Sprite* m_pBackSkySprite[2];
	//ͬ��
	TMXTiledMap* m_pGameMap[2];
};