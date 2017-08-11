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
 *  Summary: ��ͼ�������������ⲿ�¼����������ݣ�������ʾ��ͼ �� �����û��¼��������û��¼�����������˫����
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
#pragma region ���಻��������д����

	/**
	 * @brief	��ʼ��State
	 *
	 * @param [in,out]	pManager	If non-null, the manager.
	 * @param	stateID				Identifier for the state.
	 */

	virtual bool Init(UIManager* pManager, ControllerID id) final;

	/** @brief	�Ӹ��ڵ����Ƴ� */
	virtual void RemoveFromParent() final;

	/**
	 * @brief	����Ҫ��ʾ��������ʱ����ͨ��StateID ��ʾ��������
	 *
	 * @param	id	The identifier.
	 */

	virtual void ShowState(ControllerID id) final;

	/**
	 * @brief	����Ҫ�ر���������ʱ����ͨ��StateID �ر���������
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
	 * @brief	��Ҫ���ӵ�Scene����һ�������
	 *
	 * @return	The scene z coordinate order.
	 */

	virtual int getSceneZOrder() { return SceneZOder::Normal; }

	/**
	 * @brief	�ڽ���ر�ʱ�Ƿ���Ҫ������State���Ƴ� Ĭ��Ϊtrue
	 *
	 * @return	true ������رջ��ͷ�����State
	 */

	virtual bool IsDestroyOnHideView() { return true; }

#pragma endregion ���಻��������д����

#pragma region �������д����
	/**
	* @brief	����Stateʱ��Ҫ�����ṩUIView�Ĵ���
	*
	* @return	null if it fails, else the new view.
	*/

	virtual UIView* createView(UIViewControllerDelegate* pDelegate) { return nullptr; }

	virtual void WillShow() override;
	virtual void DidShow() override;
	virtual void WillHide() override;
	virtual void DidHide() override;
	virtual void OnReturnKey() override{};
#pragma endregion �������д����
protected:
	UIManager* m_pManager;
	ControllerID m_id;
	UIView* m_pView;
};

UI_END