#include "Bullet.h"
#include "Effect.h"
#include "Airplane.h"

Bullet::Bullet() 
	:m_nHP(g_nHP),
	m_pType(nullptr)
{
	
}

Bullet::~Bullet()
{
	
}

Bullet* Bullet::create(EntityObject* pSrcObj, BulletType type,const std::string& szName)
{
	auto pRet = new(std::nothrow) Bullet();
	if (pRet && pRet->init(pSrcObj,type,szName))
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

bool Bullet::init(EntityObject* pSrcObj, BulletType type, const std::string& szName)
{
	do 
	{
		CC_BREAK_IF(!EntityObject::init());
		CC_BREAK_IF(!pSrcObj);
		m_pType = type.clone();
		CC_BREAK_IF(!m_pType);
		this->initWithSpriteFrameName(m_pType->szTextureName);
		this->setBlendFunc(BlendFunc::ADDITIVE);
		this->setName(szName);

		auto pos = pSrcObj->getPosition();
		auto size = pSrcObj->getContentSize();
		auto newPos = pos;
		if ( szName == g_szLeftBullet )
		{
			newPos = Vec2(pos.x - g_fBulletOffset, pos.y + 3 + size.height * 0.3);
		}
		else if ( szName == g_szRightBullet )
		{
			newPos = Vec2(pos.x + g_fBulletOffset, pos.y + 3 + size.height * 0.3);
		}
		else if ( szName == g_szEnemyBullet )
		{
			newPos = Vec2(pos.x, pos.y - size.height*0.2);
		}

		this->setPosition(newPos);
		return true;
	} while (0);
	return false;
}

void Bullet::destory()
{
	do 
	{
		//×Óµ¯±¬Õ¨ÌØÐ§
		auto pParent = this->getParent();
		CC_BREAK_IF(!pParent);

		this->stopAllActions();
		this->removeFromParentAndCleanup(true);


	} while (0);
	
}

void Bullet::hurt( int nValue )
{
	hurt();
}

void Bullet::hurt()
{
	m_nHP = 0;
}

bool Bullet::isLive()
{
	return m_nHP > 0;
}

Rect Bullet::getCollideRect()
{
	auto pos = this->getPosition();
	return Rect(pos - Vec2(3,3), Size(6, 6));
}

int Bullet::getPower()
{
	return m_pType->nPower;
}

int Bullet::getHP()
{
	return m_nHP;
}

void Bullet::update(float delta)
{

}


