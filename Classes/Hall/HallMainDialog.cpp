#include "HallMainDialog.h"
#include "HallMainView.h"

HallMainDialog::HallMainDialog()
{

}

HallMainDialog::~HallMainDialog()
{

}

UIView* HallMainDialog::createView(DialogDelegate* pDelegate)
{
	return HallMainView::create(pDelegate);
}

void HallMainDialog::WillShow()
{
	Dialog::WillShow();
}

