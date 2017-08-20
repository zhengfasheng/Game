#include "LoginHelper.h"
#include "Message.h"
#include "UIManager.h"
#include "CurrentInfo.h"
#include "cocos2d.h"
USING_NS_CC;

void initLoginConnector()
{
	LoginHelper::getInstance();
}
LoginHelper::LoginHelper()
{

}

LoginHelper::~LoginHelper()
{

}

void LoginHelper::onReceiveServerResponse(Message* pMsg)
{
	if (!pMsg) return;
	switch ((MessageType)pMsg->m_nID )
	{
	case MessageType::ApplyLogin:
	{
		auto pResponse = dynamic_cast<ResponseLogin*>(pMsg);
		if ( pMsg->m_bIsSuccess )
		{
			CurrentInfo::getInstance()->getUserInfo().setAccount(pResponse->m_szAccount);
			CurrentInfo::getInstance()->getUserInfo().setChips(pResponse->m_nChips);
			CurrentInfo::getInstance()->getUserInfo().setName(pResponse->m_szName);
		}
		//UIManager::getInstance()->SendEvent(ControllerID::Login,UIEvent::EVENT_LOGIN_RESULT,pMsg->m_bIsSuccess);
	}
	break;
	case MessageType::ChipsChange:
	{
		CCLOGERROR("-----------------%d-----",pMsg->m_nID);
		auto pResponse = dynamic_cast<ResponseChipsChange*>(pMsg);
		if (pMsg->m_bIsSuccess)
		{
			CurrentInfo::getInstance()->getUserInfo().setChips(pResponse->m_nChips);
		}
		//UIManager::getInstance()->SendEvent(ControllerID::Max, UIEvent::EVENT_USER_CHIPS_CHANGE, pMsg->m_bIsSuccess,pResponse->m_nChips);
	}
	break;
	default:
		break;
	}
}

void LoginHelper::sendApplyLogin(const std::string& szAccount, const std::string& szPwd)
{
	ApplyLogin* pMsg = new ApplyLogin();
	pMsg->m_szAccount = szAccount;
	pMsg->m_szPwd = szPwd;
	//sendServerRequest(pMsg);
	
	sendHttpRequest<UserInfo>(pMsg, [](const UserInfo& info){
		CurrentInfo::getInstance()->setUserInfo(info);
		//UIManager::getInstance()->SendEvent(ControllerID::Login, UIEvent::EVENT_LOGIN_RESULT, true);
	});

}

void LoginHelper::sendApplyChipsChange()
{
	CCLOGERROR("======================");
	auto pMsg = new ApplyChipsChang();
	sendServerRequest(pMsg);
}



