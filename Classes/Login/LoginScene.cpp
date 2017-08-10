#include "LoginScene.h"
#include "UIManager.h"

USING_NS_CC;

void LoginScene::DidEnter()
{
	UIManager::getInstance()->ShowDialog(DialogID::Login);
}
