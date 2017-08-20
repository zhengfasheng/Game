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
 *  Summary:��ʼ������ͼ
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
		Plane = 100,//���������ߵ�С�ɻ�
		Logo,//logo
		Menu,//�˵�
	};

	virtual bool init(UIViewControllerDelegate* pDelegate) override;

	IMPLEMENT_CREATE_VIEW(StartView);

private:

	//����Ϸ
	void onNewGame(Ref* pSender);

	//������Ϸ 
	void onAbout(Ref* pSender);

	//��Ϸ����
	void onSetting(Ref* pSender);

	//С�ɻ����������ص�
	void flyEndCallback();

	//����С�ɻ�������λ��
	void onFlying(float dt);

private:

	Sprite* m_pFlyPlane;//�ڽ��������λ�÷��е�С�ɻ�
};