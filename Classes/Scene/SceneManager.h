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
 *  Date:2017/7/29 0:42
 *
 *  Summary: 负责各场景的创建与场景之间的跳转,接收场景（初始化，进入，退出等状态）并通知UI管理器做相应的场景切换处理
 *  
 ******************************************************************************/
#pragma once
#include "Sigleton.h"
#include "SceneDelegate.h"
#include "IScene.h"
class SceneManager : public SceneDelegate
{
	SceneManager();
public:
	~SceneManager();

	virtual void Init(IScene* pScene) override;

	virtual void OnEnter(IScene* pScene) override;

	virtual void OnEnterTransitionDidFinish(IScene* pScene) override;

	virtual void OnExit(IScene* pScene) override;

	virtual void OnExitTransitionDidStart(IScene* pScene) override;

	void GameStart();

	void GoToScene(SceneType type);

private:

	void GoToHall();

	void GoToLogin();


	IMPLEMENT_SINGLETON(SceneManager);
};