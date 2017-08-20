#include "ResourceCommandFactory.h"
#include "StartSceneResourceCommand.h"

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
		pCommand = new StartSceneResourceCommand(pDelegate);
		break;
	default:
		break;
	}
	return pCommand;
}

