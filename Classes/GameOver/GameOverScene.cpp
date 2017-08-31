#include "GameOverScene.h"
#include "UIManager.h"

GameOverScene::GameOverScene()
{

}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::DidEnter()
{
	UIManager::getInstance()->Show(ControllerID::GameOver);
}

