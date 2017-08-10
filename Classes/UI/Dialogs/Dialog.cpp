#include "Dialog.h"
#include "UIManager.h"
#include "UIView.h"

Dialog::Dialog()
	:m_pManager(nullptr)
	, m_id(DialogID::Invalid)
	, m_pView(nullptr)
{

}

Dialog::~Dialog()
{
	m_pManager = nullptr;
	m_id = DialogID::Invalid;
	CC_SAFE_RELEASE_NULL(m_pView);
}

bool Dialog::Init(UIManager* pManager, DialogID stateID)
{
	m_pManager = pManager;
	m_id = stateID;
	return true;
}

void Dialog::RemoveFromParent()
{
	if ( getView() )
	{
		getView()->removeFromParent();
	}
}

void Dialog::ShowState(DialogID id)
{
	m_pManager->ShowDialog(id);
}

void Dialog::HideState(DialogID id)
{
	m_pManager->HideDialog(id);
}

void Dialog::ShowView()
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

void Dialog::HideView()
{
	if ( m_pView )
	{
		m_pView->Hide();
	}
}

bool Dialog::IsViewShow()
{
	if ( m_pView )
	{
		return m_pView->IsShow();
	}
	return false;
}

UIView* Dialog::getView()
{
	return m_pView;
}

void Dialog::WillShow()
{
	m_pManager->WillShow(this);
}

void Dialog::DidShow()
{
	m_pManager->DidShow(this);
}

void Dialog::WillHide()
{
	m_pManager->WillHide(this);
}

void Dialog::DidHide()
{
	m_pManager->DidHide(this);
}

