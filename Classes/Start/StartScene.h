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
 *  Date:2017/8/20 18:50
 *
 *  Summary:¿ªÊ¼³¡¾°
 *  
 ******************************************************************************/
#pragma once

#include "IScene.h"

class StartScene : public IScene
{
public:
	StartScene();
	virtual ~StartScene();
	IMPLEMENT_CREATE_SCENE(StartScene, SceneType::Start);

	virtual void DidEnter() override;
};