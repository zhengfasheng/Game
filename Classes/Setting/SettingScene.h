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
 *  Date:2017/8/23 21:26
 *
 *  Summary:…Ë÷√≥°æ∞
 *  
 ******************************************************************************/
#pragma once
#include "IScene.h"

class SettingScene : public IScene
{
public:
	SettingScene();
	virtual ~SettingScene();
	IMPLEMENT_CREATE_SCENE(SettingScene, SceneType::Setting);

	virtual void DidEnter() override;
};
