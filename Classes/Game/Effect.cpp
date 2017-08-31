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

		//设置混合模式
		pFlare->setBlendFunc(BlendFunc::ADDITIVE);
		
		pParent->addChild(pFlare, nZOder);

		//透明度
		pFlare->setOpacity(0);

		pFlare->setPosition(pos);

		pFlare->setRotation(fRotation);

		pFlare->setScale(0.2f);

		//透明渐变
		auto pOpacityFull = FadeTo::create(fDuration, 255);
		auto pOpacityEmpty = FadeTo::create(fDuration, 0);

		//大小渐变
		auto pChangeSize = ScaleBy::create(0.7f, 1.2f);

		//渐变速度
		auto pBigEase = EaseSineOut::create(pChangeSize);
		auto pMove = MoveBy::create(fDuration * 2 , Vec2(winSize.width, 0));
		auto pMoveEase = EaseSineOut::create(pMove);

		//角度旋转
		auto pRotate = RotateBy::create(fDuration * 2, 45);

		// 角度旋转速度，指数变化
		auto pRotateEase = EaseExponentialOut::create(pRotate);

		// 放大到原大小
		auto pRecoverSize = ScaleTo::create(fDuration, 1);

		// 动画完成后回调函数,干掉精灵
		auto pRemoveFunc = CallFunc::create(CC_CALLBACK_0(Effect::playEnd, this, pFlare));

		// 执行动画和回调函数
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

		// 完成之后的回调
		auto pPlayEndFunc = CCCallFunc::create(CC_CALLBACK_0(Effect::playEnd,this,pSprite));

		// 爆炸动画
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

		//设置混合模式
		pSpriteOne->setBlendFunc(BlendFunc::ADDITIVE);
		pSpriteTwo->setBlendFunc(BlendFunc::ADDITIVE);
		pSpriteThree->setBlendFunc(BlendFunc::ADDITIVE);

		//设置位置
		pSpriteOne->setPosition(pos);
		pSpriteTwo->setPosition(pos);
		pSpriteThree->setPosition(pos);

		pParent->addChild(pSpriteOne,nZOder);
		pParent->addChild(pSpriteTwo, nZOder);
		pParent->addChild(pSpriteThree, nZOder);

		//设置缩放大小
		pSpriteOne->setScale(fScale);
		pSpriteTwo->setScale(fScale);
		pSpriteThree->setScale(fScale);

		pSpriteThree->setRotation(rand_0_1() * 360);

		//向负方向的旋转
		auto pRotateNegative = RotateBy::create(fDuration, -45);
		//向正方向的旋转
		auto pRotatePositive = RotateBy::create(fDuration, 45);
		//缩放
		auto pScaleBy = ScaleBy::create(fDuration, 3);
		//消隐
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

