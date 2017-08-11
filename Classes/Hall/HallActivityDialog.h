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
 *  Date:2017/7/29 19:58
 *
 *  Summary:Declares the hall activity state class
 *  
 ******************************************************************************/
#pragma once

#include "UIViewController.h"
USING_UI;
class HallActivityDialog : public UIViewController
{
public:
	HallActivityDialog();
	virtual ~HallActivityDialog();

	virtual UIView* createView(UIViewControllerDelegate* pDelegate) override;

	//void onLoginResult(GValue p1, GValue p2, GValue p3, GValue p4);



	EVENT_HANDLER_BEGIN
		//EVENT_HANDLER(UIEvent::EVENT_LOGIN_RESULT, onLoginResult);
	EVENT_HANDLER_END
};