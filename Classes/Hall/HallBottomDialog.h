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
 *  Date:2017/7/29 19:57
 *
 *  Summary:Declares the hall bottom state class
 *  
 ******************************************************************************/
#pragma once
#include "Dialog.h"
#include "UIEvent.h"

class HallBottomDialog : public Dialog
{
public:
	HallBottomDialog();
	virtual ~HallBottomDialog();

	virtual UIView* createView(DialogDelegate* pDelegate) override;

	DECLARE_HANDLER(onUserInfoChange);
	DECLARE_HANDLER(onUserChipsChange);



	EVENT_HANDLER_BEGIN
		EVENT_HANDLER(UIEvent::EVENT_USER_INFO_CHANGE, onUserInfoChange);
		EVENT_HANDLER(UIEvent::EVENT_USER_CHIPS_CHANGE, onUserChipsChange);
	EVENT_HANDLER_END
};