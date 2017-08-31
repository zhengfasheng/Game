#pragma once
#include "cocos2d.h"
USING_NS_CC;

class EntityObject : public Sprite
{
public:
	EntityObject(){}
	virtual ~EntityObject(){}

	virtual bool init() override{ return Sprite::init(); }

	//释放对象
	virtual void destory() = 0;
	//对象受到攻击
	virtual void hurt( int nValue ) = 0;
	//对象受到全额的攻击伤害，也就是一击毙命
	virtual void hurt() = 0;
	//对象是否活着
	virtual bool isLive() = 0;
	//得到碰撞测试的Rect
	virtual Rect getCollideRect() = 0;
	//得到实体的攻击伤害
	virtual int getPower() = 0;
	//得到实体的血量
	virtual int getHP() = 0;
};