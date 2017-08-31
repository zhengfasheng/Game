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
 *  Date:2017/8/25 23:43
 *
 *  Summary:����Ϸ�ؼ���
 *  
 ******************************************************************************/
#pragma once
#include "cocos2d.h"
#include "GameEvent.h"
#include "UIViewController.h"

USING_UI;
USING_NS_CC;
class EnemyManager;
class GameLevelManager;
class AirplaneLevelManager;
class GameMainView;
class EntityObject;
class GameInfoView;
class GameOpView;
class GameLevel;
class GameController : public UIViewController
{
public:
	GameController();
	virtual ~GameController();

	virtual UIView* createView(UIViewControllerDelegate* pDelegate) override;

	virtual bool Init(UIManager* pManager, ControllerID id) override;

	GameMainView* getRealView();

	virtual void DidShow() override;

private:

	//boss����ɱ
	DECLARE_HANDLER(onBossDead);
	//�ӷ�
	DECLARE_HANDLER(onAddScore);
	//ɾ���л�����ӵ�
	DECLARE_HANDLER(onRemoveEnemyBullet);
	//��ʼ�����л�
	DECLARE_HANDLER(onStartAddEnemy);
	//ֹͣ�����л�
	DECLARE_HANDLER(onStopAddEnemy);
	//�Լ��ķɻ���ײ��
	DECLARE_HANDLER(onMyAirplaneDestory);
	//�Լ��ķɻ�����
	DECLARE_HANDLER(onMyAirplaneReborn);
	//ɾ���Լ�������ӵ�
	DECLARE_HANDLER(onRemoveMyBullet);

	//��ҷɻ����
	DECLARE_HANDLER(onAirplaneShoot);

	//��Ϸ��ͣ
	DECLARE_HANDLER(onGamePause);
	//��Ϸ�ָ�
	DECLARE_HANDLER(onGameResume);

	//����Ϸ�߼�update֪ͨ
	DECLARE_HANDLER(onGameUpdate);

	//��ӵл�����Ϸ��ͼ
	DECLARE_HANDLER(onAddEnemyToView);

	//֪ͨɾ���л�
	DECLARE_HANDLER(onRemoveEnemy);

	//�л����
	DECLARE_HANDLER(onEnemyShoot);

	//��Ҳ����ɻ�����
	DECLARE_HANDLER(onAirplaneLevelUp);

	EVENT_HANDLER_BEGIN
	EVENT_HANDLER(GameEvent::NOTIFY_BOOS_DEAD, onBossDead);
	EVENT_HANDLER(GameEvent::NOTIFY_ADD_SCORE, onAddScore);
	EVENT_HANDLER(GameEvent::NOTIFY_REMOVE_ENEMY_BULLET, onRemoveEnemyBullet);
	EVENT_HANDLER(GameEvent::NOTITY_START_ADD_ENEMY, onStartAddEnemy);
	EVENT_HANDLER(GameEvent::NOTITY_STOP_ADD_ENEMY, onStopAddEnemy);
	EVENT_HANDLER(GameEvent::NOTITY_MY_AIRPLANE_DESTORY, onMyAirplaneDestory);
	EVENT_HANDLER(GameEvent::NOTIFY_MY_AIRPLANE_REBORN, onMyAirplaneReborn);
	EVENT_HANDLER(GameEvent::NOTIFY_REMOVE_MY_BULLET, onRemoveMyBullet);
	EVENT_HANDLER(GameEvent::NOTIFY_AIRPLANE_SHOOT, onAirplaneShoot);
	EVENT_HANDLER(GameEvent::NOTITY_GAME_PAUSE, onGamePause);
	EVENT_HANDLER(GameEvent::NOTITY_GAME_RESUME, onGameResume);
	EVENT_HANDLER(GameEvent::NOTIFY_GAME_UPDATE, onGameUpdate);
	EVENT_HANDLER(GameEvent::NOTIFY_ADD_ENEMY_TO_VIEW, onAddEnemyToView);
	EVENT_HANDLER(GameEvent::NOTIFY_REMOVE_ENEMY, onRemoveEnemy);
	EVENT_HANDLER(GameEvent::NOFITY_ENEMY_SHOOT, onEnemyShoot);
	EVENT_HANDLER(GameEvent::NOTIFY_AIRPLANE_LEVEL_UP, onAirplaneLevelUp);
	EVENT_HANDLER_END

	
	GValue getAirplaneLevel();
	GValue getAirplanePower();
	GValue getAirplaneShootSpeed();
	GValue getAirplanePosition();
	GValue getGameTime();

	GameLevel getGameLevel();
	GValue getGameLevelInterval();
	GValue getGameLevelMaxCount();
	GValue getGameLevelMinType();
	GValue getGameLevelMaxType();

	GValue getAirplaneLevelInfo();

	GET_VALUE_HANDLER_BEGIN
	GET_VALUE_HANDLER(GameEvent::GET_AIRPLANE_LEVEL, getAirplaneLevel);
	GET_VALUE_HANDLER(GameEvent::GET_AIRPLANE_POWER, getAirplanePower);
	GET_VALUE_HANDLER(GameEvent::GET_AIRPLANE_SHOOT_SPEED, getAirplaneShootSpeed);
	GET_VALUE_HANDLER(GameEvent::GET_AIRPLANE_POSITION, getAirplanePosition);
	GET_VALUE_HANDLER(GameEvent::GET_GAME_TIME, getGameTime);

	GET_VALUE_HANDLER(GameEvent::GET_GAME_LEVEL_INTERVAL, getGameLevelInterval);
	GET_VALUE_HANDLER(GameEvent::GET_GAME_LEVEL_MAX_COUNT, getGameLevelMaxCount);
	GET_VALUE_HANDLER(GameEvent::GET_GAME_LEVEL_MIN_TYPE, getGameLevelMinType);
	GET_VALUE_HANDLER(GameEvent::GET_GAME_LEVEL_MAX_TYPE, getGameLevelMaxType);


	GET_VALUE_HANDLER(GameEvent::GET_AIRPLANE_LEVEL_INFO, getAirplaneLevelInfo);

	GET_VALUE_HANDLER_END

private:

	/** @brief	���� */
	void destory();

	//�����ײ
	void checkCollide();

	//�Ƿ�����ײ
	bool IsCollide(EntityObject* pA, EntityObject* pB);

	//����Ƿ�������󻹻��ţ�������ţ���update������Ѿ����ˣ�ɾ����
	void checkObject(float dt);

	//��������������ʾ��
	void decreaseRebornTimes();

	GameOpView* getOpView();

	GameInfoView* getInfoView();

private:

	
	/** @brief	�л������� */
	EnemyManager* m_pEnemyManager;

	/** @brief	��Ϸ�ȼ����Ѷȣ������� */
	GameLevelManager* m_pGameLevelManger;

	AirplaneLevelManager* m_pAirplaneLevelManager;

	//��ǰ��Ϸʱ��
	float m_fGameTime;
};