#include "GameOpView.h"
#include "Airplane.h"
#include "Effect.h"
#include "UIManager.h"
#include "GameEvent.h"
#include "Enemy.h"
#include "Bullet.h"

const std::string ADD_ENEMY_TIMER = "ADD_ENEMY_TIMER";
GameOpView::GameOpView()
	:m_pAirplane(nullptr)
{

}

GameOpView::~GameOpView()
{
	m_pAirplane = nullptr;
}

bool GameOpView::init(UIViewControllerDelegate* pUIViewControllerDelegate)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!GameView::init(pUIViewControllerDelegate));

		scheduleUpdate();

		bRet = true;
	} while (0);
	return bRet;
}

void GameOpView::startPlaySunEffect()
{
	float dt = random(2.0f, 10.0f);
	scheduleOnce(CC_SCHEDULE_SELECTOR(GameOpView::schedulePlaySunEffect), dt);
}

void GameOpView::schedulePlaySunEffect(float dt)
{
	auto pEffecf = Effect::create();
	if (pEffecf)
	{
		auto winSize = Director::getInstance()->getWinSize();
		auto pCall = CallFunc::create(CC_CALLBACK_0(GameOpView::startPlaySunEffect, this));
		pEffecf->playFlareEffect(this, (int)OpViewZOrder::Effect,Vec2(50, winSize.height - 50), -130, random(5.0f, 8.0f), pCall);
	}
}

void GameOpView::addAirplane()
{
	//创建自己的飞机
	auto level = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_AIRPLANE_LEVEL);
	auto power = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_AIRPLANE_POWER);
	auto shootSpeed = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_AIRPLANE_SHOOT_SPEED);

	m_pAirplane = Airplane::create(level.asInt(),power.asInt(),shootSpeed.asFloat());
	if ( m_pAirplane )
	{
		addChild(m_pAirplane, (int)OpViewZOrder::MyPlane);
	}
}

bool GameOpView::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void GameOpView::onTouchMoved(Touch *touch, Event *unused_event)
{
	do
	{
		//如果当前的飞机没有了
		CC_BREAK_IF(!m_pAirplane);
		auto winSize = Director::getInstance()->getWinSize();
		auto pos = touch->getDelta();
		auto currentPos = m_pAirplane->getPosition();
		currentPos += pos;
		m_pAirplane->setPosition(currentPos.getClampPoint(Vec2::ZERO, Vec2(winSize.width, winSize.height)));

	} while (0);
}

void GameOpView::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void GameOpView::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

void GameOpView::Show()
{
	GameView::Show();
	startPlaySunEffect();
	addAirplane();
	addEventListener();
	startAddEnemy();
}

void GameOpView::update(float delta)
{
	UIManager::getInstance()->SendEvent(ControllerID::Game,GameEvent::NOTIFY_GAME_UPDATE,delta);
}

Airplane* GameOpView::getAirplane()
{
	return m_pAirplane;
}

void GameOpView::checkAirplane()
{
	if (m_pAirplane && !m_pAirplane->isLive())
	{
		m_pAirplane->destory();
		m_pAirplane = nullptr;
	}
}

void GameOpView::HideEnd()
{
	removeEventListener();
	GameView::HideEnd();
}

void GameOpView::startAddEnemy()
{
	schedule([](float dt){
		UIManager::getInstance()->SendEvent(ControllerID::Game, GameEvent::NOTITY_START_ADD_ENEMY,dt);
	}, ADD_ENEMY_TIMER);
}

void GameOpView::stopAddEnemy()
{
	unschedule(ADD_ENEMY_TIMER);
}

void GameOpView::addEnemy(Enemy* pEnemy)
{
	if ( pEnemy )
	{
		this->addChild(pEnemy, (int)OpViewZOrder::Enemy);
	}
}

void GameOpView::addBullet(Bullet* pBullet)
{
	if ( pBullet )
	{
		this->addChild(pBullet, (int)OpViewZOrder::Bullet);
	}
}



