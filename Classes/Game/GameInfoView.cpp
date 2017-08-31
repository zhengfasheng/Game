#include "GameInfoView.h"
#include "Language.h"
#include "GameEvent.h"
#include "UIManager.h"

GameInfoView::GameInfoView()
	:m_pScoreText(nullptr)
{
	m_pLifeCountSpriteVec.resize(g_nMaxLife);
	for (auto& p : m_pLifeCountSpriteVec)
	{
		p = nullptr;
	}
}

GameInfoView::~GameInfoView()
{
	m_pLifeCountSpriteVec.clear();
}

bool GameInfoView::init(UIViewControllerDelegate* pUIViewControllerDelegate)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!GameView::init(pUIViewControllerDelegate));

		auto winSize = Director::getInstance()->getWinSize();
		//增加分数标签
		m_pScoreText = TextBMFont::create(Language::getInstance()->getStringWithParam("game_over.score",0), Language::getInstance()->getArial14Font());
		CC_BREAK_IF(!m_pScoreText);
		m_pScoreText->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		addChild(m_pScoreText);
		m_pScoreText->setPosition(Size(winSize.width - 5, winSize.height - 30));

		//创建生命指示
		auto pPalneTexture = getTextureForKey(s_ship01);
		CC_BREAK_IF(!pPalneTexture);
		for (auto &pLife : m_pLifeCountSpriteVec)
		{
			pLife = Sprite::createWithTexture(pPalneTexture, g_planeRect[0]);
			if (!pLife)
				continue;
			pLife->setScale(0.6f);
			pLife->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
			addChild(pLife);
		}
		//设置生命指示位置
		for (size_t i = 0; i < m_pLifeCountSpriteVec.size(); i++)
		{
			auto& pLife = m_pLifeCountSpriteVec[i];
			if (!pLife)
				continue;
			pLife->setPosition(Vec2(i * pLife->getContentSize().width * pLife->getScale(), winSize.height - 20));
		}

		//创建暂停按钮
		auto pPauseBtn = Button::create();
		CC_BREAK_IF(!pPauseBtn);
		pPauseBtn->loadTextureNormal(s_pause, Widget::TextureResType::PLIST);
		pPauseBtn->loadTexturePressed(s_pause, Widget::TextureResType::PLIST);
		pPauseBtn->setPressedActionEnabled(true);
		pPauseBtn->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		pPauseBtn->setPosition(Vec2(winSize.width, 10));
		addChild(pPauseBtn);
		pPauseBtn->addClickEventListener(CC_CALLBACK_1(GameInfoView::onGamePause, this));

		bRet = true;
	} while (0);
	return bRet;
}

void GameInfoView::onGamePause(Ref* pSender)
{
	UIManager::getInstance()->SendEvent(ControllerID::Game,GameEvent::NOTITY_GAME_PAUSE);
}

void GameInfoView::decreaseRebornTimes( int nLife )
{
	if ( nLife < 0 || nLife >= m_pLifeCountSpriteVec.size() )
	{
		return;
	}
	//现在只减不增,先不考虑其它情况
	if (m_pLifeCountSpriteVec[nLife])
	{
		//播放一个动画闪烁，减少生命显示器
		Sprite*& pLifeSprite = m_pLifeCountSpriteVec[nLife];
		auto pBlink = Blink::create(3, 3);
		auto pCall = CallFunc::create([pLifeSprite](){
			pLifeSprite->setVisible(false);
		});
		auto pAction = Sequence::createWithTwoActions(pBlink, pCall);

		pLifeSprite->runAction(pAction);
	}
}

void GameInfoView::setScore(int nScore)
{
	if ( m_pScoreText )
	{
		m_pScoreText->setString(toString(nScore));
	}
}

