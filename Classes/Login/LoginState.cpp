#include "LoginState.h"
#include "LoginView.h"
#include "GameProcedure.h"
#include "UIManager.h"
#include "LoginConnector.h"

LoginState::LoginState()
{

}

LoginState::~LoginState()
{

}

UIView* LoginState::createView(UIViewDelegate* pDelegate)
{
	return LoginView::create(pDelegate);
}

IMPLEMENT_HANDLER(LoginState,onLoginResult)
{
	auto bIsSuccess = p1.asBool();
	if ( bIsSuccess )
	{
		m_pManager->ShowTips("Login Success");
		GameProcedure::getInstance()->GoToHall();
	}
	else
	{
		m_pManager->ShowTips("Login Failure");
	}
}

IMPLEMENT_HANDLER(LoginState, onApplyLogin)
{
	LoginConnector::getInstance()->sendApplyLogin(p1.asString(), p2.asString());
}

