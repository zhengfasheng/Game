#include "GameOverView.h"
#include "ui/CocosGUI.h"
#include "CurrentPlayerInfo.h"
#include "Language.h"
#include "UIEvent.h"

using namespace cocos2d::ui;
GameOverView::GameOverView()
{

}

GameOverView::~GameOverView()
{

}

bool GameOverView::init(UIViewControllerDelegate* pDelegate)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!UIView::init(pDelegate));
		auto pBackground = Sprite::createWithTexture(getTextureForKey(s_loading));
		CC_BREAK_IF(!pBackground);
		pBackground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		addChild(pBackground);
		auto winSize = Director::getInstance()->getWinSize();
		//添加标题
		auto pGameOverTitle = Sprite::createWithTexture(getTextureForKey(s_gameOver));
		CC_BREAK_IF(!pGameOverTitle);
		pGameOverTitle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
		pGameOverTitle->setPosition(Vec2(winSize.width / 2, winSize.height - 50));
		addChild(pGameOverTitle);

		//当前分数标签title

		auto pLayout = Layout::create();
		CC_BREAK_IF(!pLayout);
		pLayout->setLayoutType(Layout::Type::VERTICAL);
		pLayout->setContentSize(Size(winSize.width, winSize.height - pGameOverTitle->getContentSize().height - 50));
		addChild(pLayout);
		pLayout->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

		//显示分数相关信息（当前分数与最低分数）
		auto nScore = CurrentPlayerInfo::getInstance()->getUserInfo().getScore();
		auto nBestScore = CurrentPlayerInfo::getInstance()->getUserInfo().getBestScore();

		auto pScoreText = Text::create(Language::getInstance()->getStringWithParam("game_over.score",nScore), "", 24);
		auto pBestScoreText = Text::create(Language::getInstance()->getStringWithParam("game_over.best_score",nBestScore), "", 24);
		CCASSERT(pScoreText && pBestScoreText, "create score text failed");

		auto pLayoutParameter = LinearLayoutParameter::create();
		CC_BREAK_IF(!pLayoutParameter);
		pLayoutParameter->setGravity(LinearLayoutParameter::LinearGravity::LEFT);
		pLayoutParameter->setMargin(Margin(30, 30, 0, 0));
		pScoreText->setLayoutParameter(pLayoutParameter);
		pBestScoreText->setLayoutParameter(pLayoutParameter);

		pLayout->addChild(pScoreText);
		pLayout->addChild(pBestScoreText);

		//添加返回按钮
		auto pGoBackLabel = TextBMFont::create(Language::getInstance()->getString("about.go_back"), Language::getInstance()->getBitmapFont());
		CC_BREAK_IF(!pGoBackLabel);
		auto pGoBackItem = MenuItemLabel::create(pGoBackLabel, [this](Ref* pSender){
			if (getDelegate())
			{
				getDelegate()->SendEvent(UIEvent::EVENT_GAME_OVER_GO_BACK);
			}
		});
		CC_BREAK_IF(!pGoBackItem);

		//添加重试按钮
		auto pTryAgain = TextBMFont::create(Language::getInstance()->getString("about.try_again"), Language::getInstance()->getBitmapFont());
		CC_BREAK_IF(!pTryAgain);
		auto pTryAgainItem = MenuItemLabel::create(pTryAgain, [this](Ref* pSender){
			if (getDelegate())
				getDelegate()->SendEvent(UIEvent::EVNET_GAME_OVER_TRY_AGAIN);
		});
		CC_BREAK_IF(!pTryAgainItem);

		//这个Menu在不设置大小的情况下，ContentSize就是winsize
		auto pMenu = Menu::create(pTryAgainItem, pGoBackItem, nullptr);
		CC_BREAK_IF(!pMenu);
		pMenu->setContentSize(Size(winSize.width, pGoBackItem->getContentSize().height * 2 + 50));
		addChild(pMenu);
		pMenu->alignItemsVerticallyWithPadding(20);
		pMenu->setPosition(winSize.width / 2, (pGoBackItem->getContentSize().height + 40));

		//设置按钮动画效果

		pGoBackItem->runAction(getMenuItemAction());
		pTryAgainItem->runAction(getMenuItemAction());
		bRet = true;
	} while (0);
	return bRet;
}

Action* GameOverView::getMenuItemAction()
{
	return [](){
		auto pActionFadeIn = FadeIn::create(0.5);
		auto pActionFadeOut = FadeOut::create(0.5);
		auto pActionSineInOutWithFadeIn = EaseSineInOut::create(pActionFadeIn);
		auto pActionSineInOutWithFadeOut = EaseSineInOut::create(pActionFadeOut);
		auto pAction = RepeatForever::create(Sequence::create(pActionSineInOutWithFadeIn, pActionSineInOutWithFadeOut, nullptr));
		return pAction;
	}();
}