#include "HallActivityDialog.h"
#include "HallActivityView.h"

HallActivityDialog::HallActivityDialog()
{

}

HallActivityDialog::~HallActivityDialog()
{

}

UIView* HallActivityDialog::createView(UIViewControllerDelegate* pDelegate)
{
	return HallActivityView::create(pDelegate);
}

