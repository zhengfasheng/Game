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
 *  Date:2017/7/29 21:26
 *
 *  Summary:Declares the hall user information view class
 *  
 ******************************************************************************/
#pragma once

#include "UIView.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class HallUserInfoView : public UIView
{
	HallUserInfoView();
public:
	~HallUserInfoView();
	virtual bool init(UIViewDelegate* pDelegate) override;

	IMPLEMENT_CREATE_VIEW(HallUserInfoView);

	void setAccount(const std::string& szAccount);
	void setUserName(const std::string& szName);
	void setChips(const int nChips);

private:
	void onClose(Ref* pSender);
	void onChange(Ref* pSender);

private:

	Text* m_pAccount;
	Text* m_pName;
	Text* m_pChips;

};