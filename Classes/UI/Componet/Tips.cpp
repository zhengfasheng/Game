#include "Tips.h"
#include "ui\UIScale9Sprite.h"
#include "UIManager.h"

Tips* Tips::create(const std::string& szContent)
{
	auto pRet = new Tips;
	if ( pRet && pRet->init(szContent) )
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool Tips::init(const std::string& szContent)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!UIView::init(this));

		auto pContent = Label::create(szContent, "", 24);
		this->setContentSize(pContent->getContentSize() + Size(50,20));

		this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);

		this->setPosition(Size(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height));

		auto pBackground = ui::Scale9Sprite::create("server_list_roll_button.png");
		pBackground->setContentSize(this->getContentSize());
		this->addChild(pBackground);
		pBackground->addChild(pContent);
		pBackground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		pBackground->setPosition(Vec2::ZERO);
		pContent->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		pContent->setPosition(pBackground->getContentSize() / 2);

		setEnableShowAction(true);
		bRet = true;
	} while (0);
	return bRet;
}

void Tips::ShowWithAction()
{
	m_pProtocol->WillShow();
	m_bIsShow = true;
	this->setOpacity(0);
	Director::getInstance()->getRunningScene()->addChild(this, SceneZOder::Notice);
	this->retain();
	this->runAction(Sequence::create(MoveTo::create(0.2f,Vec2(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height - this->getContentSize().height - 10)),DelayTime::create(1.0f),FadeOut::create(0.2f),CallFunc::create([this](){
		m_pProtocol->DidShow();
		ShowEnd();
		this->removeFromParent();
		this->release();
	}),nullptr));
}

