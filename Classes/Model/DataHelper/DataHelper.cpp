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

//������ʱֻ�Ǹ�ģ�⣬
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

