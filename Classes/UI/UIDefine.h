/******************************************************************************
 *  Copyright (c) 2017 Topfun Technologies Inc. All rights reserved.
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
 *  Date:2017/8/11 11:29
 *
 *  Summary:名字空间与ui相关宏的定义
 *  
 ******************************************************************************/
#pragma once

#ifdef __cplusplus

#define UI_BEGIN                     namespace UI {
#define UI_END                       }
#define USING_UI                     using namespace UI

#else
#define UI_BEGIN                     
#define UI_END                       
#define USING_UI                    
#endif


//UIView实现宏
#define IMPLEMENT_CREATE_VIEW( _TYPE_ ) \
public:\
	static _TYPE_* create(UI::UIViewControllerDelegate* pDelegate)\
{\
	auto pRet = new _TYPE_();\
	if (pRet && pRet->init(pDelegate))\
	{\
	pRet->autorelease();\
	}\
	else\
	{\
	CC_SAFE_DELETE(pRet);\
	}\
	return pRet;\
}

//控制器接收事件实现宏
#define EVENT_HANDLER_BEGIN \
public: \
	virtual bool OnEvent(const std::string& szEventName, const GValue& param1, const GValue& param2, const GValue& param3, const GValue& param4) override\
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

//控制器接收事件实现宏
#define GET_VALUE_HANDLER_BEGIN \
public: \
virtual GValue GetValue(const std::string& szEventName) override\
{

#define GET_VALUE_HANDLER( _EVENT_NAME_ , _FUNCTION_ )\
	if ( _EVENT_NAME_ == szEventName )\
	{\
		return _FUNCTION_();\
	}

#define GET_VALUE_HANDLER_END\
	return GValue::Null;\
}



//处理接收事件函数定义宏
#define DECLARE_HANDLER( _FUNCTION_NAME_ ) \
	void _FUNCTION_NAME_(const GValue& p1, const GValue& p2, const GValue& p3, const GValue& p4)
//处理接收事件函数实现宏
#define IMPLEMENT_HANDLER( _TYPE_ , _FUNCTION_NAME_ )\
	void _TYPE_::_FUNCTION_NAME_(const GValue& p1, const GValue& p2, const GValue& p3, const GValue& p4)

#define IMPLEMENT_GET_REAL_VIEW( _VIEW_TPYE_ ) \
_VIEW_TPYE_* getRealView() \
{ \
	return dynamic_cast<_VIEW_TPYE_*>(getView()); \
}