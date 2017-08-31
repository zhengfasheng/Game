#include "EnemyManager.h"
#include "Enemy.h"
#include "Airplane.h"
#include "Resource.h"
#include "GameLevelManager.h"
#include "UIView.h"
#include "Bullet.h"
#include "UIManager.h"
#include "GameEvent.h"

EnemyInfo::EnemyInfo(
	EnemyType type,
	int nHP,
	EnemyMoveType moveType,
	int nScore,
	int nPower,
	AttackModel attackModel,
	float fShootSpeed,
	float fMoveSpeed,
	float fAttackScope
	)
	:m_type(type),
	m_nHp(nHP),
	m_moveType(moveType),
	m_nScore(nScore),
	m_nPower(nPower),
	m_attackModel(attackModel),
	m_fShootSpeed(fShootSpeed),
	m_fMoveSpeed(fMoveSpeed),
	m_fAttackScope(fAttackScope)
{

}

const char* EnemyInfo::getTextureName() const
{
	//这个地方是要取数组，防止数组越界
	if (m_type < EnemyType::Min || m_type > EnemyType::Max)
	{
		return g_enemyTextureNameVec[0];
	}
	else
	{
		return g_enemyTextureNameVec[static_cast<int>(m_type)];
	}
}

const char* EnemyInfo::getBulletTextureName() const
{
	return s_enemybullet;
}

const EnemyType EnemyInfo::getType() const
{
	return m_type;
}

const int EnemyInfo::getHP() const
{
	return m_nHp;
}

void EnemyInfo::setHP(int nValue)
{
	m_nHp = nValue;
}

const int EnemyInfo::getScore() const
{
	return m_nScore;
}

const EnemyMoveType EnemyInfo::getMoveType() const
{
	return m_moveType;
}

const int EnemyInfo::getPower() const
{
	return m_nPower;
}

const float EnemyInfo::getShootSpeed() const
{
	return m_fShootSpeed;
}

void EnemyInfo::setShootSpeed(float fValue)
{
	m_fShootSpeed = fValue;
}

EnemyInfo* EnemyInfo::clone()
{
	return new(std::nothrow) EnemyInfo(
		m_type,
		m_nHp,
		m_moveType,
		m_nScore,
		m_nPower,
		m_attackModel,
		m_fShootSpeed,
		m_fMoveSpeed,
		m_fAttackScope);
}

const float EnemyInfo::getMoveSpeed() const
{
	return m_fMoveSpeed;
}

void EnemyInfo::setMoveSpeed(float fValue)
{
	m_fMoveSpeed = fValue;
}

const float EnemyInfo::getAttackScope() const
{
	return m_fAttackScope;
}

const AttackModel EnemyInfo::getAttackModel() const
{
	return m_attackModel;
}


EnemyManager::EnemyManager()
	:m_fPrevAddEnemyTime(0)
{
	m_bossFlag[0] = 0;
	m_bossFlag[1] = 0;
}

EnemyManager::~EnemyManager()
{

}

//EnemyInfo(EnemyType type, int nHP, EnemyMoveType moveType, int nScore, int nPower, float fShootSpeed);
bool EnemyManager::init()
{
	m_enemyInfoVec.push_back(EnemyInfo(EnemyType::E0, 2, EnemyMoveType::MoveToEnd, 20, g_nPower));
	m_enemyInfoVec.push_back(EnemyInfo(EnemyType::E1, 4, EnemyMoveType::MoveToProtagonist, 40, g_nPower));
	m_enemyInfoVec.push_back(EnemyInfo(EnemyType::E2, 6, EnemyMoveType::MoveToProtagonist, 80, g_nPower * 2, AttackModel::LockTarget));
	m_enemyInfoVec.push_back(EnemyInfo(EnemyType::E3, 8, EnemyMoveType::MoveToPosThenLeftOrRigth, 120, g_nPower * 2));
	m_enemyInfoVec.push_back(EnemyInfo(EnemyType::E4, 10, EnemyMoveType::MoveToLeftOrRight, 160, g_nPower * 3, AttackModel::LockTarget));
	m_enemyInfoVec.push_back(EnemyInfo(EnemyType::E5, 100, EnemyMoveType::MoveBoss, 500, g_nPower * 3, AttackModel::Boss));
	return true;
}

void EnemyManager::createEnemy(float dt)
{
	do
	{
		//如果boss还在且没有被打死，不再产生敌机
		if (isBossAppear())
		{
			//如果已经被炸毁，恢复状态
			if (isBossDestroy())
			{
				setBossAppear(false);
				setBossDestroy(false);
			}
			else
			{
				return;
			}
		}
		auto param = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_GAME_LEVEL_INTERVAL);
		if ( param.isNull() )
		{
			return;
		}
		
		auto fInterval = param.asFloat();

		m_fPrevAddEnemyTime += dt;
		if (m_fPrevAddEnemyTime < fInterval )
		{
			return;
		}
		m_fPrevAddEnemyTime = 0.f;

		param = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_GAME_LEVEL_MAX_COUNT);
		if (param.isNull() )
		{
			return;
		}
		auto nMaxCount = param.asInt();
		//产生敌机数
		auto nMax = random(1, nMaxCount);
		size_t nType;
		param = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_GAME_LEVEL_MIN_TYPE);
		if (param.isNull())
		{
			return;
		}
		auto nMinType = param.asInt();
		param = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_GAME_LEVEL_MAX_TYPE);
		if (param.isNull())
		{
			return;
		}
		auto nMaxType = param.asInt();
		for (int i = 0; i < nMax; i++)
		{
			nType = random<unsigned int>((size_t)nMinType, (size_t)nMaxType);
			if (nType >= m_enemyInfoVec.size())
			{
				nType = m_enemyInfoVec.size() - 1;
			}
			addEnemyToLayer(&m_enemyInfoVec[nType]);
		}

	} while (0);
}

//#define OneAdd

#ifdef OneAdd
bool bIsAdd = false;
#endif // 0

void EnemyManager::addEnemyToLayer(EnemyInfo* pInfo)
{
	do
	{
#ifdef OneAdd
		if (bIsAdd)
		{
			return;
		}
#endif

		auto pNewInfo = pInfo->clone();
		CC_BREAK_IF(!pNewInfo);
		pNewInfo->setShootSpeed(random(g_fMinShootSpeed, g_fMaxShootSpeed));
		pNewInfo->setMoveSpeed(random(g_fMinMoveSpeed, g_fMaxMoveSpeed));
		if (pNewInfo->getAttackModel() == AttackModel::Boss)//boss出现
		{
			setBossAppear(true);
		}

		auto pEnemy = Enemy::create(pNewInfo);
		CC_BREAK_IF(!pEnemy);
		auto winSize = Director::getInstance()->getWinSize();
			
		//产生出生坐标点
		auto startPos = Vec2(random<float>(60, winSize.width - 60), winSize.height);
#ifdef OneAdd
		startPos = Vec2(g_defaultPlanePosition.x + 60, winSize.height - 60);
#endif
		pEnemy->setPosition(startPos);

		Vec2 endPos = startPos;
		Action *pAction = nullptr;
		CallFunc* pCall = nullptr;
		auto size = pEnemy->getContentSize();
		float fTime = 0.0f;
		switch (pEnemy->getMoveType())
		{
		case EnemyMoveType::MoveToProtagonist:
		{
			auto param = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_AIRPLANE_POSITION);
			if ( !param.isNull() && param.asPointer() )
			{
				auto pos = *(Vec2*)param.asPointer();
				if (pos.x - startPos.x == 0)//90/-90度
				{
					endPos.y = -size.height;
				}
				else
				{
					//先计算出斜率
					auto fSlope = (pos.y - startPos.y) / (pos.x - startPos.x);

					auto fAngle = CC_RADIANS_TO_DEGREES(atan(fSlope));

					auto fRotateAngle = fSlope > 0 ? 90 - fAngle : -(90 - fabs(fAngle));

					pEnemy->setRotation(fRotateAngle);

					//点斜式 y2 - y1 = k * ( x2 - x1 )
					//x2 = (y2 - y1)/k + x1
					endPos.y = -size.height;;
					endPos.x = (endPos.y - startPos.y) / fSlope + startPos.x;

				}
			}
			else
			{
				endPos = Vec2(winSize.width / 2, -size.height);//飞出去,不然停在屏幕最低下了
			}
		}
		break;
		case EnemyMoveType::MoveToEnd:
		{
			endPos.y = -size.height;
		}
		break;
		case EnemyMoveType::MoveToPosThenLeftOrRigth:
		{
			//endPos.x = winSize.width + (rand_0_1() ? -1 : 1) * random(20.f, winSize.width - 20.f);
			endPos.y = random(winSize.height / 2, winSize.height * 2 / 3);
			pCall = CallFunc::create(CC_CALLBACK_0(EnemyManager::moveEndCallback, this, pEnemy));
		}
		break;
		case EnemyMoveType::MoveToLeftOrRight:
		{
			//屏幕左侧(往右移动)
			if (startPos.x <= winSize.width / 2)
			{
				endPos.x = winSize.width + size.width;
				endPos.y = winSize.height / 2;
			}
			else
			{
				endPos.x = -size.width;
				endPos.y = winSize.height / 2;
			}
		}
		break;
		case EnemyMoveType::MoveBoss:
		{
			endPos.x = random(10.f, winSize.width - 10.f);
			endPos.y = random(winSize.height / 2, winSize.height);
			pCall = CallFunc::create(CC_CALLBACK_0(EnemyManager::onBossMoveEnd, this, pEnemy));
		}
		break;
		default:
			break;
		}

		UIManager::getInstance()->SendEvent(ControllerID::Game, GameEvent::NOTIFY_ADD_ENEMY_TO_VIEW, pEnemy);
		addEnemyToContainer(pEnemy);
#ifdef OneAdd
		bIsAdd = true;
#endif

		//计算时间
		auto distance = startPos.distance(endPos);
		fTime = distance / pNewInfo->getMoveSpeed();
		auto pMoveTo = MoveTo::create(fTime, endPos);
		if (pCall)
		{
			pAction = Sequence::createWithTwoActions(pMoveTo, pCall);
		}
		else
		{
			pAction = pMoveTo;
		}
		if (pAction)
		{
#ifndef OneAdd
			pEnemy->runAction(pAction);
#endif
		}

	} while (0);
}

void EnemyManager::moveEndCallback(Enemy* pEnemy)
{
	do
	{

		CC_BREAK_IF(!pEnemy);
		auto winSize = Director::getInstance()->getWinSize();
		auto nTimes = pEnemy->getTag();
		auto startPos = pEnemy->getPosition();
		auto size = pEnemy->getContentSize();
		auto endPos = startPos;
		auto nMaxMoveTimes = 3;

		if (nTimes >= nMaxMoveTimes)//移动屏幕
		{
			endPos.x = random(0, 1) > 0 ? winSize.width + size.width : -size.width;
			//log("---||%f||---", endPos.x);
		}
		else
		{
			if (startPos.x < winSize.width / 2)//左边(右跑)
			{
				endPos.x = random(winSize.width / 2, winSize.width - 10);
			}
			else//在右边
			{
				endPos.x = random(0.f, winSize.width / 2);
			}
		}

		auto distance = startPos.distance(endPos);
		auto fTime = distance / pEnemy->getMoveSpeed();

		auto pDelay = DelayTime::create(1);
		auto pMoveby = MoveTo::create(fTime, endPos);

		CallFunc* pCall = nullptr;
		if (nTimes < nMaxMoveTimes)
		{
			pCall = CallFunc::create(CC_CALLBACK_0(EnemyManager::moveEndCallback, this, pEnemy));
		}
		else
		{
			pCall = CallFunc::create(CC_CALLBACK_0(EnemyManager::removeEnemy, this, pEnemy));
		}

		auto pAction = CCSequence::create(pDelay, pMoveby, pCall, nullptr);
		pEnemy->setTag(++nTimes);
		pEnemy->runAction(pAction);

	} while (0);
}

void EnemyManager::removeEnemy(Enemy* pEnemy)
{
	do
	{
		CC_BREAK_IF(!pEnemy);
		UIManager::getInstance()->SendEvent(ControllerID::Game, GameEvent::NOTIFY_REMOVE_ENEMY, (void*)pEnemy);
	} while (0);
}

void EnemyManager::recoverToDefault()
{
	m_fPrevAddEnemyTime = 0.f;
	m_bossFlag[0] = 0;
	m_bossFlag[1] = 0;
}

void EnemyManager::setBossAppear(bool bIsAppear)
{
	m_bossFlag[0] = bIsAppear;
}

bool EnemyManager::isBossAppear()
{
	return m_bossFlag[0] == 1;
}

void EnemyManager::setBossDestroy(bool bIsDeath)
{
	m_bossFlag[1] = bIsDeath;
}

bool EnemyManager::isBossDestroy()
{
	return m_bossFlag[1] == 1;
}

void EnemyManager::onBossMoveEnd(Enemy* pEnemy)
{
	do
	{
		CC_BREAK_IF(!pEnemy);
		auto winSize = Director::getInstance()->getWinSize();
		auto startPos = pEnemy->getPosition();
		auto endPos = startPos;
		auto nDirX = random(0, 1);
		auto nDirY = random(0, 1);
		endPos.x = nDirX ? random(startPos.x, winSize.width) : random(0.f, startPos.x);
		endPos.y = nDirY ? random(startPos.y, winSize.height) : random(winSize.height / 2, startPos.y);

		//计算时间
		auto distance = startPos.distance(endPos);
		auto fTime = distance / pEnemy->getMoveSpeed();
		auto pMoveTo = MoveTo::create(fTime, endPos);
		auto pCall = CallFunc::create(CC_CALLBACK_0(EnemyManager::onBossMoveEnd, this, pEnemy));
		pEnemy->runAction(Sequence::createWithTwoActions(pMoveTo, pCall));

	} while (0);
}

void EnemyManager::addEnemyToContainer(Enemy* pEnemy)
{
	if ( pEnemy )
	{
		m_enemyContainer.pushBack(pEnemy);
	}
}

void EnemyManager::addEnemyToBulletContainer(Bullet* pBullet)
{
	if ( pBullet )
	{
		m_enemyBulletContainer.pushBack(pBullet);
	}
}

void EnemyManager::addMyBulletContainer(Bullet* pBullet)
{
	if ( pBullet )
	{
		m_myBulletContainer.pushBack(pBullet);
	}
}

