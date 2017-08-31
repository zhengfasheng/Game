#include "UIView.h"

UI_BEGIN
UIView::UIView()
	:m_pDelegate(nullptr)
	, m_bIsShow(false)
	, m_bIsEnableHideAction(true)
	, m_bIsEnableShowAction(true)
	, m_bIsEnableDelegate(true)
	, m_pEventListener(nullptr)
{

}

UIView::~UIView()
{
	m_pDelegate = nullptr;
	m_bIsShow = false;
	removeEventListener();
}

bool UIView::init(UIViewControllerDelegate* pDelegate)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init() || !pDelegate);
		setVisible(false);
		m_pDelegate = pDelegate;
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
		setVisible(true);
		if ( isEnableDelegate() ) m_pDelegate->WillShow();
		ShowEnd();
		if ( isEnableDelegate() ) m_pDelegate->DidShow();
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
		if (isEnableDelegate()) m_pDelegate->WillHide();
		HideEnd();
		if (isEnableDelegate()) m_pDelegate->DidHide();
	}
}

void UIView::ShowEnd()
{

}

void UIView::HideEnd()
{
	m_bIsShow = false;
	setVisible(false);
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
	if (isEnableDelegate()) m_pDelegate->WillShow();
	m_bIsShow = true;
	setVisible(true);
	this->setOpacity(0);

	auto pAction = Sequence::createWithTwoActions(FadeIn::create(0.5f), CallFunc::create([this](){
		if (isEnableDelegate()) m_pDelegate->DidShow();
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
	if (isEnableDelegate()) m_pDelegate->WillHide();
	this->retain();
	auto pAction = Sequence::createWithTwoActions(FadeOut::create(0.5f), CallFunc::create([this](){
		m_bIsShow = false;
		HideEnd();
		this->release();
		if (isEnableDelegate()) m_pDelegate->DidHide();
	}));
	pAction->setTag(HIDE_ACTION_TAG);
	this->runAction(pAction);
}

void UIView::setEnableDelegate(bool bIsEnabled)
{
	m_bIsEnableDelegate = bIsEnabled;
}

bool UIView::isEnableDelegate()
{
	return m_bIsEnableDelegate;
}

bool UIView::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void UIView::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void UIView::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void UIView::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

void UIView::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{

	}
}

void UIView::addEventListener()
{
	m_pEventListener = EventListenerTouchOneByOne::create();
	if (m_pEventListener)
	{
		m_pEventListener->setEnabled(true);
		m_pEventListener->setSwallowTouches(true);
		//ÉèÖÃ»Øµ÷
		m_pEventListener->onTouchBegan = CC_CALLBACK_2(UIView::onTouchBegan, this);
		m_pEventListener->onTouchMoved = CC_CALLBACK_2(UIView::onTouchMoved, this);
		m_pEventListener->onTouchEnded = CC_CALLBACK_2(UIView::onTouchEnded, this);
		m_pEventListener->onTouchCancelled = CC_CALLBACK_2(UIView::onTouchCancelled, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pEventListener, this);
	}
}

void UIView::removeEventListener()
{
	if ( m_pEventListener )
	{
		_eventDispatcher->removeEventListener(m_pEventListener);
	}
	m_pEventListener = nullptr;
}

UI_END
