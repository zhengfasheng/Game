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
		
		//�л�������
		m_pEnemyManager = new EnemyManager;
		CC_BREAK_IF(!m_pEnemyManager);
		m_pEnemyManager->init();

		//��Ϸ�ȼ�������
		m_pGameLevelManger = new GameLevelManager;
		CC_BREAK_IF(!m_pGameLevelManger);
		m_pGameLevelManger->init();

		//�ɻ��ȼ�������
		m_pAirplaneLevelManager = new AirplaneLevelManager;
		CC_BREAK_IF(!m_pAirplaneLevelManager);
		m_pAirplaneLevelManager->init();

		//������������Ϣ
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
		//˵���ɻ��Ѿ����ˣ�
		if ( getOpView() )
		{
			//�����л����Լ��ҵ��󣬻�ֹͣ�л�������
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

//��ҷɻ����
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

//�л����
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

	//��Ҳ����ķɻ�
	auto pAirplane = getOpView()->getAirplane();

	//���л����Լ��ӵ���ײ��
	for (auto itEnemy = m_pEnemyManager->m_enemyContainer.begin(); itEnemy != m_pEnemyManager->m_enemyContainer.end();)
	{
		pEnemy = *itEnemy;
		if (pEnemy == nullptr)
			continue;
		//�л����Լ����ӵ�
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
		//�л����Լ��ķɻ�
		if (IsCollide(pEnemy, pAirplane))
		{
			if (pAirplane->isLive())
			{
				//�л����Լ���ײ����ͬʱ�ҵ�
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


	//����Լ���л��ӵ�
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
		//����Ƿ��Ѿ�������Ļ��Χ
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
		//�Լ����ӵ�
		IMPLAMENT_CHECK_OBJECT(m_pEnemyManager->m_myBulletContainer);
		//�л�
		IMPLAMENT_CHECK_OBJECT(m_pEnemyManager->m_enemyContainer);
		//�л��ӵ�
		IMPLAMENT_CHECK_OBJECT(m_pEnemyManager->m_enemyBulletContainer);
	}
	

	//��Ҳ����ķɻ�
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
		//��Ϸ����
		log("----------------- Game Over -----------------");
		//ֹͣupdate
		if ( pOpView )
		{
			pOpView->unscheduleUpdate();
		}

		//�������
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

	//�����д�������⣬�������{}�������ͷ��ˣ�
	/*AirplaneLevel info = m_pAirplaneLevelManager->getAirplaneLevelInfo(m_pAirplaneLevelManager->getLevel());
	AirplaneLevel* ret = &info;
	return (void*)ret;*/
}
