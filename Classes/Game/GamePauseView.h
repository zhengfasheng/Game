#pragma once
#include "GameView.h"

class GamePauseView : public GameView
{
public:

	virtual bool init(UIViewControllerDelegate* pUIViewControllerDelegate) override;

	IMPLEMENT_CREATE_VIEW(GamePauseView);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
	virtual void onTouchMoved(Touch *touch, Event *unused_event) override;

private:

	void onResumeGame(Ref* pSender);
};