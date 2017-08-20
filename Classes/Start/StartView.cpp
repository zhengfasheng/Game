#include "StartView.h"
#include "common.h"
#include "SoundHelper.h"

StartView::StartView()
{

}

StartView::~StartView()
{

}

bool StartView::init(UIViewControllerDelegate* pDelegate)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!UIView::init(pDelegate));

		//添加背景图片
		auto pBackground = Sprite::createWithTexture(getTextureForKey(s_loading));

		if (pBackground)
		{
			pBackground->setAnchorPoint(Vec2::ZERO);
			addChild(pBackground);
		}

		auto winSize = Director::getInstance()->getWinSize();

		//添加logo
		auto pLogo = Sprite::createWithTexture(getTextureForKey(s_logo));

		if (pLogo)
		{
			pLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
			pLogo->setPosition(Vec2(winSize.width / 2, winSize.height - 50));
			addChild(pLogo, (int)SpriteLayout::Logo);
		}

		//创建菜单

		auto fWidth = g_fMenuWidth;
		auto fHeight = g_fMenuHeight;
		auto pNewGameNormal = Sprite::createWithTexture(getTextureForKey(s_menu), Rect(0, 0, fWidth, fHeight));
		auto pNewGameSelected = Sprite::createWithTexture(getTextureForKey(s_menu), Rect(0, fHeight, fWidth, fHeight));

		auto pSettingNormal = Sprite::createWithTexture(getTextureForKey(s_menu), Rect(fWidth, 0, fWidth, fHeight));
		auto pSettingSelected = Sprite::createWithTexture(getTextureForKey(s_menu), Rect(fWidth, fHeight, fWidth, fHeight));

		auto pAboutNormal = Sprite::createWithTexture(getTextureForKey(s_menu), Rect(fWidth * 2, 0, fWidth, fHeight));
		auto pAboutSelected = Sprite::createWithTexture(getTextureForKey(s_menu), Rect(fWidth * 2, fHeight, fWidth, fHeight));


		auto pNewGame = MenuItemSprite::create(pNewGameNormal, pNewGameSelected, CC_CALLBACK_1(StartView::onNewGame, this));

		auto pSetting = MenuItemSprite::create(pSettingNormal, pSettingSelected, CC_CALLBACK_1(StartView::onSetting, this));

		auto pAbout = MenuItemSprite::create(pAboutNormal, pAboutSelected, CC_CALLBACK_1(StartView::onAbout, this));

		//创建菜单
		auto pMenu = Menu::create(pNewGame, pSetting, pAbout, nullptr);

		if (pMenu)
		{
			pMenu->alignItemsVerticallyWithPadding(20);
			addChild(pMenu, (int)SpriteLayout::Menu);
			pMenu->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 80));
		}

		//创建在主界面随机飞行的小飞机

		m_pFlyPlane = Sprite::createWithTexture(getTextureForKey(s_ship01), g_planeRect[1]);

		if (m_pFlyPlane)
		{
			auto pos = Vec2(random<float>(0, winSize.width), 0);
			m_pFlyPlane->setPosition(pos);

			addChild(m_pFlyPlane, (int)SpriteLayout::Plane);
			auto pAction = MoveBy::create(2, Vec2(random<float>(0, winSize.width), pos.y + winSize.height));

			auto call = CallFunc::create(CC_CALLBACK_0(StartView::flyEndCallback, this));

			m_pFlyPlane->runAction(Sequence::create(pAction, call, nullptr));

			schedule(schedule_selector(StartView::onFlying), 0.1f);

		}

		SoundHelper::getInstance()->playBackgroundMusic(SoundHelper::BackgroundMusicType::BackMusic);

		bRet = true;
	} while (0);
	return bRet;
}

void StartView::onNewGame(Ref* pSender)
{
	if ( getDelegate() )
	{
		getDelegate()->SendEvent(UIEvent::EVENT_START_NEW_GAME);
	}
}

void StartView::onAbout(Ref* pSender)
{
	if ( getDelegate() )
	{
		getDelegate()->SendEvent(UIEvent::EVENT_OPEN_ABOUT);
	}
}

void StartView::onSetting(Ref* pSender)
{
	if ( getDelegate() )
	{
		getDelegate()->SendEvent(UIEvent::EVENT_OPENT_SETTING);
	}
}

void StartView::flyEndCallback()
{
	if (m_pFlyPlane)
	{
		auto winSize = Director::getInstance()->getWinSize();
		auto pos = Vec2(random<float>(0, winSize.width), 10);
		m_pFlyPlane->setPosition(pos);

		auto pAction = MoveBy::create(3 * random(0, 1), Vec2(random<float>(0, winSize.width), pos.y + winSize.height));

		auto call = CallFunc::create(CC_CALLBACK_0(StartView::flyEndCallback, this));

		m_pFlyPlane->runAction(Sequence::create(pAction, call, nullptr));

	}
}

void StartView::onFlying(float dt)
{
	if (m_pFlyPlane)
	{
		auto winSize = Director::getInstance()->getWinSize();
		if (m_pFlyPlane->getPositionX() > winSize.width || m_pFlyPlane->getPositionY() > winSize.height)
		{
			m_pFlyPlane->stopAllActions();

			flyEndCallback();
		}
	}
}

