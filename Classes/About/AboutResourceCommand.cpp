#include "AboutResourceCommand.h"
#include "Resource.h"

AboutResourceCommand::AboutResourceCommand(ResourceDelegate* pDelegate,SceneType type)
	:ResourceCommand(pDelegate,type)
{

}

AboutResourceCommand::~AboutResourceCommand()
{
	Director::getInstance()->getScheduler()->unschedule("Load_About_Resource_Timer", Director::getInstance());
}

void AboutResourceCommand::onLoading(Texture2D* pTexture, const char* szResourceName)
{
	m_nCurrentFinish++;
	//加载完成
	loadResourceProgress(m_nCurrentFinish, m_resources.size());
}

void AboutResourceCommand::unloadResourceStart()
{
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_logo);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_menuTitle);
	unloadResourceComplete();
}

void AboutResourceCommand::loadResourceStart()
{
	m_nCurrentFinish = 0;
	m_resources.clear();
	m_resources.push_back(s_logo);
	m_resources.push_back(s_menuTitle);

	Director::getInstance()->getScheduler()->schedule([this](float dt){
		if (m_nCurrentFinish < m_resources.size())
		{
			Director::getInstance()->getTextureCache()->addImageAsync(m_resources[m_nCurrentFinish], CC_CALLBACK_1(AboutResourceCommand::onLoading, this, m_resources[m_nCurrentFinish].data()));
		}
		else
		{
			if (m_nCurrentFinish > m_resources.size())
			{
				//完成加载 
				Director::getInstance()->getScheduler()->unschedule("Load_About_Resource_Timer", Director::getInstance());
				loadResourceComplete();
			}
			else
			{
				m_nCurrentFinish++;
			}
		}
	}, Director::getInstance(), 0.5f, CC_REPEAT_FOREVER, 0, false, "Load_About_Resource_Timer");
}

