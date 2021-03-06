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
 *  Date:2017/8/27 1:02
 *
 *  Summary:�¼�����
 *  
 ******************************************************************************/
#pragma once
#include "GValue.h"
#include "Any.h"

class EventDelegate
{
public:
	EventDelegate(){}
	virtual ~EventDelegate(){}
	virtual bool OnEvent(const std::string& szEventName, const GValue& param1, const GValue& param2, const GValue& param3, const GValue& param4){ return true; }
	virtual GValue GetValue(const std::string& szValueName) { return GValue::Null; }
	template< class T1, class T2, class T3, class T4>
	void SendEvent(const std::string& szEventName, T1 p1, T2 p2, T3 p3, T4 p4)
	{
		OnEvent(szEventName, p1, p2, p3, p4);
	}

	template<class T1, class T2, class T3 >
	void SendEvent(const std::string& szEventName, T1 p1, T2 p2, T3 p3)
	{
		SendEvent(szEventName, p1, p2, p3, 0);
	}

	template<class T1, class T2>
	void SendEvent(const std::string& szEventName, T1 p1, T2 p2)
	{
		SendEvent(szEventName, p1, p2, 0);
	}

	template<class T1>
	void SendEvent(const std::string& szEventName, T1 p1)
	{
		SendEvent(szEventName, p1, 0);
	}

	void SendEvent(const std::string& szEventName)
	{
		SendEvent(szEventName, 0);
	}
};