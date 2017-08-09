#include "Connector.h"
#include "Message.h"
#include "LocalServer.h"
#include "IParser.h"

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

void Connector::onReceiveHttpResponse(Message* pMsg)
{
	
}

