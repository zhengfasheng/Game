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
 *  Date:2017/7/26 23:41
 *
 *  Summary:Declares the object factory class
 *  
 ******************************************************************************/
#pragma once

#include "IFactory.h"

struct tClass;
class ObjectFactory : public IFactory
{
	ObjectFactory();
	IMPLEMENT_SINGLETON(ObjectFactory);
	virtual ~ObjectFactory();
	virtual void registerClass(tClass* pClass) override;
	virtual Ref* create( const std::string& szClassName ) override;

private:
	std::map<std::string, tClass*> m_classes;
};