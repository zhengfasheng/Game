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
 *  Summary:对话框代理，UIViewController 与 UIView 之间通信桥梁
 *  
 ******************************************************************************/
#pragma once
#include "UIDefine.h"
#include "EventDelegate.h"

UI_BEGIN

class UIViewControllerDelegate : public EventDelegate
{
public:
	UIViewControllerDelegate();
	virtual ~UIViewControllerDelegate();

	virtual void WillShow() = 0;
	virtual void DidShow() = 0;
	virtual void WillHide() = 0;
	virtual void DidHide() = 0;
	virtual void OnReturnKey() = 0;
};

UI_END

