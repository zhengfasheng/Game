#pragma once
#include "cocos2d.h"
USING_NS_CC;

class EntityObject : public Sprite
{
public:
	EntityObject(){}
	virtual ~EntityObject(){}

	virtual bool init() override{ return Sprite::init(); }

	//�ͷŶ���
	virtual void destory() = 0;
	//�����ܵ�����
	virtual void hurt( int nValue ) = 0;
	//�����ܵ�ȫ��Ĺ����˺���Ҳ����һ������
	virtual void hurt() = 0;
	//�����Ƿ����
	virtual bool isLive() = 0;
	//�õ���ײ���Ե�Rect
	virtual Rect getCollideRect() = 0;
	//�õ�ʵ��Ĺ����˺�
	virtual int getPower() = 0;
	//�õ�ʵ���Ѫ��
	virtual int getHP() = 0;
};