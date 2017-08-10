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
 *  Date:2017/7/29 19:53
 *
 *  Summary:Declares the hall main sate class
 *  
 ******************************************************************************/
#pragma once
#include "Dialog.h"

class HallMainDialog : public Dialog
{
public:
	HallMainDialog();
	virtual ~HallMainDialog();

	virtual UIView* createView(DialogDelegate* pDelegate) override;

	//void onLoginResult(GValue p1, GValue p2, GValue p3, GValue p4);

	virtual void WillShow() override;

	EVENT_HANDLER_BEGIN
		//EVENT_HANDLER(UIEvent::EVENT_LOGIN_RESULT, onLoginResult);
	EVENT_HANDLER_END

};