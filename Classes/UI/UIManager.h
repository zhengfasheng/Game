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
 *  Summary:UI������ ����Ի���Ĵ��������٣���ʾ���ؼ�ui�¼��ķַ�
 *  
 ******************************************************************************/
#pragma once
#include "common.h"
#include "Dialog.h"
#include "SceneDelegate.h"

class UIManager : public SceneDelegate
{
	UIManager();
	IMPLEMENT_SINGLETON(UIManager);
	~UIManager();
public:
#pragma region ���⹫��ʹ��
	void ShowDialog(DialogID id);
	void HideDialog(DialogID id);
	void ShowOrHideDialog(DialogID id);

	/**
	 * @brief	Gets a state.
	 *
	 * @param	id		 	The identifier.
	 * @param	bIsCreate	(Optional) true ���Ҳ���ʱ�����Զ�����һ��
	 *
	 * @return	null if it fails, else the state.
	 */

	Dialog* GetDialog(DialogID id , bool bIsCreate = true );
	const std::string getDialogViewName( DialogID id);
	void ShowTips(const std::string& szContent);
	void ShowMessageBox();
	template< class T1, class T2, class T3, class T4>
	void SendEvent(DialogID id, const std::string& szEventName, T1 p1, T2 p2, T3 p3, T4 p4)
	{
		if (id > DialogID::Min && id < DialogID::Max)
		{
			auto it = m_dialogs.find(id);
			if (it == m_dialogs.end())
			{
				return;
			}
			auto pDlg = it->second;
			if (!pDlg)
				return;
			pDlg->OnEvent(szEventName, p1, p2, p3, p4,DialogDelegate::EventType::Game);
		}
		//�㲥���ж���
		else if (id == DialogID::Max)
		{
			for (auto it = m_dialogs.begin(); it != m_dialogs.end(); ++it)
			{
				auto pDlg = it->second;
				if (pDlg)
				{
					pDlg->OnEvent(szEventName, p1, p2, p3, p4,DialogDelegate::EventType::Game);
				}
			}
		}
	}

	template<class T1, class T2, class T3 >
	void SendEvent(DialogID id, const std::string& szEventName, T1 p1, T2 p2, T3 p3)
	{
		SendEvent(id, szEventName, p1, p2, p3, 0);
	}

	template<class T1, class T2>
	void SendEvent(DialogID id, const std::string& szEventName, T1 p1, T2 p2)
	{
		SendEvent(id, szEventName, p1, p2, 0);
	}

	template<class T1>
	void SendEvent(DialogID id, const std::string& szEventName, T1 p1)
	{
		SendEvent(id, szEventName, p1, 0);
	}

	void SendEvent(DialogID id, const std::string& szEventName)
	{
		SendEvent(id, szEventName, 0);
	}
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
	Dialog* Create(DialogID id);
	void WillShow(Dialog* pDialog);
	void DidShow(Dialog* pDialog);
	void WillHide(Dialog* pDialog);
	void DidHide(Dialog* pDialog);
	void Destory(DialogID id);
	void Destory();

#pragma endregion ˽��

private:

	std::map<DialogID, Dialog*> m_dialogs;
	friend class Dialog;
};