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
 *  Date:2017/8/19 2:02
 *
 *  Summary:◊ ‘¥º”‘ÿ√¸¡Ó
 *  
 ******************************************************************************/
#pragma once
#include "Command.h"
#include "ResourceCommanDelegate.h"
#include "SceneType.h"
#include "cocos2d.h"

USING_NS_CC;

class ResourceDelegate;
class ResourceCommand : public ResourceCommanDelegate
{
public:
	ResourceCommand( ResourceDelegate* pDelegate , SceneType type );
	virtual ~ResourceCommand();

	virtual void onLoading(Texture2D* pTexture, const char* szResourceName) = 0;

	virtual void unloadResourceStart() override;
	virtual void unloadResourceComplete() override;
	virtual void loadResourceStart() override;
	virtual void loadResourceComplete() override;
	virtual void loadResourceProgress(unsigned int nLoaded, unsigned int nTotal) override;
	virtual const SceneType& getSceneType() const final;
protected:

	ResourceDelegate* m_pDelegate;

private:

	SceneType m_sceneType;
};