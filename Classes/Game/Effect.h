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
 *  Date:2017/8/27 1:21
 *
 *  Summary:游戏特效
 *  
 ******************************************************************************/
#pragma once

#include "common.h"

class Effect : public Node
{
public:
	CREATE_FUNC(Effect);
	Effect();
	~Effect();

	virtual bool init() override;

	//屏幕闪光特效
	void playFlareEffect(Node* pParent , int nZOder , Vec2 pos , float fRotation , float fDuration , CallFunc* pCall );

	//爆炸特效
	void playExplodeEffect(Node* pParent, int nZOder, Vec2 pos, CallFunc* pCall = nullptr);
	
	//闪光特效
	void playSparkEffect(Node* pParent, int nZOder,  Vec2 pos, float fScale = 1.2f, float fDuration = 0.7f);

private:

	void playEnd(Node* pSender);

};