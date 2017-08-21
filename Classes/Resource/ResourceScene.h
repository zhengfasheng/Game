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
 *  Date:2017/8/19 1:09
 *
 *  Summary:资源场景，用于场景间的资源加载与
 *  
 ******************************************************************************/
#pragma once

#include "IScene.h"
#include "ResourceDelegate.h"
#include "SceneType.h"
#include "ResourceCommand.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
class ResourceScene : public IScene , public ResourceDelegate
{
	ResourceScene();
public:
	virtual ~ResourceScene(  );
	static ResourceScene* create(SceneDelegate* pDelegate, SceneType fromSceneType , SceneType toSceneType);

	virtual bool init(SceneDelegate* pDelegate, SceneType fromSceneType, SceneType toSceneType);

	/**
	* @brief	释放指定场景资源开始
	*
	* @param	type	The type.
	*/

	virtual void unloadResourceStart(SceneType type) override;

	/**
	* @brief	释放指定场景资源完成
	*
	* @param	type	The type.
	*/

	virtual void unloadResourceComplete(SceneType type) override;

	/** @brief	加载场景资源开始 */
	virtual void loadResourceStart(SceneType type) override;

	/** @brief	加载场景资源完成 */
	virtual void loadResourceComplete(SceneType type) override;

	/**
	* @brief	资源加载进度
	*
	* @param	nLoadedCount	已经加载的数量
	* @param	nTotal			需要加载的资源总数
	*/

	virtual void loadResourceProgress(SceneType type, unsigned int nLoadedCount, unsigned int nTotal) override;

	virtual void DidEnter() override;

	virtual void DidExit() override;

private:

	void setLoadingString(const std::string& szContent);
	void setLoadingBarVisible(bool bIsVisible);
	void setLoadingBarProgress(float fProgress);

private:

	//进度条
	LoadingBar* m_pLoadingBar;

	//进度显示标签
	Text* m_pShowLoadingText;

	SceneType m_fromSceneType;
	SceneType m_toSceneType;
	ResourceCommand* m_pFromSceneCommand;
	ResourceCommand* m_pToSceneCommand;
};