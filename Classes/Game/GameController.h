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
 *  Summary:主游戏控件器
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

	//boss被击杀
	DECLARE_HANDLER(onBossDead);
	//加分
	DECLARE_HANDLER(onAddScore);
	//删除敌机打出子弹
	DECLARE_HANDLER(onRemoveEnemyBullet);
	//开始生产敌机
	DECLARE_HANDLER(onStartAddEnemy);
	//停止生产敌机
	DECLARE_HANDLER(onStopAddEnemy);
	//自己的飞机被撞毁
	DECLARE_HANDLER(onMyAirplaneDestory);
	//自己的飞机重生
	DECLARE_HANDLER(onMyAirplaneReborn);
	//删除自己打出的子弹
	DECLARE_HANDLER(onRemoveMyBullet);

	//玩家飞机射击
	DECLARE_HANDLER(onAirplaneShoot);

	//游戏暂停
	DECLARE_HANDLER(onGamePause);
	//游戏恢复
	DECLARE_HANDLER(onGameResume);

	//主游戏逻辑update通知
	DECLARE_HANDLER(onGameUpdate);

	//添加敌机到游戏视图
	DECLARE_HANDLER(onAddEnemyToView);

	//通知删除敌机
	DECLARE_HANDLER(onRemoveEnemy);

	//敌机射击
	DECLARE_HANDLER(onEnemyShoot);

	//玩家操作飞机升级
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

	/** @brief	销毁 */
	void destory();

	//检查碰撞
	void checkCollide();

	//是否发生碰撞
	bool IsCollide(EntityObject* pA, EntityObject* pB);

	//检查是否这个对象还活着，如果活着，走update，如果已经挂了，删除掉
	void checkObject(float dt);

	//减少重生次数显示器
	void decreaseRebornTimes();

	GameOpView* getOpView();

	GameInfoView* getInfoView();

private:

	
	/** @brief	敌机管理器 */
	EnemyManager* m_pEnemyManager;

	/** @brief	游戏等级（难度）管理器 */
	GameLevelManager* m_pGameLevelManger;

	AirplaneLevelManager* m_pAirplaneLevelManager;

	//当前游戏时长
	float m_fGameTime;
};