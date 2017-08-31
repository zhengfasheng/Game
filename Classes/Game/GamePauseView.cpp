#include "GamePauseView.h"
#include "Common.h"
#include "ui/CocosGUI.h"
#include "GameEvent.h"
#include "UIManager.h"
using namespace ui;

bool GamePauseView::init(UIViewControllerDelegate* pUIViewControllerDelegate)
{
	do 
	{
		CC_BREAK_IF(!GameView::init(pUIViewControllerDelegate));

		auto pBackground = LayerColor::create(Color4B(0, 0, 0, 100));
		CC_BREAK_IF(!pBackground);
		this->addChild(pBackground);

		//创建一个事件监听
		auto pListener = EventListenerTouchOneByOne::create();
		CC_BREAK_IF(!pListener);
		pListener->onTouchBegan = CC_CALLBACK_2(GamePauseView::onTouchBegan, this);
		pListener->onTouchMoved = CC_CALLBACK_2(GamePauseView::onTouchMoved, this);
		//设置为接受触摸事件
		pListener->setEnabled(true);
		//设置为吞噬事件，不在向下发送
		pListener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
		
		auto winSize = Director::getInstance()->getWinSize();

		auto pPlay = Button::create();
		CC_BREAK_IF(!pPlay);
		pPlay->loadTextureNormal(s_play, Widget::TextureResType::PLIST);
		pPlay->loadTexturePressed(s_play, Widget::TextureResType::PLIST);
		pPlay->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		pPlay->setPressedActionEnabled(true);
		pPlay->setPosition(winSize / 2);
		pPlay->addClickEventListener(CC_CALLBACK_1(GamePauseView::onResumeGame, this));
		addChild(pPlay);
		return true;
	} while (0);
	return false;
}

void GamePauseView::onResumeGame(Ref* pSender)
{
	_eventDispatcher->removeEventListenersForTarget(this);
	UIManager::getInstance()->SendEvent(ControllerID::Game, GameEvent::NOTITY_GAME_RESUME);
	this->removeFromParent();
}

bool GamePauseView::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void GamePauseView::onTouchMoved(Touch *touch, Event *unused_event)
{

}

