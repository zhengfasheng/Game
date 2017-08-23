#include "ResourceCommandFactory.h"
#include "StartSceneResourceCommand.h"
#include "AboutResourceCommand.h"
#include "SettingResourceCommand.h"
#include "GameResourceCommand.h"

ResourceCommandFactory::ResourceCommandFactory()
{

}

ResourceCommandFactory::~ResourceCommandFactory()
{

}

ResourceCommand* ResourceCommandFactory::create(ResourceDelegate* pDelegate , SceneType type)
{
	ResourceCommand* pCommand = nullptr;
	switch (type)
	{
	case SceneType::Invalid:
		return nullptr;
		break;
	case SceneType::Resource:
		return nullptr;
		break;
	case SceneType::Start:
		pCommand = new StartSceneResourceCommand(pDelegate, type);
		break;
	case SceneType::About:
		pCommand = new AboutResourceCommand(pDelegate, type);
		break;
	case SceneType::Setting:
		pCommand = new SettingResourceCommand(pDelegate, type);
		break;
	case SceneType::Game:
		pCommand = new GameResourceCommand(pDelegate, type);
	default:
		break;
	}
	return pCommand;
}

