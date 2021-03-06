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
 *  Date:2017/7/28 1:00
 *
 *  Summary: 视图控制器，接收外部事件，处理数据，更新显示视图 ， 接收用户事件，处理用户事件，如果点击，双击等
 *    
 ******************************************************************************/
#pragma once
#include "ControllerType.h"
#include "GValue.h"
#include "UIViewControllerDelegate.h"
#include "UIEvent.h"
#include "UIDefine.h"

class UIManager;
UI_BEGIN
class UIView;
class UIViewController : public UIViewControllerDelegate
{
public:
	UIViewController();
	virtual ~UIViewController();
#pragma region 父类不可子类重写部分

	/**
	 * @brief	初始化State
	 *
	 * @param [in,out]	pManager	If non-null, the manager.
	 * @param	stateID				Identifier for the state.
	 */

	virtual bool Init(UIManager* pManager, ControllerID id) ;

	/** @brief	从父节点上移除 */
	virtual void RemoveFromParent() final;

	/**
	 * @brief	当需要显示其它界面时，可通过StateID 显示其它界面
	 *
	 * @param	id	The identifier.
	 */

	virtual void ShowState(ControllerID id) final;

	/**
	 * @brief	当需要关闭其它界面时，可通过StateID 关闭其它界面
	 *
	 * @param	id	The identifier.
	 */

	virtual void HideState(ControllerID id) final;

	virtual void ShowView() final;

	virtual void HideView() final;

	virtual bool IsViewShow() final;

	virtual UIView* getView()final;

	virtual ControllerID getStateID() final { return m_id; }

	/**
	 * @brief	需要添加到Scene的哪一个层次上
	 *
	 * @return	The scene z coordinate order.
	 */

	virtual int getSceneZOrder() { return SceneZOder::Normal; }

	/**
	 * @brief	在界面关闭时是否需要把整个State给移除 默认为true
	 *
	 * @return	true 当界面关闭会释放整个State
	 */

	virtual bool IsDestroyOnHideView() { return true; }

#pragma endregion 父类不可子类重写部分

#pragma region 子类可重写部分
	/**
	* @brief	创建State时需要子类提供UIView的创建
	*
	* @return	null if it fails, else the new view.
	*/

	virtual UIView* createView(UIViewControllerDelegate* pDelegate) { return nullptr; }

	virtual void WillShow() override;
	virtual void DidShow() override;
	virtual void WillHide() override;
	virtual void DidHide() override;
	virtual void OnReturnKey() override{};
#pragma endregion 子类可重写部分
protected:
	UIManager* m_pManager;
	ControllerID m_id;
	UIView* m_pView;
};

UI_END