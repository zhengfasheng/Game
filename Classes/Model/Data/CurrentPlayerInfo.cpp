#include "CurrentPlayerInfo.h"
#include "GameConfig.h"
#include "UIManager.h"
#include "UIEvent.h"
#include "GameEvent.h"

CurrentPlayerInfo::CurrentPlayerInfo()
	:m_userInfo()
{

}

CurrentPlayerInfo::~CurrentPlayerInfo()
{

}

void CurrentPlayerInfo::savePlayerInformation()
{
	auto pUser = UserDefault::getInstance();
	if (pUser)
	{
		int nScore = pUser->getIntegerForKey(g_szBestScoreKey, 0);
		if (m_userInfo.getScore() > nScore)
		{
			m_userInfo.setBestScore(m_userInfo.getScore());
			pUser->setIntegerForKey(g_szBestScoreKey, m_userInfo.getBestScore());
		}
	}
}

void CurrentPlayerInfo::readPlayerInformation()
{
	auto pUser = UserDefault::getInstance();
	log("%s", pUser->getXMLFilePath().data());
	if (pUser)
	{
		m_userInfo.setBestScore( pUser->getIntegerForKey(g_szBestScoreKey, 0));
		log("best score %d", m_userInfo.getBestScore());
	}
}

void CurrentPlayerInfo::addScore(int nScore)
{
	m_userInfo.setScore(m_userInfo.getScore() + nScore);

	m_userInfo.setCurrentDestroyEnemy(m_userInfo.getCurrentDestroyEnemy() + 1);
	if (m_userInfo.getCurrentDestroyEnemy() == g_nKillEnemyLvUp)
	{
		//通知飞机升级
		UIManager::getInstance()->SendEvent(ControllerID::Game, GameEvent::NOTIFY_AIRPLANE_LEVEL_UP);
		m_userInfo.setCurrentDestroyEnemy(0);
	}
}

void CurrentPlayerInfo::reset()
{
	m_userInfo.reset();
}

