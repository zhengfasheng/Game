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
 *  Summary:玩家控制的小飞机
 *  
 ******************************************************************************/
#pragma once

#include "EntityObject.h"

class Bullet;
//飞机
class Airplane : public EntityObject
{
public:

	Airplane();
	~Airplane();

	static Airplane* create(int nLevel, int nPower, float fShootSpeed);

	//初始化
	virtual bool init(int nLevel, int nPower, float fShootSpeed);

	//受伤
	virtual void hurt( int nValue ) override;

	//对象受到全额的攻击伤害，也就是一击毙命
	virtual void hurt() override;

	//销毁飞机
	virtual void destory() override;

	//是否活着
	virtual bool isLive() override;

	//得到碰撞Rect
	virtual Rect getCollideRect() override;

	//得到实体的攻击伤害
	virtual int getPower() override;

	//得到实体的血量
	virtual int getHP() override;

	//飞机设置飞机等级
	void setLevel(int nValue);

	void setShootSpeed(float fSpeed);

private:

	//射击
	void shoot(float dt);

	//开始射击
	void startShoot();

	//改变敲击速度
	void changeShootSpeed(float fSpeed);

	//设置是否可被攻击
	void setCanAttaked(bool bIsAttacked)
	{
		m_bCanAttack = bIsAttacked;
	}

	//创建子弹的移动动作
	Action* createBulletAction(Bullet* pBullet);

	//子弹移动结束
	void onBulletMoveEnd(Bullet* pBullet);

private:

	//子弹速度
	int m_nBulletSpeed;

	//生命值
	int m_nHP;

	//是否可被攻击
	bool m_bCanAttack;

	//初始位置
	Point m_appearPosition;

	//攻击力
	int m_nPower;

	//发射速度
	float m_fShootSpeed;

	//当前飞机等级
	int m_nLevel;

};