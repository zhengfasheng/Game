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
 *  Summary:子弹
 *  
 ******************************************************************************/
#pragma once

#include "EntityObject.h"
#include "GameConfig.h"

//子弹类型
struct BulletType
{
	float fSpeed;//fSpeed 速度， 1 秒移到多少距离
	int   nPower;//攻击类型
	std::string szTextureName;//纹理名称
	AttackModel model;//攻击模式
	float  fAttackScope;//攻击范围
	BulletType(float fSpeed, int nPower, const std::string& szTextureName, AttackModel model, int fAttackScope)
	{
		this->fSpeed = fSpeed;
		this->nPower = nPower;
		this->szTextureName = szTextureName;
		this->model = model;
		this->fAttackScope = fAttackScope;
	}
	BulletType* clone()
	{
		return new(std::nothrow)BulletType(fSpeed, nPower, szTextureName, model, fAttackScope);
	}
};

class Bullet : public EntityObject
{
public:

	Bullet();
	~Bullet();
	/*
	 * pSrcObj 是谁发出的
	 * type 子弹类型
	 */
	static Bullet* create(EntityObject* pSrcObj, BulletType type,const std::string& szName );

	bool init(EntityObject* pSrcObj, BulletType type ,const std::string& szName);

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

	//得到实体的攻击伤害
	virtual int getPower() override;

	//得到实体的血量
	virtual int getHP() override;

	virtual void update(float delta) override;

	//得到子弹类型
	const BulletType* getBulletType() const
	{
		return m_pType;
	}

private:

	//血量
	int m_nHP;

	//子弹类型
	BulletType* m_pType;

};