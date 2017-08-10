#include "HallUserInfoDialog.h"
#include "HallUserInfoView.h"
#include "CurrentInfo.h"

HallUserInfoDialog::HallUserInfoDialog()
{

}

HallUserInfoDialog::~HallUserInfoDialog()
{

}

UIView* HallUserInfoDialog::createView(DialogDelegate* pDelegate)
{
	return HallUserInfoView::create(pDelegate);
}

IMPLEMENT_HANDLER(HallUserInfoDialog,onUserChipsChange)
{
	auto pView = (HallUserInfoView*)getView();
	if ( pView && p1.asBool() )
	{
		pView->setChips(p2.asInt());
	}
}

void HallUserInfoDialog::WillShow()
{
	onUserChipsChange(true, CurrentInfo::getInstance()->getUserInfo().getChips(), 0, 0);
	auto pView = (HallUserInfoView*)getView();
	if (pView)
	{
		pView->setAccount(CurrentInfo::getInstance()->getUserInfo().getAccount());
		pView->setUserName(CurrentInfo::getInstance()->getUserInfo().getName());
	}
	Dialog::WillShow();
}

