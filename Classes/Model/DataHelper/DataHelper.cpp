#include "DataHelper.h"
#include "Message.h"
#include "LocalServer.h"
#include "IParser.h"

DataHelper::DataHelper()
{
	
}

DataHelper::~DataHelper()
{

}

//这里暂时只是个模拟，
void DataHelper::sendServerRequest(Message* pMsg)
{
	LocalServer::getInstance()->onReceiveClientServerRequest(pMsg,this);
}

void DataHelper::onReceiveServerResponse(Message* pMsg)
{
	
}

void DataHelper::onReceiveHttpResponse(Message* pMsg)
{
	
}

