#include "StartScene.h"
#include "UIManager.h"
#include "SoundHelper.h"

void StartScene::DidEnter()
{
	if ( !SoundHelper::getInstance()->isPlayingBackgroundMusic() )
	{
		SoundHelper::getInstance()->playBackgroundMusic(SoundHelper::BackgroundMusicType::BackMusic);
	}
	
	UIManager::getInstance()->Show(ControllerID::Start);
}

StartScene::StartScene()
{

}

StartScene::~StartScene()
{

}

