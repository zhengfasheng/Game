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
 *  Summary:敌机
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
	//释放对象
	virtual void destory() override;
	//对象受到攻击
	virtual void hurt( int nValue ) override;
	//对象受到全额的攻击伤害，也就是一击毙命
	virtual void hurt() override;
	//对象是否活着
	virtual bool isLive() override;
	//得到碰撞测试的Rect
	virtual Rect getCollideRect() override;

	//移动类型
	const EnemyMoveType getMoveType();

	void shoot(float dt);

	//得到实体的攻击伤害
	virtual int getPower() override;

	//得到实体的血量
	virtual int getHP() override;

	//得到攻击类型
	const AttackModel getAttackModel() const ;

	//移动速度
	const float getMoveSpeed() const;

private:

	Action* createBulletAction(Bullet* pBullet , Vec2 pos = invaildPos );

	void onBulletMoveEnd(Bullet* pBullet);

	void bossShoot();

	void bossSecondShoot();

private:

	//敌机相关信息
	EnemyInfo* m_pInfo;
};