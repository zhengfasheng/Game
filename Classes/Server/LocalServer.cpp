#include "LocalServer.h"
#include "cocos2d.h"
#include "common.h"
#include "Message.h"
#include "Connector.h"

USING_NS_CC;
std::string makeTimerName()
{
	auto clock = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(clock);
	auto szTimer = toString(time);
	return szTimer;
}

LocalServer::LocalServer()
{
	start();
}

LocalServer::~LocalServer()
{
	for (auto it = m_queue.begin(); it != m_queue.end(); ++it )
	{
		if ( it->m_pMsg )
		{
			delete it->m_pMsg;
			it->m_pMsg = nullptr;
		}
	}
	m_queue.clear();
}

void LocalServer::onReceiveClientServerRequest(Message* pMsg, Connector* pConnector)
{
	auto pTemp = pMsg->clone();
	m_queue.push_back(MassageInfo(pTemp,pConnector));
}

void LocalServer::sendServerResponse(Message* pMsg, Connector* pConnector)
{
	if ( pConnector && pMsg )
	{
		Message* pResponse = nullptr;
		switch ( (MessageType)pMsg->m_nID )
		{
		case MessageType::ApplyLogin:
		{
			auto pRequest = dynamic_cast<ApplyLogin*>(pMsg);
			bool bIsSuccess = false;
			if ( pRequest )
			{
				bIsSuccess = pRequest->m_szAccount == "666" && pRequest->m_szPwd == "666888";
			}
			auto pTemp = new ResponseLogin();
			pTemp->m_nID = (int)MessageType::ApplyLogin;
			pTemp->m_bIsSuccess = bIsSuccess;
			pTemp->m_nChips = 10000;
			pTemp->m_szAccount = "ooxx";
			pTemp->m_szName = "jjjjjjjjjjjj";
			pResponse = pTemp;
		}
		break;
		case MessageType::ChipsChange:
		{
			auto pTemp = new ResponseChipsChange();
			pTemp->m_bIsSuccess = true;
			pTemp->m_nChips = cocos2d::random(100, 100000000);
			pResponse = pTemp;
		}
		break;

		default:
			break;
		}
		
		pConnector->onReceiveServerResponse(pResponse);
		if ( pResponse ) delete pResponse;
		pResponse = nullptr;
	}

	if ( pMsg )
	{
		delete pMsg;
	}
	pMsg = nullptr;
	m_queue.pop_front();
}

void LocalServer::onReceiveClientHttpRequest(Message* pMsg, Connector* pConnector)
{

}

void LocalServer::sendHttpResponse(Message* pMsg, Connector* pConnector)
{

}

void LocalServer::start()
{
	Director::getInstance()->getScheduler()->schedule([this](float dt){

		if ( m_queue.empty())
		{
			return;
		}
		this->sendServerResponse(m_queue.front().m_pMsg,m_queue.front().m_pConnector);
	}, Director::getInstance(), 2, CC_REPEAT_FOREVER, false, false, makeTimerName());
}

