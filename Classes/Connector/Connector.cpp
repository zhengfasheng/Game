#include "Connector.h"
#include "Message.h"
#include "LocalServer.h"

Connector::Connector()
{
	
}

Connector::~Connector()
{

}

//������ʱֻ�Ǹ�ģ�⣬
void Connector::sendServerRequest(Message* pMsg)
{
	LocalServer::getInstance()->onReceiveClientServerRequest(pMsg,this);
}

void Connector::onReceiveServerResponse(Message* pMsg)
{
	
}

void Connector::sendHttpRequest(Message* pMsg)
{
	LocalServer::getInstance()->onReceiveClientHttpRequest(pMsg, this);
}

void Connector::onReceiveHttpResponse(Message* pMsg)
{
	
}

