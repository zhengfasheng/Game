#include "StartScene.h"
#include "UIManager.h"
#include "SoundHelper.h"
#include "CurrentPlayerInfo.h"

void StartScene::DidEnter()
{
	if ( !SoundHelper::getInstance()->isPlayingBackgroundMusic() )
	{
		SoundHelper::getInstance()->playBackgroundMusic(SoundHelper::BackgroundMusicType::BackMusic);
	}
	CurrentPlayerInfo::getInstance()->readPlayerInformation();
	UIManager::getInstance()->Show(ControllerID::Start);
}

StartScene::StartScene()
{

}

StartScene::~StartScene()
{

}

