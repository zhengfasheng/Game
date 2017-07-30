#include "LoginConnector.h"
#include "Message.h"
#include "UIManager.h"
#include "CurrentInfo.h"
#include "cocos2d.h"
USING_NS_CC;
LoginConnector::LoginConnector()
{

}

LoginConnector::~LoginConnector()
{

}

void LoginConnector::onReceiveServerResponse(Message* pMsg)
{
	if (!pMsg) return;
	switch ((MessageType)pMsg->m_nID )
	{
	case MessageType::ApplyLogin:
	{
		auto pResponse = dynamic_cast<ResponseLogin*>(pMsg);
		if ( pMsg->m_bIsSuccess )
		{
			CurrentInfo::getInstance()->setAccount(pResponse->m_szAccount);
			CurrentInfo::getInstance()->setChips(pResponse->m_nChips);
			CurrentInfo::getInstance()->setName(pResponse->m_szName);
		}
		UIManager::getInstance()->SendEvent(StateID::Login,UIEvent::EVENT_LOGIN_RESULT,pMsg->m_bIsSuccess);
	}
	break;
	case MessageType::ChipsChange:
	{
		CCLOGERROR("-----------------%d-----",pMsg->m_nID);
		auto pResponse = dynamic_cast<ResponseChipsChange*>(pMsg);
		if (pMsg->m_bIsSuccess)
		{
			CurrentInfo::getInstance()->setChips(pResponse->m_nChips);
		}
		UIManager::getInstance()->SendEvent(StateID::Max, UIEvent::EVENT_USER_CHIPS_CHANGE, pMsg->m_bIsSuccess,pResponse->m_nChips);
	}
	break;
	default:
		break;
	}
}

void LoginConnector::onReceiveHttpResponse(Message* pMsg)
{

	
}

void LoginConnector::sendApplyLogin(const std::string& szAccount, const std::string& szPwd)
{
	ApplyLogin* pMsg = new ApplyLogin();
	pMsg->m_szAccount = szAccount;
	pMsg->m_szPwd = szPwd;
	sendServerRequest(pMsg);
}

void LoginConnector::sendApplyChipsChange()
{
	CCLOGERROR("======================");
	auto pMsg = new ApplyChipsChang();
	sendServerRequest(pMsg);
}


