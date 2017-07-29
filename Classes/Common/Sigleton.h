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
 *  Date:2017/7/25 21:52
 *
 *  Summary:µ¥Àý
 *  
 ******************************************************************************/
#pragma once

template<class T>
class Sigleton
{
public:
	Sigleton()
	{
		m_pInstance = static_cast<T*>(this);
	}
	virtual ~Sigleton()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
		}
		m_pInstance = nullptr;
	}

	static T* getInstance()
	{
		return m_pInstance;
	}

protected:
	static T* m_pInstance;
};

#define SINGLETON_INIT( TYPE ) \
template <>	 TYPE * Sigleton< TYPE >::m_pInstance = new TYPE


#define IMPLEMENT_SINGLETON( _TYPE_ )\
public:\
static _TYPE_* getInstance()\
{\
	static _TYPE_ s_instance;\
	return &s_instance;\
}