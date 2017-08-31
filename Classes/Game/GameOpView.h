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
 *  Date:2017/8/27 19:15
 *
 *  Summary:��Ҳ�����
 *  
 ******************************************************************************/
#pragma once

#include "GameView.h"

class Airplane;
class Enemy;
class Bullet;
class GameOpView : public GameView
{
	GameOpView();
public:

	virtual ~GameOpView();

	virtual bool init(UIViewControllerDelegate* pUIViewControllerDelegate ) override;

	IMPLEMENT_CREATE_VIEW(GameOpView);

	/** @brief	����������Ч */
	void startPlaySunEffect();

	/** @brief	�����Ҳ����ķɻ� */
	void addAirplane();

	virtual void Show() override;
	virtual void HideEnd() override;

	virtual void update(float delta) override;

	Airplane* getAirplane();

	/** @brief	�ɻ����� */
	void checkAirplane();

	/** @brief	��ʼ��ӵл� */
	virtual void startAddEnemy();

	//ֹͣ���ӵл�
	virtual void stopAddEnemy();

	virtual void addEnemy(Enemy* pEnemy);

	virtual void addBullet(Bullet* pBullet);

protected:

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
	virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
	virtual void onTouchEnded(Touch *touch, Event *unused_event) override;
	virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;

private:

	void schedulePlaySunEffect( float dt );

private:

	//�Լ��ķɻ�
	Airplane* m_pAirplane;

	//�¼�������
	EventListenerTouchOneByOne* m_pListener;
};