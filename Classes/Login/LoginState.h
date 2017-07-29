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
 *  Date:2017/7/29 1:56
 *
 *  Summary:µÇÂ¼½çÃæ
 *  
 ******************************************************************************/
#pragma once
#include "State.h"

class LoginState : public State
{
public:
	LoginState();
	virtual ~LoginState();

	virtual UIView* createView(UIViewDelegate* pDelegate) override;

	DECLARE_HANDLER(onLoginResult);

	DECLARE_HANDLER(onApplyLogin);

	EVENT_HANDLER_BEGIN
		EVENT_HANDLER(UIEvent::EVENT_LOGIN_RESULT, onLoginResult);
		EVENT_HANDLER(UIEvent::EVENT_APPLY_LOGIN, onApplyLogin);
	EVENT_HANDLER_END

};