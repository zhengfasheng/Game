#include "SettingView.h"
#include "Language.h"
#include "SoundHelper.h"
#include "ui/CocosGUI.h"
#include "UIEvent.h"

SettingView::SettingView()
{

}

SettingView::~SettingView()
{

}

bool SettingView::init(UIViewControllerDelegate* pDelegate)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!UIView::init(pDelegate));

		auto winSize = Director::getInstance()->getWinSize();
		//添加背景图片
		auto pBackgroud = Sprite::createWithTexture(getTextureForKey(s_loading));
		CC_BREAK_IF(!pBackgroud);
		pBackgroud->setAnchorPoint(Vec2::ZERO);
		addChild(pBackgroud);

		//增加标题
		auto pTitle = Sprite::createWithTexture(getTextureForKey(s_menuTitle), g_settingRect);
		CC_BREAK_IF(!pTitle);
		pTitle->setPosition(Vec2(winSize.width / 2, winSize.height - 60));
		addChild(pTitle);

		//添加背景声音开关
		auto pBackMusicMenuItem = MenuItemFont::create(Language::getInstance()->getString("setting.background_music"));
		CC_BREAK_IF(!pBackMusicMenuItem);
		pBackMusicMenuItem->setFontName("Arial");
		pBackMusicMenuItem->setFontSize(18);
		pBackMusicMenuItem->setEnabled(false);

		MenuItemFont::setFontName("Arial");
		MenuItemFont::setFontSize(26);

		auto pBackMusicToggle = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(SettingView::onSettingBackMusic, this),
			MenuItemFont::create(Language::getInstance()->getString("setting.sounds_on")),
			MenuItemFont::create(Language::getInstance()->getString("setting.sounds_off")), nullptr);
		CC_BREAK_IF(!pBackMusicToggle);
		auto nSelectedId = SoundHelper::getInstance()->isBackgroundMusicOn();

		pBackMusicToggle->setSelectedIndex(nSelectedId);

		//创建音效开关
		auto pAudioItem = MenuItemFont::create(Language::getInstance()->getString("setting.audio"));
		CC_BREAK_IF(!pAudioItem);
		pAudioItem->setFontName("Arial");
		pAudioItem->setFontSize(18);
		pAudioItem->setEnabled(false);

		MenuItemFont::setFontName("Arial");
		MenuItemFont::setFontSize(26);

		auto pAudioToggle = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(SettingView::onSettingAudio, this),
			MenuItemFont::create(Language::getInstance()->getString("setting.sounds_on")),
			MenuItemFont::create(Language::getInstance()->getString("setting.sounds_off")), nullptr);
		CC_BREAK_IF(!pAudioToggle);
		nSelectedId = SoundHelper::getInstance()->isAudioOn();

		pAudioToggle->setSelectedIndex(nSelectedId);


		//添加返回按钮
		auto pBackLabel = ui::TextBMFont::create(Language::getInstance()->getString("about.go_back"), Language::getInstance()->getBitmapFont());
		CC_BREAK_IF(!pBackLabel);
		auto pGoBackItem = MenuItemLabel::create(pBackLabel, CC_CALLBACK_1(SettingView::onGoBack, this));
		CC_BREAK_IF(!pGoBackItem);

		auto pMenu = Menu::create(pBackMusicMenuItem, pBackMusicToggle, pAudioItem, pAudioToggle, pGoBackItem, nullptr);
		CC_BREAK_IF(!pMenu);
		//表示的是第一行有2个按钮
		//第二行有2个按钮,第三行有1个按钮
		pMenu->alignItemsInColumns(2, 2, 1);
		addChild(pMenu);

		//创建一个按钮的动画效果
		auto pActionFadeIn = FadeIn::create(0.5);
		auto pActionFadeOut = FadeOut::create(0.5);
		auto pActionSineInOutWithFadeIn = EaseSineInOut::create(pActionFadeIn);
		auto pActionSineInOutWithFadeOut = EaseSineInOut::create(pActionFadeOut);

		auto pAction = Sequence::create(pActionSineInOutWithFadeIn, pActionSineInOutWithFadeOut, nullptr);

		CC_BREAK_IF(!pAction);
		pGoBackItem->runAction(RepeatForever::create(pAction));

		bRet = true;
	} while (0);
	return bRet;
}

void SettingView::onGoBack(Ref* pSender)
{
	if ( getDelegate() )
	{
		getDelegate()->SendEvent(UIEvent::EVENT_SETTING_GO_GACK);
	}
}

void SettingView::onSettingBackMusic(Ref* pSender)
{
	auto pMenu = (MenuItemToggle*)pSender;
	if (!pMenu) return;
	if (getDelegate())
	{
		auto bIsOpen = pMenu->getSelectedIndex() == 1;
		getDelegate()->SendEvent(UIEvent::EVENT_SETTING_CHANGE_BACKGROUND_MUSIC_STATUS,bIsOpen);
	}
}

void SettingView::onSettingAudio(Ref* pSender)
{
	auto pMenu = (MenuItemToggle*)pSender;
	if (!pMenu) return;
	if (getDelegate())
	{
		auto bIsOpen = pMenu->getSelectedIndex() == 1;
		getDelegate()->SendEvent(UIEvent::EVENT_SETTING_CHANGE_AUDIO_STATUS, bIsOpen);
	}
}

