#include "GameMapView.h"

GameMapView::GameMapView()
{
	clear();
}

GameMapView::~GameMapView()
{
	clear();
}

bool GameMapView::init(UIViewControllerDelegate* pUIViewControllerDelegate)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!GameView::init(pUIViewControllerDelegate));

		bRet = createContent();
	} while (0);
	return bRet;
}

void GameMapView::clear()
{
	m_pBackSkySprite[0] = nullptr;
	m_pBackSkySprite[1] = nullptr;
	m_pGameMap[0] = nullptr;
	m_pGameMap[1] = nullptr;
}

bool GameMapView::createContent()
{
	bool bRet = false;
	do
	{
		auto& pSprit0 = m_pBackSkySprite[0];
		auto& pSprit1 = m_pBackSkySprite[1];
		pSprit0 = Sprite::createWithTexture(getTextureForKey(s_bg01));
		CC_BREAK_IF(!pSprit0);
		pSprit0->setAnchorPoint(Vec2::ZERO);
		addChild(pSprit0, (int)ZOder::Sky);

		pSprit1 = Sprite::createWithTexture(getTextureForKey(s_bg01));
		CC_BREAK_IF(!pSprit1);
		pSprit1->setAnchorPoint(Vec2::ZERO);
		addChild(pSprit1, (int)ZOder::Sky);
		pSprit1->setPosition(Vec2(0, pSprit0->getContentSize().height));

		//tile map
		auto& pMap0 = m_pGameMap[0];
		auto& pMap1 = m_pGameMap[1];
		pMap0 = TMXTiledMap::create(s_level01);
		CC_BREAK_IF(!pMap0);
		addChild(pMap0, (int)ZOder::Map);


		pMap1 = TMXTiledMap::create(s_level01);
		CC_BREAK_IF(!pMap1);
		addChild(pMap1, (int)ZOder::Map);

		pSprit0->runAction(createMoveAction());
		pSprit1->runAction(createMoveAction());

		pMap0->runAction(createMoveAction(false));
		pMap1->runAction(createMoveAction(false));

		//m_pGameMap->runAction(Sequence::create(pMapMoveBy, pMapCall, nullptr));
		schedule(schedule_selector(GameMapView::onSkyAndMapMoving), 0.1f);

		bRet = true;
	} while (0);
	return bRet;
}

Action* GameMapView::createMoveAction(bool bIsSky /*= true*/)
{
	do
	{
		auto fy = bIsSky ? -g_fSkyMoveDistance : -g_fMapMoveDiatance;
		auto pMoveBy = MoveBy::create(g_fMapMoveSpeed, Vec2(0, fy));
		CC_BREAK_IF(!pMoveBy);
		CallFunc* pCall = nullptr;
		if (bIsSky)
		{
			pCall = CallFunc::create(CC_CALLBACK_0(GameMapView::onMoveSkyEnd, this));
		}
		else
		{
			pCall = CallFunc::create(CC_CALLBACK_0(GameMapView::onMoveMapEnd, this));
		}
		CC_BREAK_IF(!pCall);
		auto pAction = Sequence::create(pMoveBy, pCall, nullptr);
		CC_BREAK_IF(!pAction);
		return pAction;
	} while (0);
	return nullptr;
}

void GameMapView::onSkyAndMapMoving(float dt)
{
	auto& pSky0 = m_pBackSkySprite[0];
	auto& pSky1 = m_pBackSkySprite[1];
	if (pSky0 && pSky1)
	{
		//说明pSky0已经超出了屏幕显示区域
		//恢复位置到pSky1上
		if (abs(pSky0->getPositionY()) >= pSky0->getContentSize().height)
		{
			pSky0->setPositionY(pSky1->getPositionY() + pSky1->getContentSize().height);
			onMoveSkyEnd();
		}

		//说明pSky1已经超出了屏幕显示区域
		//恢复位置到pSky0上
		if (abs(pSky1->getPositionY()) >= pSky1->getContentSize().height)
		{
			pSky1->setPositionY(pSky0->getPositionY() + pSky0->getContentSize().height);
			onMoveSkyEnd();
		}
	}

	auto& pMap0 = m_pGameMap[0];
	auto& pMap1 = m_pGameMap[1];
	if (pMap0 && pMap1)
	{
		//说明pMap0已经超出了屏幕显示区域
		//恢复位置到pMap1上
		if (abs(pMap0->getPositionY()) >= pMap0->getContentSize().height)
		{
			pMap0->setPositionY(pMap1->getPositionY() + pMap1->getContentSize().height);
			onMoveMapEnd();
		}

		//说明pMap1已经超出了屏幕显示区域
		//恢复位置到pMap0上
		if (abs(pMap1->getPositionY()) >= pMap1->getContentSize().height)
		{
			pMap1->setPositionY(pMap0->getPositionY() + pMap0->getContentSize().height);
			onMoveMapEnd();
		}
	}
}

void GameMapView::onMoveSkyEnd()
{
	do
	{
		auto &pSprite0 = m_pBackSkySprite[0];
		auto &pSprite1 = m_pBackSkySprite[1];
		CC_BREAK_IF(!pSprite0 || !pSprite1);
		pSprite0->stopAllActions();
		pSprite1->stopAllActions();
		pSprite0->runAction(createMoveAction());
		pSprite1->runAction(createMoveAction());
	} while (0);
}

void GameMapView::onMoveMapEnd()
{
	do
	{
		auto& pMap0 = m_pGameMap[0];
		auto& pMap1 = m_pGameMap[1];
		CC_BREAK_IF(!pMap0 || !pMap1);
		pMap0->stopAllActions();
		pMap1->stopAllActions();
		pMap0->runAction(createMoveAction(false));
		pMap1->runAction(createMoveAction(false));
	} while (0);
}
