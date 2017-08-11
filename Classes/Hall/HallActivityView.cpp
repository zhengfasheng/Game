#include "HallActivityView.h"
#include "cocostudio/ActionTimeline/CSLoader.h"

HallActivityView::HallActivityView()
{

}

HallActivityView::~HallActivityView()
{

}

bool HallActivityView::init(UIViewControllerDelegate* pDelegate)
{
	bool bRet = false;
	do
	{
		using namespace cocos2d::ui;
		;
		CC_BREAK_IF(!UIView::init(pDelegate));
		auto rootNode = CSLoader::createNode("HallActivity.csb");
		CC_BREAK_IF(!rootNode);
		addChild(rootNode);

		////auto pAccount = (TextField*)Helper::seekWidgetByName(rootNode,"Account");
		////auto pPassWord = (TextField*)Helper::seekWidgetByName(rootNode,"Password");
		//auto pAccount = (TextField*)rootNode->getChildByName("Account");
		//auto pPassWord = (TextField*)rootNode->getChildByName("Password");
		//CC_BREAK_IF(!pAccount || !pPassWord);

		//auto pAccountEditBox = EditBox::create(Size(300, 36), "green_edit.png");
		//pAccountEditBox->setAnchorPoint(pAccount->getAnchorPoint());
		//pAccountEditBox->setColor(pAccount->getColor());
		//pAccountEditBox->setPosition(pAccount->getPosition());
		//pAccountEditBox->setFontSize(pAccount->getFontSize());
		//pAccountEditBox->setInputFlag(EditBox::InputFlag::SENSITIVE);
		//rootNode->addChild(pAccountEditBox);

		//auto pPassWordEditBox = EditBox::create(Size(300, 36), "green_edit.png");
		//pPassWordEditBox->setAnchorPoint(pPassWord->getAnchorPoint());
		//pPassWordEditBox->setColor(pPassWord->getColor());
		//pPassWordEditBox->setPosition(pPassWord->getPosition());
		//pPassWordEditBox->setFontSize(pPassWord->getFontSize());
		//rootNode->addChild(pPassWordEditBox);

		//pAccount->removeFromParent();
		//pPassWord->removeFromParent();

		//m_pAccount = pAccountEditBox;
		//m_pPassword = pPassWordEditBox;

		//auto pLogin = (Button*)rootNode->getChildByName("Login");
		//CC_BREAK_IF(!pLogin);
		//pLogin->addClickEventListener(CC_CALLBACK_1(LoginView::onLogin, this));

		bRet = true;
	} while (0);
	return bRet;
}

