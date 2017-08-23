#include "GameResourceCommand.h"
#include "Resource.h"
#include "commontools.h"
#include "GameConfig.h"

const static std::string LOAD_RESOURCE_TIMER = "Load_Start_Resource_Timer";

GameResourceCommand::GameResourceCommand(ResourceDelegate* pDelegate, SceneType type /* = SceneType::Game */)
	:ResourceCommand(pDelegate, type)
	, m_nCurrentFinish(0)
{

}

GameResourceCommand::~GameResourceCommand()
{
	Director::getInstance()->getScheduler()->unschedule(LOAD_RESOURCE_TIMER, Director::getInstance());
}

void GameResourceCommand::unloadResourceStart()
{
	//释放资源 
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_bg01);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_gameOver);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_enemy);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_flare);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_bullet);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_explosion);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_explode1);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_explode2);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_explode3);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_hit);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_pause);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_play);
	unloadResourceComplete();
}

void GameResourceCommand::loadResourceStart()
{
	m_nCurrentFinish = 0;
	m_resources.clear();
	m_resources.push_back(s_bg01);
	m_resources.push_back(s_gameOver);
	m_resources.push_back(s_enemy);
	m_resources.push_back(s_flare);
	m_resources.push_back(s_bullet);
	m_resources.push_back(s_explosion);
	m_resources.push_back(s_explode1);
	m_resources.push_back(s_explode2);
	m_resources.push_back(s_explode3);
	m_resources.push_back(s_hit);
	m_resources.push_back(s_pause);
	m_resources.push_back(s_play);

	Director::getInstance()->getScheduler()->schedule([this](float dt){
		if (m_nCurrentFinish < m_resources.size())
		{
			Director::getInstance()->getTextureCache()->addImageAsync(m_resources[m_nCurrentFinish], CC_CALLBACK_1(GameResourceCommand::onLoading, this, m_resources[m_nCurrentFinish].data()));
		}
		else
		{
			if (m_nCurrentFinish > m_resources.size())
			{
				//完成加载 
				Director::getInstance()->getScheduler()->unschedule(LOAD_RESOURCE_TIMER, Director::getInstance());
				loadResourceComplete();
			}
			else
			{
				m_nCurrentFinish++;
			}
		}
	}, Director::getInstance(), 0.2f, CC_REPEAT_FOREVER, 0, false, LOAD_RESOURCE_TIMER);

	//加载plist
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_bullet_plist);
}

void GameResourceCommand::onLoading(Texture2D* pTexture, const char* szResourceName)
{
	m_nCurrentFinish++;

	//敌机
	if (szResourceName == s_enemy)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_Enemy_plist, getTextureForKey(s_enemy));
	}
	//开始与暂停按钮
	if (szResourceName == s_pause || szResourceName == s_play)
	{
		auto pTexture = getTextureForKey(szResourceName);
		auto pSpriteFrame = SpriteFrame::createWithTexture(pTexture, Rect(0, 0, pTexture->getContentSize().width, pTexture->getContentSize().height));
		SpriteFrameCache::getInstance()->addSpriteFrame(pSpriteFrame, szResourceName);
	}

	//爆炸特效资源
	if (szResourceName == s_explosion)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_explosion_plist, getTextureForKey(szResourceName));

		Vector<SpriteFrame*> FrameVec;
		char str[64] = { 0 };
		// 这个sprintf真心很强大啊
		for (int i = 1; i < 35; ++i) {
			sprintf(str, "explosion_%02d.png", i);
			CCLOG("%s", str);
			auto pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			FrameVec.pushBack(pFrame);
		}
		auto pAnimation = CCAnimation::createWithSpriteFrames(FrameVec, 0.04f);

		// 帧动画命名
		AnimationCache::getInstance()->addAnimation(pAnimation, g_szExplosion);
	}

	//加载完成
	loadResourceProgress(m_nCurrentFinish, m_resources.size());
}
