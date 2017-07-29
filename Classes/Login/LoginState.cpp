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
#include "Any.h"

void onApplyLogin11(const GValue& p1, const GValue& p2)
{
	auto szAccount = p1.asString();// boost::any_cast<std::string>(p1);
	auto szPwd = p2.asString();//boost::any_cast<std::string>(p2);
	auto pAccount = (int*)p2.asPointer();
	//LoginConnector::getInstance()->sendApplyLogin(szAccount, szPwd);
}

void onApplyLogin( const GValue& p1 , const GValue& p2)
{
	::onApplyLogin11(p1, p2);
	//auto& szAccount = boost::any_cast<std::string>(p1);
	//auto& szPwd = boost::any_cast<std::string>(p2);
	//LoginConnector::getInstance()->sendApplyLogin(szAccount,szPwd);
}

IMPLEMENT_HANDLER(LoginState, onApplyLogin)
{
	::onApplyLogin(p1, p2);
}

