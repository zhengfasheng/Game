#include "HallMainDialog.h"
#include "HallMainView.h"

HallMainDialog::HallMainDialog()
{

}

HallMainDialog::~HallMainDialog()
{

}

UIView* HallMainDialog::createView(UIViewControllerDelegate* pDelegate)
{
	return HallMainView::create(pDelegate);
}

void HallMainDialog::WillShow()
{
	UIViewController::WillShow();
}

