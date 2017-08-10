#include "LoginView.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "ui/UIHelper.h"
#include "ui/UITextField.h"
#include "ui/UIEditBox/UIEditBox.h"

LoginView::LoginView()
	:m_pAccount(nullptr)
	, m_pPassword(nullptr)
{

}

LoginView::~LoginView()
{
	m_pAccount = nullptr;
	m_pPassword = nullptr;
}

bool LoginView::init(DialogDelegate* pDelegate)
{
	bool bRet = false;
	do 
	{
		using namespace cocos2d::ui;
		;
		CC_BREAK_IF(!UIView::init(pDelegate));
		auto rootNode = CSLoader::createNode("MainScene.csb");
		CC_BREAK_IF(!rootNode);
		addChild(rootNode);

		//auto pAccount = (TextField*)Helper::seekWidgetByName(rootNode,"Account");
		//auto pPassWord = (TextField*)Helper::seekWidgetByName(rootNode,"Password");
		auto pAccount = (TextField*)rootNode->getChildByName("Account");
		auto pPassWord = (TextField*)rootNode->getChildByName("Password");
		CC_BREAK_IF(!pAccount || !pPassWord);

		auto pAccountEditBox = EditBox::create(Size(300, 36), "green_edit.png");
		pAccountEditBox->setAnchorPoint(pAccount->getAnchorPoint());
		pAccountEditBox->setColor(pAccount->getColor());
		pAccountEditBox->setPosition(pAccount->getPosition());
		pAccountEditBox->setFontSize(pAccount->getFontSize());
		pAccountEditBox->setInputFlag(EditBox::InputFlag::SENSITIVE);
		rootNode->addChild(pAccountEditBox);

		auto pPassWordEditBox = EditBox::create(Size(300, 36), "green_edit.png");
		pPassWordEditBox->setAnchorPoint(pPassWord->getAnchorPoint());
		pPassWordEditBox->setColor(pPassWord->getColor());
		pPassWordEditBox->setPosition(pPassWord->getPosition());
		pPassWordEditBox->setFontSize(pPassWord->getFontSize());
		rootNode->addChild(pPassWordEditBox);

		pAccount->removeFromParent();
		pPassWord->removeFromParent();

		m_pAccount = pAccountEditBox;
		m_pPassword = pPassWordEditBox;

		m_pAccount->setText("666");
		m_pPassword->setText("666888");

		auto pLogin = (Button*)rootNode->getChildByName("Login");
		CC_BREAK_IF(!pLogin);
		pLogin->addClickEventListener(CC_CALLBACK_1(LoginView::onLogin, this));

		bRet = true;
	} while (0);
	return bRet;
}

void LoginView::onLogin(Ref* pSender)
{
	if ( m_pProtocol )
	{
		m_pProtocol->SendEvent(UIEvent::EVENT_APPLY_LOGIN,m_pAccount->getText(),m_pPassword->getText());
	}
}

