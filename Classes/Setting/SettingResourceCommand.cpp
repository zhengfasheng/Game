#include "SettingResourceCommand.h"
#include "Resource.h"

const std::string LOAD_RESOUREC_TIME = "Load_Setting_Resource_Timer";
SettingResourceCommand::SettingResourceCommand(ResourceDelegate* pDelegate,SceneType type /* = SceneType::Setting */)
	:ResourceCommand(pDelegate,type)
{

}

SettingResourceCommand::~SettingResourceCommand()
{
	Director::getInstance()->getScheduler()->unschedule(LOAD_RESOUREC_TIME, Director::getInstance());
}

void SettingResourceCommand::onLoading(Texture2D* pTexture, const char* szResourceName)
{
	m_nCurrentFinish++;
	//加载完成
	loadResourceProgress(m_nCurrentFinish, m_resources.size());
}

void SettingResourceCommand::unloadResourceStart()
{
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_menuTitle);
	unloadResourceComplete();
}

void SettingResourceCommand::loadResourceStart()
{
	m_nCurrentFinish = 0;
	m_resources.clear();
	m_resources.push_back(s_menuTitle);

	Director::getInstance()->getScheduler()->schedule([this](float dt){
		if (m_nCurrentFinish < m_resources.size())
		{
			Director::getInstance()->getTextureCache()->addImageAsync(m_resources[m_nCurrentFinish], CC_CALLBACK_1(SettingResourceCommand::onLoading, this, m_resources[m_nCurrentFinish].data()));
		}
		else
		{
			if (m_nCurrentFinish > m_resources.size())
			{
				//完成加载 
				Director::getInstance()->getScheduler()->unschedule(LOAD_RESOUREC_TIME, Director::getInstance());
				loadResourceComplete();
			}
			else
			{
				m_nCurrentFinish++;
			}
		}
	}, Director::getInstance(), 0.5f, CC_REPEAT_FOREVER, 0, false, LOAD_RESOUREC_TIME);
}

