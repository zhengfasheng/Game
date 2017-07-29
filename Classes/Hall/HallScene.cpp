#include "HallScene.h"
#include "UIManager.h"
#include "CurrentInfo.h"

void HallScene::DidEnter()
{
	UIManager::getInstance()->ShowState(StateID::HallMain);
	UIManager::getInstance()->ShowState(StateID::HallBottom);
	UIManager::getInstance()->ShowState(StateID::HallActivity);
	UIManager::getInstance()->SendEvent(StateID::HallBottom, UIEvent::EVENT_USER_INFO_CHANGE,CurrentInfo::getInstance()->getAccount(),CurrentInfo::getInstance()->getName(),CurrentInfo::getInstance()->getChips());
}

