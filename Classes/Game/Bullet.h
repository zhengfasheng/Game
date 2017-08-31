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
 *  Summary:�ӵ�
 *  
 ******************************************************************************/
#pragma once

#include "EntityObject.h"
#include "GameConfig.h"

//�ӵ�����
struct BulletType
{
	float fSpeed;//fSpeed �ٶȣ� 1 ���Ƶ����پ���
	int   nPower;//��������
	std::string szTextureName;//��������
	AttackModel model;//����ģʽ
	float  fAttackScope;//������Χ
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
	 * pSrcObj ��˭������
	 * type �ӵ�����
	 */
	static Bullet* create(EntityObject* pSrcObj, BulletType type,const std::string& szName );

	bool init(EntityObject* pSrcObj, BulletType type ,const std::string& szName);

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

	//�õ�ʵ��Ĺ����˺�
	virtual int getPower() override;

	//�õ�ʵ���Ѫ��
	virtual int getHP() override;

	virtual void update(float delta) override;

	//�õ��ӵ�����
	const BulletType* getBulletType() const
	{
		return m_pType;
	}

private:

	//Ѫ��
	int m_nHP;

	//�ӵ�����
	BulletType* m_pType;

};