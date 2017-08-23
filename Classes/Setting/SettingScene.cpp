#include "SettingScene.h"
#include "UIManager.h"

SettingScene::SettingScene()
{

}

SettingScene::~SettingScene()
{

}

void SettingScene::DidEnter()
{
	UIManager::getInstance()->Show(ControllerID::Setting);
}

