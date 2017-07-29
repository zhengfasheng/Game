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
 *  Date:2017/7/29 15:56
 *
 *  Summary: 负责与服务器的消息收发
 *  
 ******************************************************************************/
#pragma once

class Message;
class Connector
{
public:
	Connector();
	virtual ~Connector();

	virtual void RegisterEvent(){}

	virtual void UnRegisterEvent(){}

	virtual void sendServerRequest(Message* pMsg) final;

	virtual void onReceiveServerResponse(Message* pMsg) ;

	virtual void sendHttpRequest(Message* pMsg) final;

	virtual void onReceiveHttpResponse(Message* pMsg);
};