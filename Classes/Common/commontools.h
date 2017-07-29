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
 *  Date:2017/7/25 21:56
 *
 *  Summary:Declares the commontools class
 *  
 ******************************************************************************/
#pragma once
#include <string>
#include <sstream>
using namespace std;
template<class T>
string toString(const T& data)
{
	stringstream os;
	os << data;
	return os.str();
}

#pragma region 输入所有支持iterator的对象

template< class T >
void printObject(T obj, string separator = "\t")
{
	typedef T type;
	for (type::iterator it = obj.begin(); it != obj.end(); it++)
	{
		cout << *it << separator;
	}
	cout << endl;
}

#pragma endregion

#define IMPLEMENT_GET_NAME( _NAME_ )\
virtual std::string getName() override\
{\
	return #_NAME_;\
}

#define SAVE_DELETE(p) if(p){ delete p ; p = nullptr;}