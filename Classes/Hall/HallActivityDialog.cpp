#include "HallActivityDialog.h"
#include "HallActivityView.h"

HallActivityDialog::HallActivityDialog()
{

}

HallActivityDialog::~HallActivityDialog()
{

}

UIView* HallActivityDialog::createView(DialogDelegate* pDelegate)
{
	return HallActivityView::create(pDelegate);
}

