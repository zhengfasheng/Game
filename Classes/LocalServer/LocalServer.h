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
 *  Date:2017/7/29 16:32
 *
 *  Summary:这里面只是为了演示做一个服务器的模拟
 *  
 ******************************************************************************/
#pragma once
#include "Singleton.h"
#include "ServerDelegate.h"
#include <list>

class LocalServer : public ServerDelegate
{
	LocalServer();
public:

	struct MassageInfo
	{
		MassageInfo(Message* pMsg, DataHelper* pConnector)
			:m_pMsg(pMsg), m_pConnector(pConnector)
		{

		}
		Message* m_pMsg;
		DataHelper* m_pConnector;
	};
	virtual ~LocalServer();
	IMPLEMENT_SINGLETON(LocalServer);

	virtual void onReceiveClientServerRequest(Message* pMsg, DataHelper* pConnector) override;
	virtual void sendServerResponse(Message* pMsg, DataHelper* pConnector) override;

	virtual void onReceiveClientHttpRequest(Message* pMsg, DataHelper* pConnector) override;
	virtual void sendHttpResponse(Message* pMsg, DataHelper* pConnector) override;

private:

	virtual void start();
protected:
	std::list<MassageInfo> m_queue;
};