#include "SceneManager.h"
#include "UIManager.h"
#include "DataHelperManager.h"
#include "SceneFactory.h"
#include "ResourceScene.h"
#include "GameConfig.h"

USING_NS_CC;

SceneManager::SceneManager()
	:m_nCurrentSceneType(SceneType::Invalid)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::GameStart()
{
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	auto fWidth = GameConfig::getInstance()->getScreenWidth();
	auto fHeight = GameConfig::getInstance()->getScreenHeight();
	if (!glview) {
		glview = GLViewImpl::createWithRect("HelloCpp", Rect(0, 0, fWidth, fHeight));
		director->setOpenGLView(glview);
	}

	director->getOpenGLView()->setDesignResolutionSize(fWidth, fHeight, ResolutionPolicy::SHOW_ALL);

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60.f);

	DataHelperManager::getInstance()->init();
	Language::getInstance()->init();

	FileUtils::getInstance()->addSearchPath("res");
	FileUtils::getInstance()->addSearchPath("config");
	FileUtils::getInstance()->addSearchPath("Language");
	FileUtils::getInstance()->addSearchPath("Music");
	this->GoToScene(SceneType::Start);
}

void SceneManager::Init(IScene* pScene)
{
	UIManager::getInstance()->Init(pScene);
}

void SceneManager::OnEnter(IScene* pScene)
{
	UIManager::getInstance()->OnEnter(pScene);
}

void SceneManager::OnEnterTransitionDidFinish(IScene* pScene)
{
	UIManager::getInstance()->OnEnterTransitionDidFinish(pScene);
}

void SceneManager::OnExit(IScene* pScene)
{
	UIManager::getInstance()->OnExit(pScene);
}

void SceneManager::OnExitTransitionDidStart(IScene* pScene)
{
	UIManager::getInstance()->OnExitTransitionDidStart(pScene);
}

void SceneManager::GoToScene(SceneType type)
{
	//先跳转加载资源场景，加载资源完成，才真正的跳转到指定的场景
	do 
	{
		auto pResourceScene = ResourceScene::create(this, m_nCurrentSceneType, type);
		CC_BREAK_IF(!pResourceScene);
		Director::getInstance()->replaceScene(pResourceScene);
		m_nCurrentSceneType = type;
	} while (0);

}

void SceneManager::loadResourceComplete(SceneType type)
{
	do 
	{
		if ( type == m_nCurrentSceneType )
		{
			auto pScene = SceneFactory::getInstance()->create(this, type);
			CC_BREAK_IF(!pScene);
			Director::getInstance()->replaceScene(pScene);
		}
	} while (0);
}


