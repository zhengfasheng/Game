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
 *  Summary:敌机管理器
 *  
 ******************************************************************************/
#pragma once

#include "GameConfig.h"

class EnemyInfo
{
	EnemyType m_type; //敌机类型
	int m_nHp; //敌机血量
	EnemyMoveType m_moveType;//移动类型
	int m_nScore;//敌机的分数
	int m_nPower;//敌机的攻击力
	float m_fShootSpeed;//发射子弹速度
	float m_fMoveSpeed;//移动速度
	float m_fAttackScope;//攻击范围
	AttackModel m_attackModel;//攻击模式
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

	//返回敌机纹理名称
	const char* getTextureName() const;

	//返回敌机子弹纹理名称
	const char* getBulletTextureName() const;

	//返回敌机类型
	const EnemyType getType() const;

	//返回敌机血量
	const int getHP() const;
	void setHP(int nValue);

	//返回敌机的分数
	const int getScore() const;

	//返回敌机的移动类型
	const EnemyMoveType getMoveType() const;

	//返回敌机的攻击力
	const int getPower() const;

	//返回发射子弹速度
	const float getShootSpeed() const;
	void setShootSpeed(float fValue);

	//克隆一个对象
	EnemyInfo* clone();

	//移动速度
	const float getMoveSpeed() const;
	void setMoveSpeed(float fValue);

	//攻击范围
	const float getAttackScope() const;

	//攻击模式
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

	//初始化敌机模板
	virtual bool init( );

	void createEnemy(float dt);

	//恢复默认
	void recoverToDefault();

	//设置boss是否被炸毁
	void setBossDestroy(bool bIsDeath);

	//添加敌机到界面
	void addEnemyToLayer(EnemyInfo* pInfo);

	//敌机移动结束回调
	void moveEndCallback(Enemy* pEnemy);

	//删除战机
	void removeEnemy(Enemy* pEnemy);

	//设置boss是否出现
	void setBossAppear(bool bIsAppear);
	bool isBossAppear();
	bool isBossDestroy();

	//boss移动结束的处理
	void onBossMoveEnd(Enemy* pEnemy);

	void addEnemyToContainer(Enemy* pEnemy);
	/** @brief	保存敌机发出的子弹 */
	void addEnemyToBulletContainer(Bullet* pBullet);

	void addMyBulletContainer(Bullet* pBullet);

private:

	std::vector<EnemyInfo> m_enemyInfoVec;

	//记录上次增加敌机的时间
	float m_fPrevAddEnemyTime;

	//现在是否屏幕有boss敌机
	char m_bossFlag[2];

	Vector<Enemy*> m_enemyContainer;

	//保存敌机发出的子弹
	Vector<Bullet*> m_enemyBulletContainer;

	//保存自己飞机发射出的子弹
	Vector<Bullet*> m_myBulletContainer;

	friend class GameController;
};