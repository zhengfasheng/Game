#include "HallMainView.h"
#include "cocostudio\ActionTimeline\CSLoader.h"

HallMainView::HallMainView()
{

}

HallMainView::~HallMainView()
{

}

bool HallMainView::init(UIViewControllerDelegate* pDelegate)
{
	bool bRet = false;
	do
	{
		using namespace cocos2d::ui;
		CC_BREAK_IF(!UIView::init(pDelegate));
		auto rootNode = CSLoader::createNode("HallMainView.csb");
		CC_BREAK_IF(!rootNode);
		addChild(rootNode);

		bRet = true;
	} while (0);
	return bRet;
}


