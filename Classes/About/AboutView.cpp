#include "AboutView.h"
#include "ui/CocosGUI.h"
#include "Language.h"

AboutView::AboutView()
{

}

AboutView::~AboutView()
{

}

bool AboutView::init(UIViewControllerDelegate* pDelegate)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!UIView::init(pDelegate));
		auto winSize = Director::getInstance()->getWinSize();
			//��ӱ���
		auto pBackground = Sprite::createWithTexture(getTextureForKey(s_loading));
		CC_BREAK_IF(!pBackground);
		pBackground->setAnchorPoint(Vec2::ZERO);
		addChild(pBackground);

		//���ӱ���
		auto pTitle = Sprite::createWithTexture(getTextureForKey(s_menuTitle), g_aboutRect);
		CC_BREAK_IF(!pTitle);
		pTitle->setPosition(Vec2(winSize.width / 2, winSize.height - 60));
		addChild(pTitle);

		//��ӷ��ذ�ť
		auto pGoBackLabel = ui::TextBMFont::create(Language::getInstance()->getString("about.go_back"), Language::getInstance()->getBitmapFont());
		CC_BREAK_IF(!pGoBackLabel);
		auto pMenuItem = MenuItemLabel::create(pGoBackLabel, CC_CALLBACK_1(AboutView::onGoBack, this));
		CC_BREAK_IF(!pMenuItem);

		//���Menu�ڲ����ô�С������£�ContentSize����winsize
		auto pMenu = Menu::create(pMenuItem, nullptr);
		CC_BREAK_IF(!pMenu);
		pMenu->setPosition(winSize.width / 2, 50);
		addChild(pMenu);
		//���ð�ť����Ч��
		auto pActionFadeIn = FadeIn::create(0.5);
		auto pActionFadeOut = FadeOut::create(0.5);
		auto pActionSineInOutWithFadeIn = EaseSineInOut::create(pActionFadeIn);
		auto pActionSineInOutWithFadeOut = EaseSineInOut::create(pActionFadeOut);
		pMenuItem->runAction(RepeatForever::create(Sequence::create(pActionSineInOutWithFadeIn, pActionSineInOutWithFadeOut, nullptr)));

		//���˵������
		auto pAbout = ui::Text::create(Language::getInstance()->getString("about.about_chinese"), Language::getInstance()->getLocalFont(), 24);
		CC_BREAK_IF(!pAbout);
		pAbout->ignoreContentAdaptWithSize(false);
		pAbout->ignoreAnchorPointForPosition(true);
		pAbout->setTextAreaSize(Size(winSize.width, winSize.height - pMenuItem->getContentSize().height - pTitle->getContentSize().height));
		pAbout->setPosition(Vec2::ZERO);

		addChild(pAbout);
		return true;
		bRet = true;
	} while (0);
	return bRet;
}

void AboutView::onGoBack(Ref* pSender)
{
	if ( getDelegate() )
	{
		getDelegate()->SendEvent(UIEvent::EVENT_ABOUT_GO_BACK);
	}
}

