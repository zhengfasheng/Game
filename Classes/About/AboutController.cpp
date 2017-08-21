#include "AboutController.h"
#include "AboutView.h"
#include "SceneManager.h"

AboutController::AboutController()
{

}

AboutController::~AboutController()
{

}

UIView* AboutController::createView(UIViewControllerDelegate* pDelegate)
{
	return AboutView::create(pDelegate);
}

IMPLEMENT_HANDLER(AboutController, onGoBack)
{
	SceneManager::getInstance()->GoToScene(SceneType::Start);
}