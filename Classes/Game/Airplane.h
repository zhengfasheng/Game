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
 *  Date:2017/8/27 1:29
 *
 *  Summary:��ҿ��Ƶ�С�ɻ�
 *  
 ******************************************************************************/
#pragma once

#include "EntityObject.h"

class Bullet;
//�ɻ�
class Airplane : public EntityObject
{
public:

	Airplane();
	~Airplane();

	static Airplane* create(int nLevel, int nPower, float fShootSpeed);

	//��ʼ��
	virtual bool init(int nLevel, int nPower, float fShootSpeed);

	//����
	virtual void hurt( int nValue ) override;

	//�����ܵ�ȫ��Ĺ����˺���Ҳ����һ������
	virtual void hurt() override;

	//���ٷɻ�
	virtual void destory() override;

	//�Ƿ����
	virtual bool isLive() override;

	//�õ���ײRect
	virtual Rect getCollideRect() override;

	//�õ�ʵ��Ĺ����˺�
	virtual int getPower() override;

	//�õ�ʵ���Ѫ��
	virtual int getHP() override;

	//�ɻ����÷ɻ��ȼ�
	void setLevel(int nValue);

	void setShootSpeed(float fSpeed);

private:

	//���
	void shoot(float dt);

	//��ʼ���
	void startShoot();

	//�ı��û��ٶ�
	void changeShootSpeed(float fSpeed);

	//�����Ƿ�ɱ�����
	void setCanAttaked(bool bIsAttacked)
	{
		m_bCanAttack = bIsAttacked;
	}

	//�����ӵ����ƶ�����
	Action* createBulletAction(Bullet* pBullet);

	//�ӵ��ƶ�����
	void onBulletMoveEnd(Bullet* pBullet);

private:

	//�ӵ��ٶ�
	int m_nBulletSpeed;

	//����ֵ
	int m_nHP;

	//�Ƿ�ɱ�����
	bool m_bCanAttack;

	//��ʼλ��
	Point m_appearPosition;

	//������
	int m_nPower;

	//�����ٶ�
	float m_fShootSpeed;

	//��ǰ�ɻ��ȼ�
	int m_nLevel;

};