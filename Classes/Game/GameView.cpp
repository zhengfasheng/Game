#include "GameView.h"

GameView::GameView()
{

}

GameView::~GameView()
{

}

bool GameView::init(UIViewControllerDelegate* pUIViewControllerDelegate )
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!UIView::init(pUIViewControllerDelegate));
		setEnableDelegate(false);
		setEnableHideAction(false);
		setEnableShowAction(false);
		bRet = true;
	} while (0);
	return bRet;
}



