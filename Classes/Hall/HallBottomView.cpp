#include "HallBottomView.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "GameProcedure.h"
#include "UIManager.h"


HallBottomView::HallBottomView()
	:m_pAccount(nullptr)
	, m_pChips(nullptr)
	, m_pName(nullptr)
{

}

HallBottomView::~HallBottomView()
{

}

bool HallBottomView::init(UIViewDelegate* pDelegate)
{
	bool bRet = false;
	do
	{
		using namespace cocos2d::ui;
		;
		CC_BREAK_IF(!UIView::init(pDelegate));
		auto rootNode = CSLoader::createNode("HallBottom.csb");
		CC_BREAK_IF(!rootNode);
		addChild(rootNode);

		auto pInfo = (Button*)rootNode->getChildByName("roleinfo");
		auto pGoBack = (Button*)rootNode->getChildByName("GoBack");
		m_pAccount = (Text*)rootNode->getChildByName("accout");
		m_pChips = (Text*)rootNode->getChildByName("Chips");
		m_pName = (Text*)rootNode->getChildByName("name");

		pInfo->addClickEventListener(CC_CALLBACK_1(HallBottomView::onInfo, this));
		pGoBack->addClickEventListener(CC_CALLBACK_1(HallBottomView::onGoback, this));

		bRet = true;
	} while (0);
	return bRet;
}

void HallBottomView::onGoback(Ref* pSender)
{
	GameProcedure::getInstance()->GoToLogin();
}

void HallBottomView::onInfo(Ref* pSender)
{
	UIManager::getInstance()->ShowState(StateID::HallUserInfo);
}

void HallBottomView::setAccount(const std::string& szAccount)
{
	if ( m_pAccount )
	{
		m_pAccount->setString(szAccount);
	}
}

void HallBottomView::setUserName(const std::string& szName)
{
	if ( m_pName )
	{
		m_pName->setString(szName);
	}
}

void HallBottomView::setChips(const int nChips)
{
	if ( m_pChips )
	{
		m_pChips->setString(toString(nChips));
	}
}

