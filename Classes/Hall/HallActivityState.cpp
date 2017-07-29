#include "HallActivityState.h"
#include "HallActivityView.h"

HallActivityState::HallActivityState()
{

}

HallActivityState::~HallActivityState()
{

}

UIView* HallActivityState::createView(UIViewDelegate* pDelegate)
{
	return HallActivityView::create(pDelegate);
}

