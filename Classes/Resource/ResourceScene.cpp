#include "ResourceScene.h"
#include "Resource.h"
#include "ResourceCommandFactory.h"
#include "SceneDelegate.h"
#include "Language.h"

ResourceScene::ResourceScene()
	:m_pLoadingBar(nullptr)
	, m_pShowLoadingText(nullptr)
	, m_fromSceneType(SceneType::Invalid)
	, m_toSceneType(SceneType::Invalid)
	, m_pFromSceneCommand(nullptr)
	, m_pToSceneCommand(nullptr)
{

}

ResourceScene::~ResourceScene()
{
	
}

ResourceScene* ResourceScene::create(SceneDelegate* pDelegate, SceneType fromSceneType , SceneType toSceneType)
{
	auto pRet = new ResourceScene;
	if ( pRet && pRet->init(pDelegate,fromSceneType,toSceneType) )
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool ResourceScene::init(SceneDelegate* pDelegate, SceneType fromSceneType, SceneType toSceneType)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!IScene::init(pDelegate,SceneType::Resource));
		
		auto pLayout = Layout::create();
		CC_BREAK_IF(!pLayout);
		this->addChild(pLayout);
		auto winSize = Director::getInstance()->getWinSize();
		pLayout->setContentSize(winSize);
		pLayout->setBackGroundImage(s_loading);

		//创建一个加载进度条
		m_pLoadingBar = LoadingBar::create(s_loadingbar);
		CC_BREAK_IF(!m_pLoadingBar);
		m_pLoadingBar->setScale9Enabled(true);
		m_pLoadingBar->setCapInsets(Rect::ZERO);
		m_pLoadingBar->setContentSize(Size(winSize.width - 50, 13));
		m_pLoadingBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		m_pLoadingBar->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		m_pLoadingBar->setDirection(LoadingBar::Direction::LEFT);
		m_pLoadingBar->setPercent(0);
		pLayout->addChild(m_pLoadingBar);

		//显示进度标签
		m_pShowLoadingText = Text::create(Language::getInstance()->getString("resource.read_resource"), Language::getInstance()->getLocalFont(), 20);
		CC_BREAK_IF(!m_pShowLoadingText);
		m_pShowLoadingText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		m_pShowLoadingText->setPosition(
			Vec2(winSize.width / 2, m_pLoadingBar->getPositionY() + m_pLoadingBar->getContentSize().height));

		pLayout->addChild(m_pShowLoadingText);

		m_fromSceneType = fromSceneType;
		m_toSceneType = toSceneType;

		m_pFromSceneCommand = ResourceCommandFactory::getInstance()->create(this, fromSceneType);
		m_pToSceneCommand = ResourceCommandFactory::getInstance()->create(this, toSceneType);

		bRet = true;
	} while (0);
	return bRet;
}

void ResourceScene::DidEnter()
{
	// 先释放前一场景的资源
	if ( m_pFromSceneCommand )
	{
		//前面有场景需要释放资源
		m_pFromSceneCommand->unloadResourceStart();
	}
	// 再加载后一场景的资源
	else
	{
		CCLOG("Are you sure prev scene don't need unload resource , the scene type is %d", (int)m_fromSceneType);
		if ( m_pDelegate )
		{
			m_pDelegate->unloadResourceComplete(m_fromSceneType);
		}
		//前面不需要进行资源的释放的操作，直接加载后一场景的资源 
		if ( m_pToSceneCommand )
		{
			m_pToSceneCommand->loadResourceStart();
		}
		else
		{
			CCLOG("Are you sure don't need load resource , the scene type is %d", (int)m_toSceneType);
			if ( m_pDelegate )
			{
				m_pDelegate->loadResourceComplete(m_toSceneType);
			}
		}
	}
}

void ResourceScene::unloadResourceStart(SceneType type)
{
	if ( m_pDelegate )
	{
		m_pDelegate->unloadResourceStart(type);
	}
	setLoadingString(Language::getInstance()->getString("resource.unload_resource_start_" + toString((int)type)));
	setLoadingBarVisible(false);
}

void ResourceScene::unloadResourceComplete(SceneType type)
{
	if ( m_pDelegate )
	{
		m_pDelegate->unloadResourceComplete(type);
	}
	setLoadingString(Language::getInstance()->getString("resource.unload_resource_complete_" + toString((int)type)));
	setLoadingBarVisible(false);
	//前一场景资源释放完成，加载 后一场景的资源
	if (m_pToSceneCommand)
	{
		m_pToSceneCommand->loadResourceStart();
		setLoadingString(Language::getInstance()->getString("resource.load_resource_start_" + toString((int)type)));
		setLoadingBarVisible(true);
		setLoadingBarProgress(0.0f);
	}
	else
	{
		CCLOG("Are you sure don't need load resource , the scene type is %d", (int)m_toSceneType);
		if (m_pDelegate)
		{
			m_pDelegate->loadResourceComplete(m_toSceneType);
		}
	}
}

void ResourceScene::loadResourceStart(SceneType type)
{
	if ( m_pDelegate )
	{
		m_pDelegate->loadResourceStart(type);
	}
	setLoadingString(Language::getInstance()->getString("resource.load_resource_start_" + toString((int)type)));
	setLoadingBarVisible(true);
	setLoadingBarProgress(0.0f);
}

void ResourceScene::loadResourceComplete(SceneType type)
{
	if ( m_pDelegate )
	{
		m_pDelegate->loadResourceComplete(type);
	}
	setLoadingString(Language::getInstance()->getString("resource.load_resource_complete_" + toString((int)type)));
}

void ResourceScene::loadResourceProgress(SceneType type, unsigned int nLoadedCount, unsigned int nTotal)
{
	if ( m_pDelegate )
	{
		m_pDelegate->loadResourceProgress(type, nLoadedCount, nTotal);
	}
	setLoadingString(Language::getInstance()->getStringWithParam("resource.loading_resource_" + toString((int)type) , (int)nLoadedCount,(int)nTotal));
	float fProgress = (float)nLoadedCount / (float)nTotal;
	setLoadingBarProgress(fProgress * 100);
}


void ResourceScene::setLoadingString(const std::string& szContent)
{
	if (m_pShowLoadingText && !szContent.empty() )
	{
		m_pShowLoadingText->setString(szContent);
	}
}

void ResourceScene::setLoadingBarVisible(bool bIsVisible)
{
	if ( m_pLoadingBar )
	{
		m_pLoadingBar->setVisible(bIsVisible);
	}
}

void ResourceScene::setLoadingBarProgress(float fProgress)
{
	if ( m_pLoadingBar )
	{
		m_pLoadingBar->setPercent(fProgress);
	}
}

void ResourceScene::DidExit()
{
	if ( m_pFromSceneCommand )
	{
		m_pFromSceneCommand->setDelegate(nullptr);
		delete m_pFromSceneCommand;
		m_pFromSceneCommand = nullptr;
	}
	if ( m_pToSceneCommand )
	{
		m_pToSceneCommand->setDelegate(nullptr);
		delete m_pToSceneCommand;
		m_pToSceneCommand = nullptr;
	}
}


