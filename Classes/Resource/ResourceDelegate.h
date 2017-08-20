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
 *  Date:2017/8/19 0:58
 *
 *  Summary: ��Դ�������ش���
 *  
 ******************************************************************************/
#pragma once
#include "SceneType.h"
class ResourceDelegate
{
public:
	ResourceDelegate(){}
	virtual ~ResourceDelegate(){}

	/**
	 * @brief	�ͷ�ָ��������Դ��ʼ
	 *
	 * @param	type	The type.
	 */

	virtual void unloadResourceStart(SceneType type) {};

	/**
	 * @brief	�ͷ�ָ��������Դ���
	 *
	 * @param	type	The type.
	 */

	virtual void unloadResourceComplete(SceneType type) {};

	/** @brief	���س�����Դ��ʼ */
	virtual void loadResourceStart(SceneType type) {};

	/** @brief	���س�����Դ��� */
	virtual void loadResourceComplete(SceneType type) {};

	/**
	 * @brief	��Դ���ؽ���
	 *
	 * @param	nLoadedCount	�Ѿ����ص�����
	 * @param	nTotal			��Ҫ���ص���Դ����
	 */

	virtual void loadResourceProgress(SceneType type , unsigned int nLoadedCount, unsigned int nTotal) {};

};
