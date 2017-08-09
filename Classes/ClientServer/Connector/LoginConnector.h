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
 *  Date:2017/7/29 16:24
 *
 *  Summary: 登录模块与服务器的消息收发
 *  
 ******************************************************************************/
#pragma once
#include "Sigleton.h"
#include "Connector.h"
#include "common.h"

class LoginConnector : public Connector
{
	LoginConnector();
public:
	virtual ~LoginConnector();
	IMPLEMENT_SINGLETON(LoginConnector);

	virtual void onReceiveServerResponse(Message* pMsg) override;

	void sendApplyLogin(const std::string& szAccount, const std::string& szPwd);

	void sendApplyChipsChange();
};
