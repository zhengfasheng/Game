#include "HallScene.h"
#include "UIManager.h"
#include "CurrentInfo.h"

void HallScene::DidEnter()
{
	UIManager::getInstance()->Show(ControllerID::HallMain);
	UIManager::getInstance()->Show(ControllerID::HallBottom);
	UIManager::getInstance()->Show(ControllerID::HallActivity);
	UIManager::getInstance()->SendEvent(ControllerID::HallBottom, UIEvent::EVENT_USER_INFO_CHANGE, CurrentInfo::getInstance()->getUserInfo().getAccount(), CurrentInfo::getInstance()->getUserInfo().getName(), CurrentInfo::getInstance()->getUserInfo().getChips());
}

