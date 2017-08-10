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
#include <map>
#include <functional>
#include "cocos2d.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"

USING_NS_CC;

using namespace cocos2d::network;
;

class IParser;
class Message;
class DataHelper
{
public:
	DataHelper();
	virtual ~DataHelper();

	virtual void RegisterEvent(){}

	virtual void UnRegisterEvent(){}

	virtual void sendServerRequest(Message* pMsg) final;

	virtual void onReceiveServerResponse(Message* pMsg) ;

	template<class DataType>
	void sendHttpRequest(Message* pMsg, const std::function<void(const DataType& data)>& callback)
	{

		HttpRequest* request = new (std::nothrow) HttpRequest();
		// required fields
		request->setUrl("http://httpbin.org/ip");
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback([callback](HttpClient* client, HttpResponse* response){
			DataType data;
			data.decode("");
			callback(data);
		});
		if (true)
		{
			request->setTag("GET immediate test2");
			HttpClient::getInstance()->sendImmediate(request);
		}
		else
		{
			request->setTag("GET test2");
			HttpClient::getInstance()->send(request);
		}
		// don't forget to release it, pair to new
		request->release();
	}

	virtual void onReceiveHttpResponse(Message* pMsg) final;

public:

};