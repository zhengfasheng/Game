#include "IScene.h"
#include "SceneDelegate.h"

IScene::IScene()
	:m_pDelegate(nullptr)
	, m_type(SceneType::Invalid)
{

}

IScene::~IScene()
{
	m_pDelegate = nullptr;
	m_type = SceneType::Invalid;
}

bool IScene::init(SceneDelegate* pDelegate, SceneType type)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Scene::init() || !pDelegate || type == SceneType::Invalid);
		m_pDelegate = pDelegate;
		m_type = type;
		m_pDelegate->Init(this);
		bRet = true;
	} while (0);
	return bRet;
}

void IScene::onEnter()
{
	Scene::onEnter();
	this->WillEnter();
	m_pDelegate->OnEnter(this);
}

void IScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	m_pDelegate->OnEnterTransitionDidFinish(this);
	this->DidEnter();
}

void IScene::onExit()
{
	this->DidExit();
	m_pDelegate->OnExit(this);
	Scene::onExit();
	
}

void IScene::onExitTransitionDidStart()
{
	this->WillExit();
	m_pDelegate->OnExitTransitionDidStart(this);
	Scene::onExitTransitionDidStart();
	
}

const SceneType& IScene::getSceneType()
{
	return m_type;
}
