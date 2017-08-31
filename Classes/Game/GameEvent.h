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
 *  Date:2017/8/27 2:57
 *
 *  Summary:主游戏界面事件定义
 *  
 ******************************************************************************/
#pragma once
#include <string>

namespace GameEvent
{
	
	/** @brief	通知Boss 敌机被击杀  */
	const std::string NOTIFY_BOOS_DEAD = "NOTIFY_BOOS_DEAD";

	/** @brief	通知加分 */
	const std::string NOTIFY_ADD_SCORE = "NOTIFY_ADD_SCORE";

	/** @brief	通知删除敌机子弹 */
	const std::string NOTIFY_REMOVE_ENEMY_BULLET = "NOTIFY_REMOVE_ENEMY_BULLET";

	/** @brief	开始增加敌机 */
	const std::string NOTITY_START_ADD_ENEMY = "NOTITY_START_ADD_ENEMY";
	/** @brief	停止增加敌机 */
	const std::string NOTITY_STOP_ADD_ENEMY = "NOTITY_STOP_ADD_ENEMY";

	/** @brief	自己的飞机被撞毁 */
	const std::string NOTITY_MY_AIRPLANE_DESTORY = "NOTITY_MY_AIRPLANE_DESTORY";

	/** @brief	重生 */
	const std::string NOTIFY_MY_AIRPLANE_REBORN = "NOTIFY_MY_AIRPLANE_RENEW";

	/** @brief	删除自己打出的子弹 */
	const std::string NOTIFY_REMOVE_MY_BULLET = "NOTIFY_REMOVE_MY_BULLET";

	/** @brief	游戏暂停 */
	const std::string NOTITY_GAME_PAUSE = "NOTITY_GAME_PAUSE";

	/** @brief	游戏恢复 */
	const std::string NOTITY_GAME_RESUME = "NOTITY_GAME_RESUME";

	/** @brief	自己的敌机开始射击 */
	const std::string NOTIFY_AIRPLANE_SHOOT = "NOTIFY_AIRPLANE_SHOOT";

	/** @brief	敌机开始射击. */
	const std::string NOFITY_ENEMY_SHOOT = "NOFITY_ENEMY_SHOOT";

	/** @brief	主游戏逻辑update方法通知 */
	const std::string NOTIFY_GAME_UPDATE = "NOTIFY_GAME_UPDATE";

	/** @brief	添加敌机到游戏操作视图 */
	const std::string NOTIFY_ADD_ENEMY_TO_VIEW = "NOTIFY_ADD_ENEMY_TO_VIEW";

	/** @brief	通知删除敌机 */
	const std::string NOTIFY_REMOVE_ENEMY = "NOTIFY_REMOVE_ENEMY";
	/** @brief	玩家操作的飞机升级 */
	const std::string NOTIFY_AIRPLANE_LEVEL_UP = "NOTIFY_AIRPLANE_LEVEL_UP";

	const std::string GET_AIRPLANE_LEVEL = "GET_AIRPLANE_LEVEL";
	const std::string GET_AIRPLANE_POWER = "GET_AIRPLANE_POWER";
	const std::string GET_AIRPLANE_SHOOT_SPEED = "GET_AIRPLANE_SHOOT_SPEED";
	
	const std::string GET_AIRPLANE_POSITION = "GET_AIRPLANE_POSITION";
	const std::string GET_GAME_TIME = "GET_GAME_TIME";

	const std::string GET_GAME_LEVEL_INTERVAL = "GET_GAME_LEVEL_INTERVAL";
	const std::string GET_GAME_LEVEL_MAX_COUNT = "GET_GAME_LEVEL_MAX_COUNT";
	const std::string GET_GAME_LEVEL_MIN_TYPE = "GET_GAME_LEVEL_MIN_TYPE";
	const std::string GET_GAME_LEVEL_MAX_TYPE = "GET_GAME_LEVEL_MAX_TYPE";

	const std::string GET_AIRPLANE_LEVEL_INFO = "GET_AIRPLANE_LEVEL_INFO"; 
}