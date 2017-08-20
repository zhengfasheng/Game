#include "StartScene.h"
#include "UIManager.h"

void StartScene::DidEnter()
{
	UIManager::getInstance()->Show(ControllerID::Start);
}

