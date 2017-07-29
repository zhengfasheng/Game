#include "Message.h"

Message::Message( )
	: m_nID((int)MessageType::Invalid)
	,m_bIsSuccess(false)
{

}

Message::~Message()
{

}

Message* Message::clone()
{
	return new Message(*this);
}


ApplyLogin::ApplyLogin()
{
	m_nID = (int)MessageType::ApplyLogin;
}

ApplyLogin::~ApplyLogin()
{

}

Message* ApplyLogin::clone()
{
	return new ApplyLogin(*this);
}

ResponseLogin::ResponseLogin()
	:m_szAccount("")
	, m_szName("")
	, m_nChips(0)
{
	m_nID = (int)MessageType::ApplyLogin;
}

ResponseLogin::~ResponseLogin()
{

}

Message* ResponseLogin::clone()
{
	return new ResponseLogin(*this);
}

ApplyChipsChang::ApplyChipsChang()
{
	m_nID = (int)MessageType::ChipsChange;
}

ApplyChipsChang::~ApplyChipsChang()
{

}

Message* ApplyChipsChang::clone()
{
	return new ApplyChipsChang(*this);
}

ResponseChipsChange::ResponseChipsChange()
{
	m_nID = (int)MessageType::ChipsChange;
}

ResponseChipsChange::~ResponseChipsChange()
{

}

Message* ResponseChipsChange::clone()
{
	return new ResponseChipsChange(*this);
}
