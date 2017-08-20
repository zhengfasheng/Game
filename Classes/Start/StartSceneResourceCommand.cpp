#include "StartSceneResourceCommand.h"
#include "ResourceDelegate.h"
#include "SceneType.h"
#include "Resource.h"
#include "SoundHelper.h"

const static float TOTAL_RESOURCE = 6.0f;

StartSceneResourceCommand::StartSceneResourceCommand(ResourceDelegate* pDelegate)
	:ResourceCommand(pDelegate,SceneType::Start)
	, m_nCurrentFinish(0)
{

}

StartSceneResourceCommand::~StartSceneResourceCommand()
{

}

void StartSceneResourceCommand::unloadResourceStart()
{
	//释放资源 
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_menu);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_logo);
}

void StartSceneResourceCommand::loadResourceStart()
{
	m_nCurrentFinish = 0;
	m_resources.clear();
	m_resources.push_back(s_ship01);
	m_resources.push_back(s_menu);
	m_resources.push_back(s_logo);
	m_resources.push_back(s_cocos2dx);
	m_resources.push_back(s_menuTitle);
	m_resources.push_back(s_arial14);

	Director::getInstance()->getScheduler()->schedule([this](float dt){
		if ( m_nCurrentFinish < m_resources.size() )
		{
			Director::getInstance()->getTextureCache()->addImageAsync(m_resources[m_nCurrentFinish], CC_CALLBACK_1(StartSceneResourceCommand::onLoading, this, m_resources[m_nCurrentFinish].data()));
		}
		else
		{
			if ( m_nCurrentFinish > m_resources.size() )
			{
				//完成加载 
				Director::getInstance()->getScheduler()->unschedule("Load_Start_Resource_Timer", Director::getInstance());
				loadResourceComplete();
			}
			else
			{
				m_nCurrentFinish++;
			}
		}
	}, Director::getInstance(), 0.5f, CC_REPEAT_FOREVER, 0, false, "Load_Start_Resource_Timer");

	//为了方便，写一个宏了
//#define IMPLEMENT_ADD_IMAGE_ASYNC( resName )\
	//Director::getInstance()->getTextureCache()->addImageAsync(resName, CC_CALLBACK_1(StartSceneResourceCommand::onLoading, this, resName))\

	//IMPLEMENT_ADD_IMAGE_ASYNC(s_bg01);//game
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_ship01);//common
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_menu);//start
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_logo);//start
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_cocos2dx);//common
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_gameOver);//gameover
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_menuTitle);//common
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_enemy);//game
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_flare);//game
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_bullet);//game
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_explosion);//game
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_explode1);//game
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_explode2);//game
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_explode3);//game
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_hit);//game
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_arial14);//common
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_pause);//game
	//IMPLEMENT_ADD_IMAGE_ASYNC(s_play);//game

	//加载plist
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_bullet_plist);
	
	//预加载音乐与音效
	SoundHelper::getInstance()->preloadAudio();
	SoundHelper::getInstance()->preloadBackgroundMusic();
}

void StartSceneResourceCommand::onLoading(Texture2D* pTexture, const char* szResourceName)
{
	do
	{
		m_nCurrentFinish++;
		//加载完成
		loadResourceProgress(m_nCurrentFinish, m_resources.size());

	} while (0);
}

