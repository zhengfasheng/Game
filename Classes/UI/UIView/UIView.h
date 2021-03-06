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
 *  Summary:显示视图，对Controller提供更新视图的接口，派发用户事件给Controller
 *  
 ******************************************************************************/
#pragma once

#include "common.h"
#include "cocos2d.h"
#include "UIViewControllerDelegate.h"
USING_NS_CC;

UI_BEGIN
const static int SHOW_ACTION_TAG = 100;
const static int HIDE_ACTION_TAG = 200;

class UIView : public Layer
{
public:
	UIView();
	~UIView();

	virtual bool init(UIViewControllerDelegate* pDelegate);

	/**
	 * @brief	界面是否显示 
	 *
	 * @return	true if show, false if not.
	 */

	virtual bool IsShow();

	/** @brief	显示界面 */
	virtual void Show();

	/** @brief	隐藏界面 */
	virtual void Hide();

	/** @brief	子类如果自己实现了入场动作，必须显示完成时调用此函数 */
	virtual void ShowEnd();

	/** @brief	子类如果重写了出场动作，必须隐藏完成时调用此函数 */
	virtual void HideEnd();

	virtual void setEnableShowAction(bool bIsEnable) final;
	virtual bool isEnableShowAction() final;

	virtual void setEnableHideAction(bool bIsEnable) final;
	virtual bool isEnableHideAction()  final;

	/** @brief	只有当允许入场动画，此函数才会调用 */
	virtual void ShowWithAction();

	/** @brief	只有当允许出场动画，此函数才会调用 */
	virtual void HideWithAction();

	virtual UIViewControllerDelegate* getDelegate() { return m_pDelegate; }

	/**
	 * @brief	设置是否允许代理传播UIView相关事件到UIManager中，在一个控制器中有多个显示视图时，
	 * 			只有允许有一个主的显示视图，这时子视图不需要向UIManager传播事件
	 * 			默认开启
	 *
	 * @param	bIsEnabled	true if this object is enabled.
	 */

	virtual void setEnableDelegate( bool bIsEnabled );
	virtual bool isEnableDelegate();

protected:

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
	virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
	virtual void onTouchEnded(Touch *touch, Event *unused_event) override;
	virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;

	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	virtual void addEventListener();
	virtual void removeEventListener();

protected:

	bool m_bIsShow;
	bool m_bIsEnableShowAction;
	bool m_bIsEnableHideAction;
	UIViewControllerDelegate* m_pDelegate;
	bool m_bIsEnableDelegate;

	//事件监听
	EventListenerTouchOneByOne* m_pEventListener;
};

UI_END
