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
 *  Summary: 资源场景加载代理
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
	 * @brief	释放指定场景资源开始
	 *
	 * @param	type	The type.
	 */

	virtual void unloadResourceStart(SceneType type) {};

	/**
	 * @brief	释放指定场景资源完成
	 *
	 * @param	type	The type.
	 */

	virtual void unloadResourceComplete(SceneType type) {};

	/** @brief	加载场景资源开始 */
	virtual void loadResourceStart(SceneType type) {};

	/** @brief	加载场景资源完成 */
	virtual void loadResourceComplete(SceneType type) {};

	/**
	 * @brief	资源加载进度
	 *
	 * @param	nLoadedCount	已经加载的数量
	 * @param	nTotal			需要加载的资源总数
	 */

	virtual void loadResourceProgress(SceneType type , unsigned int nLoadedCount, unsigned int nTotal) {};

};
