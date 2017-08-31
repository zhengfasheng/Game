#include "Enemy.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "Effect.h"
#include "Airplane.h"
#include "UIManager.h"
#include "GameEvent.h"
#include "SoundHelper.h"
#include "UIView.h"
#include "EnemyManager.h"

Enemy::Enemy() 
	:m_pInfo(nullptr)
{

}

Enemy::~Enemy()
{
	CC_SAFE_DELETE(m_pInfo);
}

void Enemy::destory()
{
	this->stopAllActions();
	unschedule(schedule_selector(Enemy::shoot));
	if ( getHP() <=0 )
	{
		

		//播放一个爆炸特效
		auto pEffect = Effect::create();
		pEffect->playExplodeEffect(this->getParent(),(int)OpViewZOrder::Effect, getPosition());
		pEffect->playSparkEffect(this->getParent(), (int)OpViewZOrder::Effect, getPosition());
		
		if ( m_pInfo )
		{
			if (m_pInfo->getType() == EnemyType::E5)//是boss，通知敌机管理器设置炸毁状态
			{
				UIManager::getInstance()->SendEvent(ControllerID::Game,GameEvent::NOTIFY_BOOS_DEAD);
			}
			//只有当是被打死的才加分
			UIManager::getInstance()->SendEvent(ControllerID::Game,GameEvent::NOTIFY_ADD_SCORE, m_pInfo->getScore());
		}
		
		SoundHelper::getInstance()->playAudio(SoundHelper::AudioType::EnemyDestroy);
	}
	else
	{
		//log("this plane fly over the screen");
	}

	this->removeFromParentAndCleanup(true);
}

void Enemy::hurt( int nValue )
{
	if (m_pInfo)
		m_pInfo->setHP(m_pInfo->getHP() - nValue);
}

void Enemy::hurt()
{
	if (m_pInfo)
		hurt(m_pInfo->getHP());
}

bool Enemy::isLive()
{
	if (m_pInfo) 
		return m_pInfo->getHP() > 0;
	return false;
}

Rect Enemy::getCollideRect()
{
	auto size = getContentSize();
	auto pos = getPosition();

	return Rect(pos.x - size.width / 2, pos.y - size.height / 4, size.width, size.height / 2);
}

Enemy* Enemy::create(EnemyInfo* pInfo)
{
	auto pRet = new Enemy;
	if ( pRet && pRet->init(pInfo) )
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}

bool Enemy::init(EnemyInfo* pInfo)
{
	do 
	{
		CC_BREAK_IF(!EntityObject::init() || !pInfo );

		m_pInfo = pInfo;

		this->initWithSpriteFrameName(m_pInfo->getTextureName());

		schedule(schedule_selector(Enemy::shoot), m_pInfo->getShootSpeed());
		return true;

	} while (0);
	return false;
}

void Enemy::shoot(float dt)
{
	do 
	{
		if (!m_pInfo) return;
		switch ( m_pInfo->getAttackModel() )
		{
		case AttackModel::Normal:
		case AttackModel::LockTarget:
		{
			float fMoveSpeed = m_pInfo->getMoveSpeed();
			float fBulletSpeed = fMoveSpeed * random(1.2f, 1.5f);
			auto bulletType = BulletType(fBulletSpeed, getPower(), s_enemybullet, m_pInfo->getAttackModel(), m_pInfo->getAttackScope());
			auto pBullet = Bullet::create(this, bulletType, g_szEnemyBullet);
			CC_BREAK_IF(!pBullet);

			auto pAction = createBulletAction(pBullet);
			if ( pAction )
			{
				UIManager::getInstance()->SendEvent(ControllerID::Game, GameEvent::NOFITY_ENEMY_SHOOT, (void*)pBullet);
				pBullet->runAction(pAction);
			}

		}
		break;
		case AttackModel::Boss:
		{
			
			bossShoot();
			bossSecondShoot();
		}
		break;
		default:
			break;
		}
		
	} while (0);

}

int Enemy::getPower()
{
	if (m_pInfo)
		return m_pInfo->getPower(); 
	return -1;
}

int Enemy::getHP()
{
	if (m_pInfo) 
		return m_pInfo->getHP();
	return -1;
}

const EnemyMoveType Enemy::getMoveType()
{
	if (m_pInfo) 
		return m_pInfo->getMoveType();
	return EnemyMoveType::MoveToEnd;
}

const AttackModel Enemy::getAttackModel() const
{
	if ( m_pInfo )
	{
		return m_pInfo->getAttackModel();
	}
	return AttackModel::Normal;
}

const float Enemy::getMoveSpeed() const
{
	if (m_pInfo)
		return m_pInfo->getMoveSpeed();
	return g_fMinMoveSpeed;
}

Action* Enemy::createBulletAction(Bullet* pBullet , Vec2 pos )
{
	Action* pAction = nullptr;
	do 
	{
		auto startPos = getPosition();
		auto endPos = startPos;
		float fTime = 0.f;
		CallFunc* pCall = nullptr;
		switch ( pBullet->getBulletType()->model )
		{
		case AttackModel::Normal:
		{
			
			//垂直发射子弹
			//飞机有旋转角度问题
			auto pRotateAngle = getRotation();
			endPos.y = -20;//让飞机飞出屏幕
			if (pRotateAngle > 0)
			{
				endPos.x = (startPos.y - endPos.y) / tan(CC_DEGREES_TO_RADIANS(90 + pRotateAngle)) + startPos.x;
			}
			else if (pRotateAngle < 0)
			{
				//点斜式 y2 - y1 = k * ( x2 - x1 )
				//x2 = (y2 - y1)/k + x1

				endPos.x = (startPos.y - endPos.y) / tan(CC_DEGREES_TO_RADIANS(90 - fabs(pRotateAngle))) + startPos.x;
			}

			fTime = startPos.distance(endPos) / pBullet->getBulletType()->fSpeed;

			auto pMoveTo = MoveTo::create(fTime, endPos);
			pCall = CallFunc::create(CC_CALLBACK_0(Enemy::onBulletMoveEnd, this,pBullet));
			pAction = Sequence::create(pMoveTo, pCall, nullptr);
		}
		break;
		case AttackModel::LockTarget:
		{
			auto param = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_AIRPLANE_POSITION);
			if ( param.isNull() || !param.asPointer() )
			{
				break;
			}
			endPos = *(Vec2*)param.asPointer();

			//先计算出斜率
			auto fSlope = (endPos.y - startPos.y) / (endPos.x - startPos.x);

			//点斜式 y2 - y1 = k * ( x2 - x1 )
			//x2 = (y2 - y1)/k + x1
			endPos.y = -20;
			endPos.x = (endPos.y - startPos.y) / fSlope + startPos.x;

			auto distance = startPos.distance(endPos);
			fTime = distance / pBullet->getBulletType()->fSpeed;
			pAction = MoveTo::create(fTime, endPos);
		}
		break;
		case  AttackModel::Boss:
		{
			auto distance = startPos.distance(pos);
			fTime = distance / pBullet->getBulletType()->fSpeed;
			auto pCall = CallFunc::create(CC_CALLBACK_0(Enemy::onBulletMoveEnd, this, pBullet));
			auto pMoveTo = MoveTo::create(fTime, pos);
			pAction = Sequence::createWithTwoActions(pMoveTo, pCall);
		}
		break;
		default:
			break;
		}
		
	} while (0);
	return pAction;
}

void Enemy::onBulletMoveEnd(Bullet* pBullet)
{
	if (!pBullet) return;
	UIManager::getInstance()->SendEvent(ControllerID::Game,GameEvent::NOTIFY_REMOVE_ENEMY_BULLET, (void*)pBullet);
}

void Enemy::bossShoot()
{
	do 
	{
		if (!m_pInfo) return;
		float fMoveSpeed = m_pInfo->getMoveSpeed();
		float fBulletSpeed = fMoveSpeed * random(1.2f, 1.5f);
		auto bulletType = BulletType(fBulletSpeed, getPower(), s_enemybullet, m_pInfo->getAttackModel(), m_pInfo->getAttackScope());
		//打出子弹的数量
		auto nCount = random(5, 10);

		auto startPos = getPosition();
		//计算角度(每个角多少度)
		auto fAngle = 360 / nCount;

		auto endPos = startPos;

		Bullet* pBullet = nullptr;
		Action* pAction = nullptr;
		auto posCenter = getPosition();//圆点
		//产生子弹(360)
		for (int i = 0; i < nCount; i++)
		{
			pBullet = Bullet::create(this, bulletType, g_szEnemyBullet);
			CC_BREAK_IF(!pBullet);

			auto fcos = cos(CC_DEGREES_TO_RADIANS(fAngle*i));
			auto fsin = sin(CC_DEGREES_TO_RADIANS(fAngle*i));

			//log("cos %d = %f ", fAngle *i, fcos);
			//log("sin %d = %f ", fAngle *i, fsin);
			//计算攻击范围
			endPos.x = fcos * m_pInfo->getAttackScope();
			endPos.y = fsin * m_pInfo->getAttackScope();
			//加上当前圆点坐标
			endPos += posCenter;

			pAction = createBulletAction(pBullet, endPos);
			if (pAction)
			{
				UIManager::getInstance()->SendEvent(ControllerID::Game, GameEvent::NOFITY_ENEMY_SHOOT, (void*)pBullet);
				pBullet->runAction(pAction);
			}

		}
	} while (0);
	
}

void Enemy::bossSecondShoot()
{
	if (!m_pInfo) return;
	auto pDelay = DelayTime::create(random(m_pInfo->getShootSpeed() + 0.2, m_pInfo->getShootSpeed() + 1.2));
	auto pCall = CallFunc::create(CC_CALLBACK_0(Enemy::bossShoot, this));
	auto pDelayCallAction = Sequence::createWithTwoActions(pDelay, pCall);
	this->runAction(pDelayCallAction);
}




