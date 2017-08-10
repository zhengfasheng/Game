#include "SceneManager.h"
#include "LoginScene.h"
#include "UIManager.h"
#include "HallScene.h"
#include "DataHelperManager.h"

USING_NS_CC;

SceneManager::SceneManager()
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
	if (!glview) {
		glview = GLViewImpl::createWithRect("HelloCpp", Rect(0, 0, 960, 640));
		director->setOpenGLView(glview);
	}

	director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60.f);

	DataHelperManager::getInstance()->init();

	FileUtils::getInstance()->addSearchPath("res");
	auto scene = LoginScene::create(this);
	
	// run
	director->runWithScene(scene);
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

void SceneManager::GoToHall()
{
	auto pScene = HallScene::create(this);
	Director::getInstance()->replaceScene(pScene);
}

void SceneManager::GoToLogin()
{
	auto pScene = LoginScene::create(this);
	Director::getInstance()->replaceScene(pScene);
}

void SceneManager::GoToScene(SceneType type)
{
	switch (type)
	{
	case SceneType::Invalid:
		break;
	case SceneType::Login:
		GoToLogin();
		break;
	case SceneType::Hall:
		GoToHall();
		break;
	case SceneType::Room:
		break;
	case SceneType::RoomList:
		break;
	default:
		break;
	}
}


