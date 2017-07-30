#include "HallUserInfoView.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "LoginConnector.h"

HallUserInfoView::HallUserInfoView()
{

}

HallUserInfoView::~HallUserInfoView()
{

}

bool HallUserInfoView::init(UIViewDelegate* pDelegate)
{
	bool bRet = false;
	do
	{
		using namespace cocos2d::ui;
		CC_BREAK_IF(!UIView::init(pDelegate));
		auto rootNode = CSLoader::createNode("RoleInfo.csb");
		CC_BREAK_IF(!rootNode);
		addChild(rootNode);

		auto pChange = (Button*)rootNode->getChildByName("Change");
		auto pClose = (Button*)rootNode->getChildByName("Close");
		m_pAccount = (Text*)rootNode->getChildByName("Account");
		m_pChips = (Text*)rootNode->getChildByName("Chips");
		m_pName = (Text*)rootNode->getChildByName("Name");

		pChange->addClickEventListener(CC_CALLBACK_1(HallUserInfoView::onChange, this));
		pClose->addClickEventListener(CC_CALLBACK_1(HallUserInfoView::onClose, this));
		this->setPosition(Director::getInstance()->getWinSize() / 2);

		bRet = true;
	} while (0);
	return bRet;
}

void HallUserInfoView::setAccount(const std::string& szAccount)
{
	if ( m_pAccount )
	{
		m_pAccount->setString(szAccount);
	}
}

void HallUserInfoView::setUserName(const std::string& szName)
{
	if ( m_pName )
	{
		m_pName->setString(szName);
	}
}

void HallUserInfoView::setChips(const int nChips)
{
	if ( m_pChips )
	{
		m_pChips->setString(toString(nChips));
	}
}

void HallUserInfoView::onClose(Ref* pSender)
{
	this->Hide();
}


void HallUserInfoView::onChange(Ref* pSender)
{
	LoginConnector::getInstance()->sendApplyChipsChange();
}




//
//class BaseUser;
//
//class Proxy
//{
//public:
//	Proxy(BaseUser* bu)
//	{
//		m_isLive = true;
//		t = bu;
//	}
//
//	BaseUser* ptr()
//	{
//		if (m_isLive)
//		{
//			return t;
//		}
//		return 0;
//	}
//
//	void release()
//	{
//		m_isLive = false;
//	}
//
//private:
//	bool m_isLive = false;
//	BaseUser* t = 0;
//};
//
//class BaseUser
//{
//public:
//	BaseUser()
//	{
//	};
//	virtual ~BaseUser()
//	{
//		m_proxy->release();
//	}
//
//	std::shared_ptr<Proxy> CreateProxy()
//	{
//		if (0 == m_proxy)
//		{
//			m_proxy = std::make_shared<Proxy>(this);
//		}
//		return m_proxy;
//	}
//private:
//	std::shared_ptr<Proxy> m_proxy = 0;
//
//}








