#include "HallBottomState.h"
#include "HallBottomView.h"

HallBottomState::HallBottomState()
{

}

HallBottomState::~HallBottomState()
{

}

UIView* HallBottomState::createView(UIViewDelegate* pDelegate)
{
	return HallBottomView::create(pDelegate);
}

IMPLEMENT_HANDLER(HallBottomState,onUserInfoChange)
{
	auto pView = (HallBottomView*)getView();
	if ( pView )
	{
		pView->setAccount(p1.asString());
		pView->setUserName(p2.asString());
		pView->setChips(p3.asInt());
	}
}

IMPLEMENT_HANDLER(HallBottomState,onUserChipsChange)
{
	auto pView = (HallBottomView*)getView();
	if (pView && p1.asBool() )
	{
		pView->setChips(p2.asInt());
	}
}

