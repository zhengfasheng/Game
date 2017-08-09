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
 *  Date:2017/8/9 22:32
 *
 *  Summary:Declares the uset information class
 *  
 ******************************************************************************/
#pragma once

#include "IParser.h"
#include "CCPlatformMacros.h"

enum class Sex
{
	Male,
	Famale,
};

class UserInfo : public IParser
{
public:
	UserInfo();
	virtual ~UserInfo();

	virtual bool decode(const std::string& strMsg) override;

	virtual bool encode(const std::string& strMsg) override;


	CC_SYNTHESIZE(Sex, m_sex, Sex);
	CC_SYNTHESIZE(std::string, m_szName, Name);
	CC_SYNTHESIZE(int, m_nChips, Chips);
	CC_SYNTHESIZE(std::string, m_szAccount, Account);

};