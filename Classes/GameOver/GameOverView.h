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
 *  Date:2017/8/27 15:30
 *
 *  Summary:游戏结束显示视图
 *  
 ******************************************************************************/
#pragma once

#include "UIView.h"

USING_UI;

class GameOverView : public UIView
{
	GameOverView();
public:
	virtual ~GameOverView();

	virtual bool init(UIViewControllerDelegate* pDelegate) override;

	IMPLEMENT_CREATE_VIEW(GameOverView);

private:

	Action* getMenuItemAction();
};