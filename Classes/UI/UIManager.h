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
 *  Summary:UI管理器
 *  
 ******************************************************************************/
#pragma once
#include "common.h"
#include "State.h"
#include "SceneDelegate.h"

class UIManager : public SceneDelegate
{
	UIManager();
	IMPLEMENT_SINGLETON(UIManager);
	~UIManager();
public:
#pragma region 对外公开使用
	void ShowState(StateID id);
	void HideState(StateID id);
	void ShowOrHideState(StateID id);

	/**
	 * @brief	Gets a state.
	 *
	 * @param	id		 	The identifier.
	 * @param	bIsCreate	(Optional) true 当找不到时，会自动创建一个
	 *
	 * @return	null if it fails, else the state.
	 */

	State* GetState(StateID id , bool bIsCreate = true );
	const std::string getStateViewName( StateID id);
	void ShowTips(const std::string& szContent);
	void ShowMessageBox();
	template< class T1, class T2, class T3, class T4>
	void SendEvent(StateID id, const std::string& szEventName, T1 p1, T2 p2, T3 p3, T4 p4)
	{
		if (id > StateID::Min && id < StateID::Max)
		{
			auto it = m_states.find(id);
			if (it == m_states.end())
			{
				return;
			}
			auto pState = it->second;
			if (!pState)
				return;
			pState->OnEvent(szEventName, p1, p2, p3, p4,UIViewDelegate::EventType::Game);
		}
		//广播所有对象
		else if (id == StateID::Max)
		{
			for (auto it = m_states.begin(); it != m_states.end(); ++it)
			{
				auto pState = it->second;
				if (pState)
				{
					pState->OnEvent(szEventName, p1, p2, p3, p4,UIViewDelegate::EventType::Game);
				}
			}
		}
	}

	template<class T1, class T2, class T3 >
	void SendEvent(StateID id, const std::string& szEventName, T1 p1, T2 p2, T3 p3)
	{
		SendEvent(id, szEventName, p1, p2, p3, 0);
	}

	template<class T1, class T2>
	void SendEvent(StateID id, const std::string& szEventName, T1 p1, T2 p2)
	{
		SendEvent(id, szEventName, p1, p2, 0);
	}

	template<class T1>
	void SendEvent(StateID id, const std::string& szEventName, T1 p1)
	{
		SendEvent(id, szEventName, p1, 0);
	}

	void SendEvent(StateID id, const std::string& szEventName)
	{
		SendEvent(id, szEventName, 0);
	}
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
	State* CreateState(StateID id);
	void WillShow(State* pState);
	void DidShow(State* pState);
	void WillHide(State* pState);
	void DidHide(State* pState);
	void Destory(StateID id);
	void Destory();

#pragma endregion 私有

private:

	std::map<StateID, State*> m_states;
	friend class State;
};