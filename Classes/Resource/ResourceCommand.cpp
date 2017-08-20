#include "ResourceCommand.h"
#include "ResourceDelegate.h"

ResourceCommand::ResourceCommand( ResourceDelegate* pDelegate , SceneType type )
	:m_pDelegate(pDelegate)
	, m_sceneType(type)
{

}

ResourceCommand::~ResourceCommand()
{
	m_pDelegate = nullptr;
}

void ResourceCommand::unloadResourceStart()
{
	if ( m_pDelegate )
	{
		m_pDelegate->unloadResourceStart(getSceneType());
	}
}

void ResourceCommand::unloadResourceComplete()
{
	if ( m_pDelegate )
	{
		m_pDelegate->unloadResourceComplete(getSceneType());
	}
}

void ResourceCommand::loadResourceStart()
{
	if ( m_pDelegate )
	{
		m_pDelegate->loadResourceStart(getSceneType());
	}
}

void ResourceCommand::loadResourceComplete()
{
	if ( m_pDelegate )
	{ 
		m_pDelegate->loadResourceComplete(getSceneType());
	}
}

void ResourceCommand::loadResourceProgress(unsigned int nLoaded, unsigned int nTotal)
{
	if ( m_pDelegate )
	{
		m_pDelegate->loadResourceProgress(getSceneType(),nLoaded, nTotal);
	}
}

const SceneType& ResourceCommand::getSceneType() const
{
	return m_sceneType;
}
