#include "GameProcedure.h"
#include "LoginScene.h"
#include "UIManager.h"
#include "Hall\HallScene.h"

USING_NS_CC;

GameProcedure::GameProcedure()
{

}

GameProcedure::~GameProcedure()
{

}

void GameProcedure::GameStart()
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

	FileUtils::getInstance()->addSearchPath("res");
	auto scene = LoginScene::create(this);

	// run
	director->runWithScene(scene);
}

void GameProcedure::Init(IScene* pScene)
{
	UIManager::getInstance()->Init(pScene);
}

void GameProcedure::OnEnter(IScene* pScene)
{
	UIManager::getInstance()->OnEnter(pScene);
}

void GameProcedure::OnEnterTransitionDidFinish(IScene* pScene)
{
	UIManager::getInstance()->OnEnterTransitionDidFinish(pScene);
}

void GameProcedure::OnExit(IScene* pScene)
{
	UIManager::getInstance()->OnExit(pScene);
}

void GameProcedure::OnExitTransitionDidStart(IScene* pScene)
{
	UIManager::getInstance()->OnExitTransitionDidStart(pScene);
}

void GameProcedure::GoToHall()
{
	auto pScene = HallScene::create(this);
	Director::getInstance()->replaceScene(pScene);
}

void GameProcedure::GoToLogin()
{
	auto pScene = LoginScene::create(this);
	Director::getInstance()->replaceScene(pScene);
}


