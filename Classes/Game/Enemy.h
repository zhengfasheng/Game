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
 *  Date:2017/8/27 1:26
 *
 *  Summary:�л�
 *  
 ******************************************************************************/
#pragma once

#include "EntityObject.h"
#include "GameConfig.h"

class EnemyInfo;
class Bullet;

static Vec2 invaildPos = Vec2( -9999, -9999 );

class Enemy : public EntityObject
{
public:

	Enemy();
	~Enemy();

	static Enemy* create(EnemyInfo* pInfo);

	bool init(EnemyInfo* pInfo);
	//�ͷŶ���
	virtual void destory() override;
	//�����ܵ�����
	virtual void hurt( int nValue ) override;
	//�����ܵ�ȫ��Ĺ����˺���Ҳ����һ������
	virtual void hurt() override;
	//�����Ƿ����
	virtual bool isLive() override;
	//�õ���ײ���Ե�Rect
	virtual Rect getCollideRect() override;

	//�ƶ�����
	const EnemyMoveType getMoveType();

	void shoot(float dt);

	//�õ�ʵ��Ĺ����˺�
	virtual int getPower() override;

	//�õ�ʵ���Ѫ��
	virtual int getHP() override;

	//�õ���������
	const AttackModel getAttackModel() const ;

	//�ƶ��ٶ�
	const float getMoveSpeed() const;

private:

	Action* createBulletAction(Bullet* pBullet , Vec2 pos = invaildPos );

	void onBulletMoveEnd(Bullet* pBullet);

	void bossShoot();

	void bossSecondShoot();

private:

	//�л������Ϣ
	EnemyInfo* m_pInfo;
};