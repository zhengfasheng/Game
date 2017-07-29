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
 *  Date:2017/7/28 0:33
 *
 *  Summary:Declares the view class
 *  
 ******************************************************************************/
#pragma once

#include "common.h"
#include "cocos2d.h"

USING_NS_CC;

const static int SHOW_ACTION_TAG = 100;
const static int HIDE_ACTION_TAG = 200;

class UIViewDelegate;
class UIView : public Layer
{
public:
	UIView();
	~UIView();

	virtual bool init(UIViewDelegate* pDelegate);

	/**
	 * @brief	�����Ƿ���ʾ 
	 *
	 * @return	true if show, false if not.
	 */

	virtual bool IsShow();

	/** @brief	��ʾ���� */
	virtual void Show();

	/** @brief	���ؽ��� */
	virtual void Hide();

	/** @brief	��������Լ�ʵ�����볡������������ʾ���ʱ���ô˺��� */
	virtual void ShowEnd();

	/** @brief	���������д�˳��������������������ʱ���ô˺��� */
	virtual void HideEnd();

	virtual void setEnableShowAction(bool bIsEnable) final;
	virtual bool isEnableShowAction() final;

	virtual void setEnableHideAction(bool bIsEnable) final;
	virtual bool isEnableHideAction()  final;

	/** @brief	ֻ�е������볡�������˺����Ż���� */
	virtual void ShowWithAction();

	/** @brief	ֻ�е���������������˺����Ż���� */
	virtual void HideWithAction();

	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

protected:

	bool m_bIsShow;
	bool m_bIsEnableShowAction;
	bool m_bIsEnableHideAction;
	UIViewDelegate* m_pDelegate;
};

//���ﲻ���õ�cocos���Զ��ͷųأ���UIManager���Լ������ڴ�

#define IMPLEMENT_CREATE_VIEW( _TYPE_ ) \
public:\
static _TYPE_* create(UIViewDelegate* pDelegate)\
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