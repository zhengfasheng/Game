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
 *  Date:2017/7/28 23:25
 *
 *  Summary:Declares the view delegate class
 *  
 ******************************************************************************/
#pragma once
#include <string>
#include "GValue.h"



class UIViewDelegate
{
public:
	enum class EventType
	{
		Game,
		UI,
	};
	UIViewDelegate();
	virtual ~UIViewDelegate();

	virtual void WillShow() = 0;
	virtual void DidShow() = 0;
	virtual void WillHide() = 0;
	virtual void DidHide() = 0;
	virtual void OnReturnKey() = 0;
	virtual bool OnEvent(const std::string& szEventName, const GValue& param1, const GValue& param2, const GValue& param3, const GValue& param4, UIViewDelegate::EventType type){ return true; }
	template< class T1, class T2, class T3, class T4>
	void SendEvent(const std::string& szEventName, T1 p1, T2 p2, T3 p3, T4 p4)
	{
		OnEvent(szEventName, p1, p2, p3, p4,UIViewDelegate::EventType::UI);
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

#define EVENT_HANDLER_BEGIN \
public: \
virtual bool OnEvent(const std::string& szEventName, const GValue& param1, const GValue& param2, const GValue& param3, const GValue& param4 , UIViewDelegate::EventType type ) override\
{

#define EVENT_HANDLER( _EVENT_NAME_ , _FUNCTION_ )\
	if ( _EVENT_NAME_ == szEventName )\
	{\
		_FUNCTION_(param1,param2,param3,param4);\
		return true;\
	}

#define EVENT_HANDLER_END\
	return true;\
}

#define DECLARE_HANDLER( _FUNCTION_NAME_ ) \
void _FUNCTION_NAME_(const GValue& p1, const GValue& p2, const GValue& p3, const GValue& p4)

#define IMPLEMENT_HANDLER( _TYPE_ , _FUNCTION_NAME_ )\
void _TYPE_::_FUNCTION_NAME_(const GValue& p1, const GValue& p2, const GValue& p3, const GValue& p4)
