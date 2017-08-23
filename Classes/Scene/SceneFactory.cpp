#include "SceneFactory.h"
#include "StartScene.h"
#include "AboutScene.h"
#include "SettingScene.h"
#include "GameScene.h"

SceneFactory::SceneFactory()
{

}

SceneFactory::~SceneFactory()
{

}

IScene* SceneFactory::create(SceneDelegate* pDelegate, SceneType type)
{
	IScene* pScene = nullptr;
	switch (type)
	{
	case SceneType::Start:
		return StartScene::create(pDelegate);
		break;
	case SceneType::Game:
		return GameScene::create(pDelegate);
		break;
	case SceneType::About:
		return AboutScene::create(pDelegate);
		break;
	case SceneType::Setting:
		return SettingScene::create(pDelegate);
		break;
	default:
		break;
	}
	return pScene;
}

