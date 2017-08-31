#include "Effect.h"

Effect::Effect()
{

}

Effect::~Effect()
{

}


bool Effect::init()
{
	return Node::init();
}

void Effect::playFlareEffect(Node* pParent , int nZOder , Vec2 pos , float fRotation , float fDuration , CallFunc* pCall )
{
	do 
	{
		CC_BREAK_IF(!pParent);
		auto pFlare = Sprite::createWithTexture(getTextureForKey(s_flare));
		CC_BREAK_IF(!pFlare);
		
		auto winSize = Director::getInstance()->getWinSize();

		pFlare->setName("flare effect");

		//���û��ģʽ
		pFlare->setBlendFunc(BlendFunc::ADDITIVE);
		
		pParent->addChild(pFlare, nZOder);

		//͸����
		pFlare->setOpacity(0);

		pFlare->setPosition(pos);

		pFlare->setRotation(fRotation);

		pFlare->setScale(0.2f);

		//͸������
		auto pOpacityFull = FadeTo::create(fDuration, 255);
		auto pOpacityEmpty = FadeTo::create(fDuration, 0);

		//��С����
		auto pChangeSize = ScaleBy::create(0.7f, 1.2f);

		//�����ٶ�
		auto pBigEase = EaseSineOut::create(pChangeSize);
		auto pMove = MoveBy::create(fDuration * 2 , Vec2(winSize.width, 0));
		auto pMoveEase = EaseSineOut::create(pMove);

		//�Ƕ���ת
		auto pRotate = RotateBy::create(fDuration * 2, 45);

		// �Ƕ���ת�ٶȣ�ָ���仯
		auto pRotateEase = EaseExponentialOut::create(pRotate);

		// �Ŵ�ԭ��С
		auto pRecoverSize = ScaleTo::create(fDuration, 1);

		// ������ɺ�ص�����,�ɵ�����
		auto pRemoveFunc = CallFunc::create(CC_CALLBACK_0(Effect::playEnd, this, pFlare));

		// ִ�ж����ͻص�����
		pFlare->runAction(CCSequence::create(pOpacityFull, pOpacityEmpty, pRemoveFunc, pCall,nullptr));
		pFlare->runAction(pMoveEase);
		pFlare->runAction(pRotateEase);
		pFlare->runAction(pRecoverSize);

	} while (0);
	

}

void Effect::playExplodeEffect(Node* pParent, int nZOder, Vec2 pos, CallFunc* pCall /* = nullptr */)
{
	do {
		CC_BREAK_IF(!pParent);
		auto pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(g_szExplosionFirstFrame);
		auto pSprite = Sprite::createWithSpriteFrame(pFrame);
		pParent->addChild(pSprite,nZOder);
		pSprite->setPosition(pos);
		pSprite->setName("explode effect");

		auto size = pSprite->getContentSize();

		// ���֮��Ļص�
		auto pPlayEndFunc = CCCallFunc::create(CC_CALLBACK_0(Effect::playEnd,this,pSprite));

		// ��ը����
		auto pAnimation = AnimationCache::getInstance()->getAnimation(g_szExplosion);
		Action* pAction = nullptr;
		if ( pCall )
		{
			pAction = CCSequence::create(Animate::create(pAnimation), pPlayEndFunc, pCall, nullptr);
		}
		else
		{
			pAction = CCSequence::create(Animate::create(pAnimation), pPlayEndFunc, nullptr);
		}
		
		pSprite->runAction(pAction);

	} while (0);
}

void Effect::playSparkEffect(Node* pParent, int nZOder, Vec2 pos, float fScale /* = 1.2f */, float fDuration /* = 0.7f */)
{
	do 
	{
		CC_BREAK_IF(!pParent);

		auto pSpriteOne = Sprite::createWithTexture(getTextureForKey(s_explode1));
		auto pSpriteTwo = Sprite::createWithTexture(getTextureForKey(s_explode2));
		auto pSpriteThree = Sprite::createWithTexture(getTextureForKey(s_explode3));

		CC_BREAK_IF(!(pSpriteOne && pSpriteTwo && pSpriteThree));

		pSpriteOne->setName("spark one");
		pSpriteTwo->setName("spark two");
		pSpriteThree->setName("spark three");

		//���û��ģʽ
		pSpriteOne->setBlendFunc(BlendFunc::ADDITIVE);
		pSpriteTwo->setBlendFunc(BlendFunc::ADDITIVE);
		pSpriteThree->setBlendFunc(BlendFunc::ADDITIVE);

		//����λ��
		pSpriteOne->setPosition(pos);
		pSpriteTwo->setPosition(pos);
		pSpriteThree->setPosition(pos);

		pParent->addChild(pSpriteOne,nZOder);
		pParent->addChild(pSpriteTwo, nZOder);
		pParent->addChild(pSpriteThree, nZOder);

		//�������Ŵ�С
		pSpriteOne->setScale(fScale);
		pSpriteTwo->setScale(fScale);
		pSpriteThree->setScale(fScale);

		pSpriteThree->setRotation(rand_0_1() * 360);

		//�򸺷������ת
		auto pRotateNegative = RotateBy::create(fDuration, -45);
		//�����������ת
		auto pRotatePositive = RotateBy::create(fDuration, 45);
		//����
		auto pScaleBy = ScaleBy::create(fDuration, 3);
		//����
		auto pFadeOut = FadeOut::create(fDuration);

		auto pCallOne = CallFunc::create(CC_CALLBACK_0(Effect::playEnd,this,pSpriteOne));
		auto pCallTwo = CallFunc::create(CC_CALLBACK_0(Effect::playEnd, this, pSpriteTwo));
		auto pCallThree = CallFunc::create(CC_CALLBACK_0(Effect::playEnd, this, pSpriteThree));

		auto pActionOne = Sequence::createWithTwoActions(pFadeOut, pCallOne);
		auto pActionTwo = Sequence::createWithTwoActions(pFadeOut->clone(), pCallTwo);
		auto pActionThree = Sequence::createWithTwoActions(pFadeOut->clone(), pCallThree);

		pSpriteOne->runAction(pRotateNegative);
		pSpriteTwo->runAction(pRotatePositive);

		pSpriteOne->runAction(pScaleBy);
		pSpriteTwo->runAction(pScaleBy->clone());
		pSpriteThree->runAction(pScaleBy->clone());
		
		
		pSpriteOne->runAction(pActionOne);
		pSpriteTwo->runAction(pActionTwo);
		pSpriteThree->runAction(pActionThree);

	} while (0);

}

void Effect::playEnd(Node* pSender)
{
	if ( pSender )
	{
		//log("%s play end", pSender->getName().data());
		pSender->removeFromParentAndCleanup(true);
	}
}

