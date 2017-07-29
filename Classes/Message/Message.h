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
 *  Date:2017/7/29 16:04
 *
 *  Summary: 与server通信的消息
 *  
 ******************************************************************************/
#pragma once
#include <string>

enum class MessageType
{
	Invalid,
	ApplyLogin,
	ChipsChange,
};

class Message
{
public:
	Message(  );
	virtual ~Message();

	virtual Message* clone();

	int m_nID;

	bool m_bIsSuccess;
};


class ApplyLogin : public Message
{
public:
	ApplyLogin();
	virtual ~ApplyLogin();

	virtual Message* clone();

	std::string m_szAccount;
	std::string m_szPwd;
};

class ResponseLogin : public Message
{
public:
	ResponseLogin();
	virtual ~ResponseLogin();
	virtual Message* clone();

	std::string m_szName;
	std::string m_szAccount;
	int m_nChips;
};

class ApplyChipsChang : public Message
{
public:
	ApplyChipsChang();
	~ApplyChipsChang();
	virtual Message* clone() override;
};

class ResponseChipsChange : public Message
{
public:
	ResponseChipsChange();
	~ResponseChipsChange();
	virtual Message* clone() override;
	int m_nChips;
};