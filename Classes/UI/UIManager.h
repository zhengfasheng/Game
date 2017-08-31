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
 *  Date:2017/7/28 0:39
 *
 *  Summary:UI管理器 负责视图控制器创建与销毁，显示隐藏及ui事件的分发
 *  
 ******************************************************************************/
#pragma once
#include "common.h"
#include "UIViewController.h"
#include "SceneDelegate.h"
#include "Any.h"
USING_UI;
class UIManager : public SceneDelegate
{
	UIManager();
	IMPLEMENT_SINGLETON(UIManager);
	~UIManager();
public:
#pragma region 对外公开使用
	void Show(ControllerID id);
	void Hide(ControllerID id);
	void ShowOrHide(ControllerID id);

	/**
	 * @brief	Gets a Controller.
	 *
	 * @param	id		 	The identifier.
	 * @param	bIsCreate	(Optional) true 当找不到时，会自动创建一个.
	 *
	 * @return	null if it fails, else the state.
	 */

	UIViewController* GetController(ControllerID id , bool bIsCreate = true );
	const std::string GetControllerViewName( ControllerID id);
	void ShowTips(const std::string& szContent);
	void ShowMessageBox();
	template< class T1, class T2, class T3, class T4>
	void SendEvent(ControllerID id, const std::string& szEventName, T1 p1, T2 p2, T3 p3, T4 p4)
	{
		if (id > ControllerID::Min && id < ControllerID::Max)
		{
			auto it = m_controllers.find(id);
			if (it == m_controllers.end())
			{
				return;
			}
			auto pDlg = it->second;
			if (!pDlg)
				return;
			pDlg->OnEvent(szEventName, p1, p2, p3, p4);
		}
		//广播所有对象
		else if (id == ControllerID::Max)
		{
			for (auto it = m_controllers.begin(); it != m_controllers.end(); ++it)
			{
				auto pDlg = it->second;
				if (pDlg)
				{
					pDlg->OnEvent(szEventName, p1, p2, p3, p4);
				}
			}
		}
	}

	template<class T1, class T2, class T3 >
	void SendEvent(ControllerID id, const std::string& szEventName, T1 p1, T2 p2, T3 p3)
	{
		SendEvent(id, szEventName, p1, p2, p3, 0);
	}

	template<class T1, class T2>
	void SendEvent(ControllerID id, const std::string& szEventName, T1 p1, T2 p2)
	{
		SendEvent(id, szEventName, p1, p2, 0);
	}

	template<class T1>
	void SendEvent(ControllerID id, const std::string& szEventName, T1 p1)
	{
		SendEvent(id, szEventName, p1, 0);
	}

	void SendEvent(ControllerID id, const std::string& szEventName)
	{
		SendEvent(id, szEventName, 0);
	}

	/**
	 * @brief	获取controller中的值
	 * 			使用陷阱，如果取的值不是基本数量类型，
	 * 			一定要返回一个const 引用，不要返回局部变量的地址
	 * 			保证地址的有效性
	 * 			
	 * 			
	 *			如下错误的使用
	 * 			class Test;
	 * 			//假使已经有一个全局变量Test g_value，或者是一个controller中的变量
	 * 			GetValue()
	 * 			{
	 * 				auto value = g_value;
	 * 				return (void*)&value;
	 * 			}
	 * 			
	 *          正确的使用应该是
	 *          GetValue()
	 * 			{
	 * 				return (void*)&g_value;
	 * 			}
	 * 			或者
	 *			GetValue()
	 * 			{
	 * 				auto& value = g_value;
	 * 				return (void*)&value;
	 * 			}
	 *
	 * @param	id		   	controller id
	 * @param	szValueName	需要取哪一个变量
	 *
	 * @return	The value.
	 */

	GValue GetValue(ControllerID id, const std::string& szValueName);

#pragma endregion 对外公开使用

#pragma region 场景代理实现
	virtual void Init(IScene* pScene);

	virtual void OnEnter(IScene* pScene);

	virtual void OnEnterTransitionDidFinish(IScene* pScene);

	virtual void OnExit(IScene* pScene);

	virtual void OnExitTransitionDidStart(IScene* pScene);
#pragma endregion 场景代理实现
	
private:
#pragma region 私有
	UIViewController* Create(ControllerID id);
	void WillShow(UIViewController* pDialog);
	void DidShow(UIViewController* pDialog);
	void WillHide(UIViewController* pDialog);
	void DidHide(UIViewController* pDialog);
	void Destory(ControllerID id);
	void Destory();

#pragma endregion 私有

private:

	std::map<ControllerID, UIViewController*> m_controllers;
	friend class UIViewController;
};