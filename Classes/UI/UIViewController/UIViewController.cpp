#include "UIViewController.h"
#include "UIManager.h"
#include "UIView.h"

UI_BEGIN
UIViewController::UIViewController()
	:m_pManager(nullptr)
	, m_id(ControllerID::Invalid)
	, m_pView(nullptr)
{

}

UIViewController::~UIViewController()
{
	m_pManager = nullptr;
	m_id = ControllerID::Invalid;
	CC_SAFE_RELEASE_NULL(m_pView);
}

bool UIViewController::Init(UIManager* pManager, ControllerID stateID)
{
	m_pManager = pManager;
	m_id = stateID;
	return true;
}

void UIViewController::RemoveFromParent()
{
	if ( getView() )
	{
		getView()->removeFromParent();
	}
}

void UIViewController::ShowState(ControllerID id)
{
	m_pManager->Show(id);
}

void UIViewController::HideState(ControllerID id)
{
	m_pManager->Hide(id);
}

void UIViewController::ShowView()
{
	//如果没有view，先创建再显示
	if (!m_pView)
	{
		m_pView = createView(this);
		if ( m_pView )
		{
			m_pView->retain();
		}
	}

	if ( m_pView )
	{
		m_pView->Show();
	}
}

void UIViewController::HideView()
{
	if ( m_pView )
	{
		m_pView->Hide();
	}
}

bool UIViewController::IsViewShow()
{
	if ( m_pView )
	{
		return m_pView->IsShow();
	}
	return false;
}

UIView* UIViewController::getView()
{
	return m_pView;
}

void UIViewController::WillShow()
{
	m_pManager->WillShow(this);
}

void UIViewController::DidShow()
{
	m_pManager->DidShow(this);
}

void UIViewController::WillHide()
{
	m_pManager->WillHide(this);
}

void UIViewController::DidHide()
{
	m_pManager->DidHide(this);
}

UI_END
