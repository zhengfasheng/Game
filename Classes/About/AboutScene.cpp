#include "AboutScene.h"
#include "UIManager.h"

void AboutScene::DidEnter()
{
	UIManager::getInstance()->Show(ControllerID::About);
}

AboutScene::AboutScene()
{

}

AboutScene::~AboutScene()
{

}

