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
 *  Date:2017/7/29 1:01
 *
 *  Summary:�����ӿ�
 *  
 ******************************************************************************/
#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum class SceneType
{
	Invalid,
	Login,
	Hall,
	Room,
	RoomList,
};

class SceneDelegate;
class IScene : public Scene
{
public:
	IScene();
	virtual ~IScene();

#pragma region ��������д����
	virtual void WillEnter() {}
	virtual void DidEnter(){}
	virtual void WillExit(){}
	virtual void DidExit(){}
#pragma endregion ��������д����

#pragma region ������д����
	/**
	* @brief	������Ϸ��������ָ������
	*
	* @param [in,out]	pDelegate	If non-null, the delegate.
	*
	* @return	true if it succeeds, false if it fails.
	*/

	virtual bool init(SceneDelegate* pDelegate, SceneType type) final;

	virtual void onEnter() override final;

	virtual void onEnterTransitionDidFinish() override final;

	virtual void onExit() override final;

	virtual void onExitTransitionDidStart() override final;

	virtual const SceneType& getSceneType() final;
#pragma endregion ������д����
	
protected:

	SceneDelegate* m_pDelegate;

	SceneType m_type;
};

#define IMPLEMENT_CREATE_SCENE( _TYPE_ , _SCENE_TYPE_ ) \
public:\
static _TYPE_* create(SceneDelegate* pDelegate, SceneType type = _SCENE_TYPE_ )\
{\
	auto pRet = new _TYPE_();\
	if (pRet && pRet->init(pDelegate, type))\
	{\
		pRet->autorelease();\
	}\
	else\
	{\
		CC_SAFE_DELETE(pRet);\
	}\
	return pRet;\
}