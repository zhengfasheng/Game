#include "HallMainSate.h"
#include "HallMainView.h"

HallMainSate::HallMainSate()
{

}

HallMainSate::~HallMainSate()
{

}

UIView* HallMainSate::createView(UIViewDelegate* pDelegate)
{
	return HallMainView::create(pDelegate);
}

void HallMainSate::WillShow()
{
	State::WillShow();
}

