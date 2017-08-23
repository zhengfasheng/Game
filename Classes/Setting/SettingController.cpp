#include "SettingController.h"
#include "SettingView.h"
#include "SceneManager.h"
#include "SoundHelper.h"

SettingController::SettingController()
{

}

SettingController::~SettingController()
{

}

UIView* SettingController::createView(UIViewControllerDelegate* pDelegate)
{
	return SettingView::create(pDelegate);
}

IMPLEMENT_HANDLER(SettingController, onGoBack)
{
	SceneManager::getInstance()->GoToScene(SceneType::Start);
}

IMPLEMENT_HANDLER(SettingController, onBackgroundMusicChange)
{
	SoundHelper::getInstance()->setBackgroundMusic(p1.asBool());
}

IMPLEMENT_HANDLER(SettingController, onAudioChange)
{
	SoundHelper::getInstance()->setAudio(p1.asBool());
}