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
 *  Summary:UI������ ������ͼ���������������٣���ʾ���ؼ�ui�¼��ķַ�
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
#pragma region ���⹫��ʹ��
	void Show(ControllerID id);
	void Hide(ControllerID id);
	void ShowOrHide(ControllerID id);

	/**
	 * @brief	Gets a Controller.
	 *
	 * @param	id		 	The identifier.
	 * @param	bIsCreate	(Optional) true ���Ҳ���ʱ�����Զ�����һ��.
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
		//�㲥���ж���
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
	 * @brief	��ȡcontroller�е�ֵ
	 * 			ʹ�����壬���ȡ��ֵ���ǻ����������ͣ�
	 * 			һ��Ҫ����һ��const ���ã���Ҫ���ؾֲ������ĵ�ַ
	 * 			��֤��ַ����Ч��
	 * 			
	 * 			
	 *			���´����ʹ��
	 * 			class Test;
	 * 			//��ʹ�Ѿ���һ��ȫ�ֱ���Test g_value��������һ��controller�еı���
	 * 			GetValue()
	 * 			{
	 * 				auto value = g_value;
	 * 				return (void*)&value;
	 * 			}
	 * 			
	 *          ��ȷ��ʹ��Ӧ����
	 *          GetValue()
	 * 			{
	 * 				return (void*)&g_value;
	 * 			}
	 * 			����
	 *			GetValue()
	 * 			{
	 * 				auto& value = g_value;
	 * 				return (void*)&value;
	 * 			}
	 *
	 * @param	id		   	controller id
	 * @param	szValueName	��Ҫȡ��һ������
	 *
	 * @return	The value.
	 */

	GValue GetValue(ControllerID id, const std::string& szValueName);

#pragma endregion ���⹫��ʹ��

#pragma region ��������ʵ��
	virtual void Init(IScene* pScene);

	virtual void OnEnter(IScene* pScene);

	virtual void OnEnterTransitionDidFinish(IScene* pScene);

	virtual void OnExit(IScene* pScene);

	virtual void OnExitTransitionDidStart(IScene* pScene);
#pragma endregion ��������ʵ��
	
private:
#pragma region ˽��
	UIViewController* Create(ControllerID id);
	void WillShow(UIViewController* pDialog);
	void DidShow(UIViewController* pDialog);
	void WillHide(UIViewController* pDialog);
	void DidHide(UIViewController* pDialog);
	void Destory(ControllerID id);
	void Destory();

#pragma endregion ˽��

private:

	std::map<ControllerID, UIViewController*> m_controllers;
	friend class UIViewController;
};