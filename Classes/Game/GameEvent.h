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
 *  Summary:����Ϸ�����¼�����
 *  
 ******************************************************************************/
#pragma once
#include <string>

namespace GameEvent
{
	
	/** @brief	֪ͨBoss �л�����ɱ  */
	const std::string NOTIFY_BOOS_DEAD = "NOTIFY_BOOS_DEAD";

	/** @brief	֪ͨ�ӷ� */
	const std::string NOTIFY_ADD_SCORE = "NOTIFY_ADD_SCORE";

	/** @brief	֪ͨɾ���л��ӵ� */
	const std::string NOTIFY_REMOVE_ENEMY_BULLET = "NOTIFY_REMOVE_ENEMY_BULLET";

	/** @brief	��ʼ���ӵл� */
	const std::string NOTITY_START_ADD_ENEMY = "NOTITY_START_ADD_ENEMY";
	/** @brief	ֹͣ���ӵл� */
	const std::string NOTITY_STOP_ADD_ENEMY = "NOTITY_STOP_ADD_ENEMY";

	/** @brief	�Լ��ķɻ���ײ�� */
	const std::string NOTITY_MY_AIRPLANE_DESTORY = "NOTITY_MY_AIRPLANE_DESTORY";

	/** @brief	���� */
	const std::string NOTIFY_MY_AIRPLANE_REBORN = "NOTIFY_MY_AIRPLANE_RENEW";

	/** @brief	ɾ���Լ�������ӵ� */
	const std::string NOTIFY_REMOVE_MY_BULLET = "NOTIFY_REMOVE_MY_BULLET";

	/** @brief	��Ϸ��ͣ */
	const std::string NOTITY_GAME_PAUSE = "NOTITY_GAME_PAUSE";

	/** @brief	��Ϸ�ָ� */
	const std::string NOTITY_GAME_RESUME = "NOTITY_GAME_RESUME";

	/** @brief	�Լ��ĵл���ʼ��� */
	const std::string NOTIFY_AIRPLANE_SHOOT = "NOTIFY_AIRPLANE_SHOOT";

	/** @brief	�л���ʼ���. */
	const std::string NOFITY_ENEMY_SHOOT = "NOFITY_ENEMY_SHOOT";

	/** @brief	����Ϸ�߼�update����֪ͨ */
	const std::string NOTIFY_GAME_UPDATE = "NOTIFY_GAME_UPDATE";

	/** @brief	��ӵл�����Ϸ������ͼ */
	const std::string NOTIFY_ADD_ENEMY_TO_VIEW = "NOTIFY_ADD_ENEMY_TO_VIEW";

	/** @brief	֪ͨɾ���л� */
	const std::string NOTIFY_REMOVE_ENEMY = "NOTIFY_REMOVE_ENEMY";
	/** @brief	��Ҳ����ķɻ����� */
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