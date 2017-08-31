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
 *  Date:2017/8/26 0:08
 *
 *  Summary:�л�������
 *  
 ******************************************************************************/
#pragma once

#include "GameConfig.h"

class EnemyInfo
{
	EnemyType m_type; //�л�����
	int m_nHp; //�л�Ѫ��
	EnemyMoveType m_moveType;//�ƶ�����
	int m_nScore;//�л��ķ���
	int m_nPower;//�л��Ĺ�����
	float m_fShootSpeed;//�����ӵ��ٶ�
	float m_fMoveSpeed;//�ƶ��ٶ�
	float m_fAttackScope;//������Χ
	AttackModel m_attackModel;//����ģʽ
public:

	EnemyInfo(
		EnemyType type,
		int nHP,
		EnemyMoveType moveType,
		int nScore,
		int nPower,
		AttackModel attackModel = AttackModel::Normal,
		float fShootSpeed = g_fMinShootSpeed,
		float fMoveSpeed = g_fMinMoveSpeed,
		float fAttackScope = attackScope()
		);

	//���صл���������
	const char* getTextureName() const;

	//���صл��ӵ���������
	const char* getBulletTextureName() const;

	//���صл�����
	const EnemyType getType() const;

	//���صл�Ѫ��
	const int getHP() const;
	void setHP(int nValue);

	//���صл��ķ���
	const int getScore() const;

	//���صл����ƶ�����
	const EnemyMoveType getMoveType() const;

	//���صл��Ĺ�����
	const int getPower() const;

	//���ط����ӵ��ٶ�
	const float getShootSpeed() const;
	void setShootSpeed(float fValue);

	//��¡һ������
	EnemyInfo* clone();

	//�ƶ��ٶ�
	const float getMoveSpeed() const;
	void setMoveSpeed(float fValue);

	//������Χ
	const float getAttackScope() const;

	//����ģʽ
	const AttackModel getAttackModel() const;
};

class Enemy;
class Bullet;
class GameController;
class EnemyManager
{
private:
	EnemyManager();
	~EnemyManager();

	//��ʼ���л�ģ��
	virtual bool init( );

	void createEnemy(float dt);

	//�ָ�Ĭ��
	void recoverToDefault();

	//����boss�Ƿ�ը��
	void setBossDestroy(bool bIsDeath);

	//��ӵл�������
	void addEnemyToLayer(EnemyInfo* pInfo);

	//�л��ƶ������ص�
	void moveEndCallback(Enemy* pEnemy);

	//ɾ��ս��
	void removeEnemy(Enemy* pEnemy);

	//����boss�Ƿ����
	void setBossAppear(bool bIsAppear);
	bool isBossAppear();
	bool isBossDestroy();

	//boss�ƶ������Ĵ���
	void onBossMoveEnd(Enemy* pEnemy);

	void addEnemyToContainer(Enemy* pEnemy);
	/** @brief	����л��������ӵ� */
	void addEnemyToBulletContainer(Bullet* pBullet);

	void addMyBulletContainer(Bullet* pBullet);

private:

	std::vector<EnemyInfo> m_enemyInfoVec;

	//��¼�ϴ����ӵл���ʱ��
	float m_fPrevAddEnemyTime;

	//�����Ƿ���Ļ��boss�л�
	char m_bossFlag[2];

	Vector<Enemy*> m_enemyContainer;

	//����л��������ӵ�
	Vector<Bullet*> m_enemyBulletContainer;

	//�����Լ��ɻ���������ӵ�
	Vector<Bullet*> m_myBulletContainer;

	friend class GameController;
};