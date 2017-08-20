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
 *  Date:2017/8/20 18:54
 *
 *  Summary:开始界面
 *  
 ******************************************************************************/
#pragma once
#include "UIViewController.h"

USING_UI;

class StartController : public UIViewController
{
public:
	StartController();
	virtual ~StartController();

	virtual UIView* createView(UIViewControllerDelegate* pDelegate) override;

	DECLARE_HANDLER(onNewGame);

	DECLARE_HANDLER(onAbout);

	DECLARE_HANDLER(onSetting);

	EVENT_HANDLER_BEGIN
		EVENT_HANDLER(UIEvent::EVENT_OPEN_ABOUT, onAbout);
		EVENT_HANDLER(UIEvent::EVENT_OPENT_SETTING, onSetting);
		EVENT_HANDLER(UIEvent::EVENT_START_NEW_GAME, onNewGame);
	EVENT_HANDLER_END
};