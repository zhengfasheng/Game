#include "LoginDialog.h"
#include "LoginView.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "LoginHelper.h"

LoginDialog::LoginDialog()
{

}

LoginDialog::~LoginDialog()
{

}

UIView* LoginDialog::createView(DialogDelegate* pDelegate)
{
	return LoginView::create(pDelegate);
}

IMPLEMENT_HANDLER(LoginDialog,onLoginResult)
{
	auto bIsSuccess = p1.asBool();
	if ( bIsSuccess )
	{
		m_pManager->ShowTips("Login Success");
		SceneManager::getInstance()->GoToScene(SceneType::Hall);
	}
	else
	{
		m_pManager->ShowTips("Login Failure");
	}
}

IMPLEMENT_HANDLER(LoginDialog, onApplyLogin)
{
	LoginHelper::getInstance()->sendApplyLogin(p1.asString(), p2.asString());
}

