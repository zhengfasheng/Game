#include "State.h"
#include "UIManager.h"
#include "UIView.h"

State::State()
	:m_pManager(nullptr)
	, m_id(StateID::Invalid)
	, m_pView(nullptr)
{

}

State::~State()
{
	m_pManager = nullptr;
	m_id = StateID::Invalid;
	CC_SAFE_RELEASE_NULL(m_pView);
}

bool State::Init(UIManager* pManager, StateID stateID)
{
	m_pManager = pManager;
	m_id = stateID;
	return true;
}

void State::RemoveFromParent()
{
	if ( getView() )
	{
		getView()->removeFromParent();
	}
}

void State::ShowState(StateID id)
{
	m_pManager->ShowState(id);
}

void State::HideState(StateID id)
{
	m_pManager->HideState(id);
}

void State::ShowView()
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

void State::HideView()
{
	if ( m_pView )
	{
		m_pView->Hide();
	}
}

bool State::IsViewShow()
{
	if ( m_pView )
	{
		return m_pView->IsShow();
	}
	return false;
}

UIView* State::getView()
{
	return m_pView;
}

void State::WillShow()
{
	m_pManager->WillShow(this);
}

void State::DidShow()
{
	m_pManager->DidShow(this);
}

void State::WillHide()
{
	m_pManager->WillHide(this);
}

void State::DidHide()
{
	m_pManager->DidHide(this);
}

