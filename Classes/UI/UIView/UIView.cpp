#include "UIView.h"

UI_BEGIN
UIView::UIView()
	:m_pProtocol(nullptr)
	, m_bIsShow(false)
	, m_bIsEnableHideAction(true)
	, m_bIsEnableShowAction(true)
{

}

UIView::~UIView()
{
	m_pProtocol = nullptr;
	m_bIsShow = false;
}

bool UIView::init(UIViewControllerDelegate* pProtocol)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init() || !pProtocol );
		m_pProtocol = pProtocol;
		bRet = true;
	} while (0);
	return bRet;
}

bool UIView::IsShow()
{
	return m_bIsShow;
}

void UIView::Show()
{
	if ( m_bIsEnableShowAction )
	{
		ShowWithAction();
	}
	else
	{
		m_bIsShow = true;
		m_pProtocol->WillShow();
		ShowEnd();
		m_pProtocol->DidShow();
	}
}

void UIView::Hide()
{
	if ( m_bIsEnableHideAction )
	{
		HideWithAction();
	}
	else
	{
		m_pProtocol->WillHide();
		HideEnd();
		m_pProtocol->DidHide();
	}
}

void UIView::ShowEnd()
{

}

void UIView::HideEnd()
{
	m_bIsShow = false;
}

void UIView::setEnableShowAction(bool bIsEnable)
{
	m_bIsEnableShowAction = bIsEnable;
}

bool UIView::isEnableShowAction()
{
	return m_bIsEnableShowAction;
}

void UIView::setEnableHideAction(bool bIsEnable)
{
	m_bIsEnableHideAction = bIsEnable;
}

bool UIView::isEnableHideAction()
{
	return m_bIsEnableHideAction;
}

void UIView::ShowWithAction()
{
	if ( this->getActionByTag(SHOW_ACTION_TAG) )
	{
		CCLOGERROR("UIView Showing");
		return;
	}
	m_pProtocol->WillShow();
	m_bIsShow = true;
	this->setScale(0.2f);

	auto pAction = Sequence::createWithTwoActions(ScaleTo::create(0.5f, 1.0f), CallFunc::create([this](){
		m_pProtocol->DidShow();
		ShowEnd();
		this->release();
	}));
	pAction->setTag(SHOW_ACTION_TAG);
	this->retain();
	this->runAction(pAction);
}

void UIView::HideWithAction()
{
	if ( this->getActionByTag(HIDE_ACTION_TAG) )
	{
		CCLOGERROR("UIView hiding");
		return;
	}
	m_pProtocol->WillHide();
	this->retain();
	auto pAction = Sequence::createWithTwoActions(FadeOut::create(0.5f), CallFunc::create([this](){
		m_bIsShow = false;
		HideEnd();
		this->release();
		m_pProtocol->DidHide();
	}));
	pAction->setTag(HIDE_ACTION_TAG);
	this->runAction(pAction);
}

void UIView::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		
	}
}

UI_END
