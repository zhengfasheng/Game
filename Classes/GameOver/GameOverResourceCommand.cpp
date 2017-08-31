#include "GameOverResourceCommand.h"
#include "Resource.h"

const std::string LOAD_RESOURCE_TIME = "Load_About_Resource_Timer";
GameOverResourceCommand::GameOverResourceCommand(ResourceDelegate* pDelegate, SceneType type)
	:ResourceCommand(pDelegate, type)
{

}

GameOverResourceCommand::~GameOverResourceCommand()
{
	Director::getInstance()->getScheduler()->unschedule(LOAD_RESOURCE_TIME, Director::getInstance());
}

void GameOverResourceCommand::onLoading(Texture2D* pTexture, const char* szResourceName)
{
	m_nCurrentFinish++;
	//加载完成
	loadResourceProgress(m_nCurrentFinish, m_resources.size());
}

void GameOverResourceCommand::unloadResourceStart()
{
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_gameOver);
	unloadResourceComplete();
}

void GameOverResourceCommand::loadResourceStart()
{
	m_nCurrentFinish = 0;
	m_resources.clear();
	m_resources.push_back(s_gameOver);

	Director::getInstance()->getScheduler()->schedule([this](float dt){
		if (m_nCurrentFinish < m_resources.size())
		{
			Director::getInstance()->getTextureCache()->addImageAsync(m_resources[m_nCurrentFinish], CC_CALLBACK_1(GameOverResourceCommand::onLoading, this, m_resources[m_nCurrentFinish].data()));
		}
		else
		{
			if (m_nCurrentFinish > m_resources.size())
			{
				//完成加载 
				Director::getInstance()->getScheduler()->unschedule(LOAD_RESOURCE_TIME, Director::getInstance());
				loadResourceComplete();
			}
			else
			{
				m_nCurrentFinish++;
			}
		}
	}, Director::getInstance(), 0.5f, CC_REPEAT_FOREVER, 0, false, LOAD_RESOURCE_TIME);
}
