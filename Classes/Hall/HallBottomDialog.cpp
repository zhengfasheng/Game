#include "HallBottomDialog.h"
#include "HallBottomView.h"

HallBottomDialog::HallBottomDialog()
{

}

HallBottomDialog::~HallBottomDialog()
{

}

UIView* HallBottomDialog::createView(DialogDelegate* pDelegate)
{
	return HallBottomView::create(pDelegate);
}

IMPLEMENT_HANDLER(HallBottomDialog,onUserInfoChange)
{
	auto pView = (HallBottomView*)getView();
	if ( pView )
	{
		pView->setAccount(p1.asString());
		pView->setUserName(p2.asString());
		pView->setChips(p3.asInt());
	}
}

IMPLEMENT_HANDLER(HallBottomDialog,onUserChipsChange)
{
	auto pView = (HallBottomView*)getView();
	if (pView && p1.asBool() )
	{
		pView->setChips(p2.asInt());
	}
}

