#include "GameOverController.h"
#include "GameOverView.h"
#include "SceneManager.h"

GameOverController::GameOverController()
{

}

GameOverController::~GameOverController()
{

}

UIView* GameOverController::createView(UIViewControllerDelegate* pDelegate)
{
	return GameOverView::create(pDelegate);
}

IMPLEMENT_HANDLER(GameOverController, onGoBack)
{
	SceneManager::getInstance()->GoToScene(SceneType::Start);
}

IMPLEMENT_HANDLER(GameOverController, onTryAgin)
{
	SceneManager::getInstance()->GoToScene(SceneType::Game);
}
