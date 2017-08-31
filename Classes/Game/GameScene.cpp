#include "GameScene.h"
#include "UIManager.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::DidEnter()
{
	UIManager::getInstance()->Show(ControllerID::Game);
}

