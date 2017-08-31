
#include "Airplane.h"
#include "Bullet.h"
#include "GameConfig.h"
#include "commontools.h"
#include "Resource.h"
#include "UIView.h"
#include "SoundHelper.h"
#include "Effect.h"
#include "GameEvent.h"
#include "UIManager.h"
#include "AirplaneLevelManager.h"

Airplane::Airplane()
	:m_nBulletSpeed(g_fBulletSpeed),
	m_nHP(g_nHP),
	m_bCanAttack(false),
	m_nPower(g_nPower),
	m_appearPosition(g_defaultPlanePosition),
	m_fShootSpeed(g_fMinShootSpeed / 2),
	m_nLevel(0)
{

}

Airplane::~Airplane()
{

}

Airplane* Airplane::create(int nLevel , int nPower , float fShootSpeed )
{
	auto pRet = new Airplane;
	if ( pRet && pRet->init(nLevel,nPower,fShootSpeed) )
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool Airplane::init(int nLevel, int nPower, float fShootSpeed)
{
	do 
	{
		CC_BREAK_IF(!EntityObject::init());
		//����Ĭ��λ��
		this->setPosition(m_appearPosition);
		//�����ɻ�֡����
		auto nCount = sizeof(g_planeRect) / sizeof(Rect);
		Vector<SpriteFrame*> pAniFrames;
		auto pTexture = getTextureForKey(s_ship01);
		for ( decltype(nCount) i = 1 ; i < nCount ;i++)
		{
			auto pFrame = SpriteFrame::createWithTexture(pTexture, g_planeRect[i]);
			pAniFrames.pushBack(pFrame);
		}

		auto pAnimation = Animation::createWithSpriteFrames(pAniFrames, 0.1f);
		auto pAnimate = Animate::create(pAnimation);
		this->runAction(RepeatForever::create(pAnimate));

		//���ó�������
		auto pDelay = DelayTime::create(g_fAttackedTime);

		auto pCall = CallFunc::create([this]()
		{
			this->setCanAttaked(true);
		});
		this->runAction(Sequence::create(pDelay, pCall, nullptr));

		//���÷ɻ��ȼ�
		m_nLevel = nLevel;
		//���ù�����
		m_nPower = nPower;
		//��������ٶ�
		m_fShootSpeed = fShootSpeed;

		//��ʼ���
		startShoot();

		return true;
	} while (0);
	return false;
}

void Airplane::shoot(float dt)
{
	do 
	{
		auto bulletType = BulletType(m_nBulletSpeed, m_nPower,s_myBullet,AttackModel::Normal,attackScope());
		//�����ɻ�����ӵ�
		auto pBulletLeft = Bullet::create(this, bulletType,g_szLeftBullet);
		CC_BREAK_IF(!pBulletLeft);

		//�����ɻ��ұ��ӵ�
		auto pBulletRight = Bullet::create(this, bulletType,g_szRightBullet);
		CC_BREAK_IF(!pBulletRight);
		
		auto pLeftAction = createBulletAction(pBulletLeft);
		if (pLeftAction )
		{
			UIManager::getInstance()->SendEvent(ControllerID::Game, GameEvent::NOTIFY_AIRPLANE_SHOOT, (void*)pBulletLeft);
			pBulletLeft->runAction(pLeftAction);
		}

		auto pRightAction = createBulletAction(pBulletRight);
		if ( pRightAction )
		{
			UIManager::getInstance()->SendEvent(ControllerID::Game, GameEvent::NOTIFY_AIRPLANE_SHOOT, (void*)pBulletRight);
			pBulletRight->runAction(pRightAction);
		}

		//�����������
		SoundHelper::getInstance()->playAudio(SoundHelper::AudioType::Fire);

	} while (0);

}

void Airplane::hurt( int nValue )
{
	if ( m_bCanAttack )
	{
		m_nHP -= nValue;
	}
}

void Airplane::hurt()
{
	if ( m_bCanAttack )
	{
		hurt(m_nHP);
	}
}

void Airplane::destory()
{
	//ֹͣ�����ӵ�
	unschedule(schedule_selector(Airplane::shoot));
	m_bCanAttack = false;

	//ֹͣ�л������
	UIManager::getInstance()->SendEvent(ControllerID::Game,GameEvent::NOTITY_STOP_ADD_ENEMY);

	SoundHelper::getInstance()->playAudio(SoundHelper::AudioType::PlaneDestroy);

	//�����¼�˵���Լ��Ѿ�����
	UIManager::getInstance()->SendEvent(ControllerID::Game,GameEvent::NOTITY_MY_AIRPLANE_DESTORY);

	auto pNoticeRebron = CCCallFunc::create([](){
		//֪ͨս������
		UIManager::getInstance()->SendEvent(ControllerID::Game, GameEvent::NOTIFY_MY_AIRPLANE_REBORN);
	});

	//����һ������
	
	auto pEffect = Effect::create();
	if ( pEffect )
	{
		pEffect->playExplodeEffect(this->getParent(), (int)OpViewZOrder::Effect,getPosition(), pNoticeRebron);
	}

	this->removeFromParentAndCleanup(true);


}

bool Airplane::isLive()
{
	return m_nHP > 0 ;
}

Rect Airplane::getCollideRect()
{
	auto pos = getPosition();
	auto size = getContentSize();
	return Rect(pos.x - size.width/2,pos.y - size.height/2,size.width/2,size.height/2);
}

int Airplane::getPower()
{
	return m_nPower;
}

int Airplane::getHP()
{
	return m_nHP;
}

void Airplane::setLevel(int nValue)
{
	if (m_nLevel == nValue)
		return;
	m_nLevel = nValue;
	auto param = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_AIRPLANE_LEVEL_INFO);
	if ( param.isNull() || !param.asPointer() )
	{
		return;
	}

	AirplaneLevel* pInfo = (AirplaneLevel*)param.asPointer();
	setShootSpeed(pInfo->getShootSpeed());
	m_nPower = pInfo->getPower();
}

void Airplane::setShootSpeed(float fSpeed)
{
	changeShootSpeed(fSpeed);
}

void Airplane::startShoot()
{
	//���õ��ȣ������ӵ�
	schedule(schedule_selector(Airplane::shoot), m_fShootSpeed);
}

void Airplane::changeShootSpeed(float fSpeed)
{
	unschedule(schedule_selector(Airplane::shoot));
	schedule(schedule_selector(Airplane::shoot), fSpeed);
}

Action* Airplane::createBulletAction(Bullet* pBullet)
{
	Action* pAction = nullptr;
	do 
	{
		CCAssert(pBullet, "bullet is null");
		//�����ӵ��Ķ���
		auto startPos = pBullet->getPosition();
		auto endPos = startPos;
		endPos.y = startPos.y + pBullet->getBulletType()->fAttackScope;
		auto fTime = endPos.y / pBullet->getBulletType()->fSpeed;
		auto pMoveto = MoveTo::create(fTime, endPos);
		auto pCall = CallFunc::create(CC_CALLBACK_0(Airplane::onBulletMoveEnd, this, pBullet));
		pAction = Sequence::createWithTwoActions(pMoveto, pCall);
	} while (0);
	return pAction;
}

void Airplane::onBulletMoveEnd(Bullet* pBullet)
{
	if (!pBullet) return;
	UIManager::getInstance()->SendEvent(ControllerID::Game,GameEvent::NOTIFY_REMOVE_MY_BULLET, (void*)pBullet);
}
