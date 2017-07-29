#include "HallUserInfoState.h"
#include "HallUserInfoView.h"
#include "CurrentInfo.h"

HallUserInfoState::HallUserInfoState()
{

}

HallUserInfoState::~HallUserInfoState()
{

}

UIView* HallUserInfoState::createView(UIViewDelegate* pDelegate)
{
	return HallUserInfoView::create(pDelegate);
}

IMPLEMENT_HANDLER(HallUserInfoState,onUserChipsChange)
{
	auto pView = (HallUserInfoView*)getView();
	if ( pView && p1.asBool() )
	{
		pView->setChips(p2.asInt());
	}
}

void HallUserInfoState::WillShow()
{
	onUserChipsChange(true, CurrentInfo::getInstance()->getChips(), 0, 0);
	auto pView = (HallUserInfoView*)getView();
	if (pView)
	{
		pView->setAccount(CurrentInfo::getInstance()->getAccount());
		pView->setUserName(CurrentInfo::getInstance()->getName());
	}
	State::WillShow();
}

