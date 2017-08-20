#include "StartController.h"
#include "StartView.h"
#include "SceneManager.h"


StartController::StartController()
{

}

StartController::~StartController()
{

}

UIView* StartController::createView(UIViewControllerDelegate* pDelegate)
{
	return StartView::create(pDelegate);
}

IMPLEMENT_HANDLER(StartController,onNewGame)
{
	SceneManager::getInstance()->GoToScene(SceneType::Game);
}

IMPLEMENT_HANDLER(StartController,onAbout)
{
	SceneManager::getInstance()->GoToScene(SceneType::About);
}

IMPLEMENT_HANDLER(StartController,onSetting)
{
	SceneManager::getInstance()->GoToScene(SceneType::Setting);
}