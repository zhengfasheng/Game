#include "SceneFactory.h"
#include "StartScene.h"

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
		return StartScene::create(pDelegate, type);
		break;
	case SceneType::Game:
		break;
	case SceneType::About:
		break;
	case SceneType::Setting:
		break;
	default:
		break;
	}
	return pScene;
}

