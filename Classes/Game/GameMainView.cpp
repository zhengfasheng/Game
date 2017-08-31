#include "GameMainView.h"
#include "GameMapView.h"
#include "GameConfig.h"
#include "GameInfoView.h"
#include "GamePauseView.h"
#include "SoundHelper.h"
#include "GameOpView.h"
#include "Bullet.h"

GameMainView::GameMainView()
	:m_pMapView(nullptr)
	, m_pGameInfoView(nullptr)
	, m_pGameOpView(nullptr)
{

}

GameMainView::~GameMainView()
{
	m_pMapView = nullptr;
	m_pGameInfoView = nullptr;
	m_pGameOpView = nullptr;
}

bool GameMainView::init(UIViewControllerDelegate* pDelegate)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!UIView::init(pDelegate));

		setEnableShowAction(false);
		setEnableHideAction(false);

		m_pMapView = GameMapView::create(pDelegate);
		CC_BREAK_IF(!m_pMapView);
		this->addChild(m_pMapView, (int)ZOder::Map);
		m_pMapView->Show();

		m_pGameInfoView = GameInfoView::create(pDelegate);
		CC_BREAK_IF(!m_pGameInfoView);
		this->addChild(m_pGameInfoView, (int)ZOder::Info);
		m_pGameInfoView->Show();

		m_pGameOpView = GameOpView::create(pDelegate);
		CC_BREAK_IF(!m_pGameOpView);
		this->addChild(m_pGameOpView, (int)ZOder::Op);
		m_pGameOpView->Show();

		bRet = true;
	} while (0);
	return bRet;
}

GameInfoView* GameMainView::getGameInfoView()
{
	return m_pGameInfoView;
}

GameOpView* GameMainView::getGameOpView()
{
	return m_pGameOpView;
}

void GameMainView::showGamePauseView()
{
	auto pPauseView = GamePauseView::create(getDelegate());
	if (pPauseView)
	{
		addChild(pPauseView, (int)ZOder::Pause);
		pPauseView->Show();
	}
}

void GameMainView::Show()
{
	UIView::Show();
}
