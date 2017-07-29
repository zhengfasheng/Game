#include "Connector.h"
#include "Message.h"
#include "LocalServer.h"

Connector::Connector()
{
	
}

Connector::~Connector()
{

}

//这里暂时只是个模拟，
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

