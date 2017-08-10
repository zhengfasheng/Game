#include "HallScene.h"
#include "UIManager.h"
#include "CurrentInfo.h"

void HallScene::DidEnter()
{
	UIManager::getInstance()->ShowDialog(DialogID::HallMain);
	UIManager::getInstance()->ShowDialog(DialogID::HallBottom);
	UIManager::getInstance()->ShowDialog(DialogID::HallActivity);
	UIManager::getInstance()->SendEvent(DialogID::HallBottom, UIEvent::EVENT_USER_INFO_CHANGE, CurrentInfo::getInstance()->getUserInfo().getAccount(), CurrentInfo::getInstance()->getUserInfo().getName(), CurrentInfo::getInstance()->getUserInfo().getChips());
}

