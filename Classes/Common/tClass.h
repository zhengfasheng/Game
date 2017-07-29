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
 *  Date:2017/7/26 21:26
 *
 *  Summary:Declares the class class
 *  
 ******************************************************************************/
#pragma once
#include "common.h"
#include "Ref.h"

struct tClass
{
	std::string m_szClassName;
	std::function<Ref*()> m_createFunc;
};

//根据类定义取得定义类
#define GETCLASS(className) (&className::m_class##className)

//类定义声明宏
#define DECLARE_CLASS( className ) \
public:\
	static tClass m_class##className;\
	typedef typename className className##type

//类定义实现宏
#define IMPLEMENT_CLASS( className )\
	tClass className::m_class##className = \
	{ #className,[](){ return new className();}}
