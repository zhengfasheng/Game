#include "GameController.h"
#include "EnemyManager.h"
#include "GameMainView.h"
#include "GameLevelManager.h"
#include "CurrentPlayerInfo.h"
#include "Bullet.h"
#include "AirplaneLevelManager.h"
#include "SoundHelper.h"
#include "UIManager.h"
#include "Enemy.h"
#include "GameOpView.h"
#include "Airplane.h"
#include "SceneManager.h"
#include "GameInfoView.h"


GameController::GameController()
	:m_pEnemyManager(nullptr)
	, m_fGameTime(0.f)
	, m_pGameLevelManger(nullptr)
{

}

GameController::~GameController()
{
	destory();
}

UIView* GameController::createView(UIViewControllerDelegate* pDelegate)
{
	return GameMainView::create(pDelegate);
}

bool GameController::Init(UIManager* pManager, ControllerID id)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!UIViewController::Init(pManager, id));
		
		//敌机管理器
		m_pEnemyManager = new EnemyManager;
		CC_BREAK_IF(!m_pEnemyManager);
		m_pEnemyManager->init();

		//游戏等级管理器
		m_pGameLevelManger = new GameLevelManager;
		CC_BREAK_IF(!m_pGameLevelManger);
		m_pGameLevelManger->init();

		//飞机等级管理器
		m_pAirplaneLevelManager = new AirplaneLevelManager;
		CC_BREAK_IF(!m_pAirplaneLevelManager);
		m_pAirplaneLevelManager->init();

		//重置玩家相关信息
		CurrentPlayerInfo::getInstance()->reset();

		bRet = true;
	} while (0);
	return bRet;
}

void GameController::destory()
{
	CC_SAFE_DELETE(m_pEnemyManager);
	CC_SAFE_DELETE(m_pGameLevelManger);
	CC_SAFE_DELETE(m_pAirplaneLevelManager);
}

IMPLEMENT_HANDLER(GameController,onBossDead)
{
	m_pEnemyManager->setBossDestroy(true);
}

IMPLEMENT_HANDLER(GameController, onAddScore)
{
	CurrentPlayerInfo::getInstance()->addScore( p1.asInt());
	if (getInfoView())
	{
		getInfoView()->setScore(CurrentPlayerInfo::getInstance()->getUserInfo().getScore());
	}
}

IMPLEMENT_HANDLER(GameController, onRemoveEnemyBullet)
{
	auto pBullet = (Bullet*)p1.asPointer();
	if (!pBullet) return;
	auto it = std::find(m_pEnemyManager->m_enemyBulletContainer.begin(), m_pEnemyManager->m_enemyBulletContainer.end(), pBullet);
	if (it != m_pEnemyManager->m_enemyBulletContainer.end())
	{
		m_pEnemyManager->m_enemyBulletContainer.erase(it);
		pBullet->removeFromParent();
	}
}

IMPLEMENT_HANDLER(GameController, onStartAddEnemy)
{
	if ( m_pEnemyManager )
	{
		m_pEnemyManager->createEnemy(p1.asFloat());
	}
}

IMPLEMENT_HANDLER(GameController, onStopAddEnemy)
{
	if ( getOpView() )
	{
		getOpView()->stopAddEnemy();
	}
}

IMPLEMENT_HANDLER(GameController, onMyAirplaneDestory)
{
	m_pAirplaneLevelManager->levelDown();
	decreaseRebornTimes();
}

IMPLEMENT_HANDLER(GameController, onMyAirplaneReborn)
{
	if (CurrentPlayerInfo::getInstance()->getUserInfo().getCurrentRebornTimes() > 0)
	{
		//说明飞机已经挂了，
		if ( getOpView() )
		{
			//产生敌机，自己挂掉后，会停止敌机的生产
			getOpView()->addAirplane();
			getOpView()->startAddEnemy();
		}
		
	}
}

IMPLEMENT_HANDLER(GameController, onRemoveMyBullet)
{
	if (!p1.isNull() && p1.asPointer())
	{
		auto pBullet = (Bullet*)p1.asPointer();
		if (!pBullet) return;
		auto it = std::find(m_pEnemyManager->m_myBulletContainer.begin(), m_pEnemyManager->m_myBulletContainer.end(), pBullet);
		if (it != m_pEnemyManager->m_myBulletContainer.end())
		{
			m_pEnemyManager->m_myBulletContainer.erase(it);
			pBullet->removeFromParent();
		}
	}
}

//玩家飞机射击
IMPLEMENT_HANDLER(GameController, onAirplaneShoot)
{
	if (m_pEnemyManager && getOpView())
	{
		auto pBullet = (Bullet*)p1.asPointer();
		if ( pBullet )
		{
			m_pEnemyManager->m_myBulletContainer.pushBack(pBullet);
			getOpView()->addBullet(pBullet);
		}
	}
}

//敌机射击
IMPLEMENT_HANDLER(GameController, onEnemyShoot)
{
	if (m_pEnemyManager && getOpView() )
	{
		auto pBullet = (Bullet*)p1.asPointer();
		if (pBullet)
		{
			m_pEnemyManager->m_enemyBulletContainer.pushBack(pBullet);
			getOpView()->addBullet(pBullet);
		}
	}
}


IMPLEMENT_HANDLER(GameController, onGamePause)
{
	Director::getInstance()->pause();
	SoundHelper::getInstance()->setBackgroundMusic(false);
	SoundHelper::getInstance()->setAudio(false);
	if ( getRealView() )
	{
		getRealView()->showGamePauseView();
	}
}

IMPLEMENT_HANDLER(GameController, onGameResume)
{
	Director::getInstance()->resume();
	SoundHelper::getInstance()->setAudio(true);
	SoundHelper::getInstance()->setBackgroundMusic(true);
}

IMPLEMENT_HANDLER(GameController, onGameUpdate)
{
	checkCollide();
	checkObject(p1.asFloat());
	m_fGameTime += p1.asFloat();
}

IMPLEMENT_HANDLER(GameController, onAddEnemyToView)
{
	if (getOpView() && !p1.isNull())
	{
		getOpView()->addEnemy((Enemy*)p1.asPointer());
	}
}

IMPLEMENT_HANDLER(GameController, onRemoveEnemy)
{
	if ( !p1.isNull() && p1.asPointer() )
	{
		auto pEnemy = (Enemy*)p1.asPointer();
		if (!pEnemy) return;
		auto it = std::find(m_pEnemyManager->m_enemyContainer.begin(), m_pEnemyManager->m_enemyContainer.end(), pEnemy);
		if (it != m_pEnemyManager->m_enemyContainer.end())
		{
			m_pEnemyManager->m_enemyContainer.erase(it);
			pEnemy->removeFromParent();
		}
	}
}

IMPLEMENT_HANDLER(GameController, onAirplaneLevelUp)
{
	m_pAirplaneLevelManager->leveUp();
	if ( getOpView() )
	{
		getOpView()->getAirplane()->setLevel(m_pAirplaneLevelManager->getLevel());
	}
}

void GameController::DidShow()
{
	UIViewController::DidShow();
}

GameMainView* GameController::getRealView()
{
	return dynamic_cast<GameMainView*>(getView());
}

GValue GameController::getAirplaneLevel()
{
	return m_pAirplaneLevelManager->getLevel();
}

GValue GameController::getAirplanePower()
{
	return m_pAirplaneLevelManager->getAirplaneLevelInfo(m_pAirplaneLevelManager->getLevel()).getPower();
}

GValue GameController::getAirplaneShootSpeed()
{
	return m_pAirplaneLevelManager->getAirplaneLevelInfo(m_pAirplaneLevelManager->getLevel()).getShootSpeed();
}

void GameController::checkCollide()
{
	if (!m_pEnemyManager || !getOpView())
	{
		return;
	}
	auto winSize = Director::getInstance()->getWinSize();
	auto screenRect = Rect(0, 0, winSize.width, winSize.height + 10);
	Enemy* pEnemy = nullptr;
	Bullet* pBullet = nullptr;

	//玩家操作的飞机
	auto pAirplane = getOpView()->getAirplane();

	//检测敌机与自己子弹的撞击
	for (auto itEnemy = m_pEnemyManager->m_enemyContainer.begin(); itEnemy != m_pEnemyManager->m_enemyContainer.end();)
	{
		pEnemy = *itEnemy;
		if (pEnemy == nullptr)
			continue;
		//敌机与自己的子弹
		for (auto itMyBullet = m_pEnemyManager->m_myBulletContainer.begin(); itMyBullet != m_pEnemyManager->m_myBulletContainer.end();)
		{
			pBullet = *itMyBullet;
			if (pBullet == nullptr)
				continue;
			if (IsCollide(pEnemy, pBullet))
			{
				pEnemy->hurt(pBullet->getPower());
				pBullet->hurt();
			}
			if (!screenRect.intersectsRect(pBullet->getBoundingBox()))
			{
				pBullet->destory();
				itMyBullet = m_pEnemyManager->m_myBulletContainer.erase(itMyBullet);
			}
			else
			{
				itMyBullet++;
			}
		}
		//敌机与自己的飞机
		if (IsCollide(pEnemy, pAirplane))
		{
			if (pAirplane->isLive())
			{
				//敌机与自己相撞两人同时挂掉
				pEnemy->hurt();
				pAirplane->hurt();
			}
		}

		if (!screenRect.intersectsRect(pEnemy->getBoundingBox()))
		{
			pEnemy->destory();
			itEnemy = m_pEnemyManager->m_enemyContainer.erase(itEnemy);
		}
		else
		{
			itEnemy++;
		}

	}


	//检查自己与敌机子弹
	for (auto it = m_pEnemyManager->m_enemyBulletContainer.begin(); it != m_pEnemyManager->m_enemyBulletContainer.end();)
	{
		pBullet = *it;
		if (pBullet == nullptr)
			continue;
		if (IsCollide(pBullet, pAirplane))
		{
			if (pAirplane->isLive())
			{
				pBullet->hurt();
				pAirplane->hurt(pBullet->getPower());
			}
		}
		//检查是否已经超出屏幕范围
		if (!screenRect.intersectsRect(pBullet->getBoundingBox()))
		{
			pBullet->destory();
			it = m_pEnemyManager->m_enemyBulletContainer.erase(it);
		}
		else
		{
			it++;
		}
	}
}

bool GameController::IsCollide(EntityObject* pA, EntityObject* pB)
{
	do
	{
		CC_BREAK_IF(!pA || !pB);
		return pA->getCollideRect().intersectsRect(pB->getCollideRect());
	} while (0);
	return false;
}

#define IMPLAMENT_CHECK_OBJECT( obj )\
	for (auto it = obj.begin(); it != obj.end();)\
	{\
		if (*it == nullptr)\
			continue;\
		(*it)->update(dt);\
		if (!(*it)->isLive())\
		{\
			(*it)->destory();\
			it = obj.erase(it);\
		}\
		else\
		{\
			it++;\
		}\
	}\

void GameController::checkObject(float dt)
{
	if ( m_pEnemyManager )
	{
		//自己的子弹
		IMPLAMENT_CHECK_OBJECT(m_pEnemyManager->m_myBulletContainer);
		//敌机
		IMPLAMENT_CHECK_OBJECT(m_pEnemyManager->m_enemyContainer);
		//敌机子弹
		IMPLAMENT_CHECK_OBJECT(m_pEnemyManager->m_enemyBulletContainer);
	}
	

	//玩家操作的飞机
	if (getOpView())
	{
		getOpView()->checkAirplane();
	}
}


GValue GameController::getAirplanePosition()
{
	if (getOpView())
	{
		auto pAirplane = getOpView()->getAirplane();
		if ( pAirplane )
		{
			return (void*)&pAirplane->getPosition();
		}
	}
	return GValue::Null;
}

void GameController::decreaseRebornTimes()
{
	auto nLife = CurrentPlayerInfo::getInstance()->getUserInfo().getCurrentRebornTimes();
	if (nLife - 1 < 0)
	{
		return;
	}
	nLife--;
	CurrentPlayerInfo::getInstance()->getUserInfo().setCurrentRebornTimes(nLife);

	GameOpView* pOpView = getOpView();
	if (nLife <= 0)
	{
		//游戏结束
		log("----------------- Game Over -----------------");
		//停止update
		if ( pOpView )
		{
			pOpView->unscheduleUpdate();
		}

		//保存分数
		CurrentPlayerInfo::getInstance()->savePlayerInformation();
		SceneManager::getInstance()->GoToScene(SceneType::GameOver);
	}

	if ( getInfoView() )
	{
		getInfoView()->decreaseRebornTimes(nLife);
	}
}

GameOpView* GameController::getOpView()
{
	if (getRealView() && getRealView()->getGameOpView())
	{
		return getRealView()->getGameOpView();
	}
	return nullptr;
}

GameInfoView* GameController::getInfoView()
{
	if (getRealView())
	{
		return getRealView()->getGameInfoView();
	}
	return nullptr;
}

GValue GameController::getGameTime()
{
	return m_fGameTime;
}


GameLevel GameController::getGameLevel()
{
	return m_pGameLevelManger->getGameLevel();
}

GValue GameController::getGameLevelInterval()
{
	return getGameLevel().getInterval();
}

GValue GameController::getGameLevelMaxCount()
{
	return getGameLevel().getMaxCount();
}

GValue GameController::getGameLevelMinType()
{
	return (int)getGameLevel().getMinType();
}

GValue GameController::getGameLevelMaxType()
{
	return (int)getGameLevel().getMaxType();
}

GValue GameController::getAirplaneLevelInfo()
{
	//return (void*)&m_pAirplaneLevelManager->getAirplaneLevelInfo(m_pAirplaneLevelManager->getLevel());
	
	const AirplaneLevel& info = m_pAirplaneLevelManager->getAirplaneLevelInfo(m_pAirplaneLevelManager->getLevel());
	const AirplaneLevel* ret = &info;
	return (void*)ret;

	//下面的写法有问题，出了这个{}变量被释放了，
	/*AirplaneLevel info = m_pAirplaneLevelManager->getAirplaneLevelInfo(m_pAirplaneLevelManager->getLevel());
	AirplaneLevel* ret = &info;
	return (void*)ret;*/
}
