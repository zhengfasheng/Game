#include "GameLevelManager.h"
#include "UIManager.h"
#include "GameEvent.h"

GameLevel::GameLevel(float fTime, EnemyType minType , EnemyType maxType, int nCount, float fInterval)
	:m_fNeedTime(fTime),
	m_minType(minType),
	m_maxType(maxType), 
	m_nMaxCount(nCount), 
	m_fInterval(fInterval)
{

}

const int GameLevel::getMaxCount() const
{
	return m_nMaxCount;
}

const float GameLevel::getNeedTime() const
{
	return m_fNeedTime;
}

const EnemyType GameLevel::getMaxType() const
{
	return m_maxType;
}

const float GameLevel::getInterval() const
{
	return m_fInterval;
}

const EnemyType GameLevel::getMinType() const
{
	return m_minType;
}



GameLevelManager::GameLevelManager( )
{
	
}

GameLevelManager::~GameLevelManager()
{

}

//GameLevel::GameLevel(float fTime, EnemyType maxType, int nCount, float fInterval)
bool GameLevelManager::init()
{
	m_gameLevelVec.push_back(GameLevel(g_fGameLvUpTime, EnemyType::E0, EnemyType::E0, 3, 1.8f));
	m_gameLevelVec.push_back(GameLevel(g_fGameLvUpTime*2, EnemyType::E0, EnemyType::E1, 2, 1.5f));
	m_gameLevelVec.push_back(GameLevel(g_fGameLvUpTime*3, EnemyType::E0, EnemyType::E2, 3, 1.3f));
	m_gameLevelVec.push_back(GameLevel(g_fGameLvUpTime*4, EnemyType::E1, EnemyType::E3, 2, .9f));
	m_gameLevelVec.push_back(GameLevel(g_fGameLvUpTime*5, EnemyType::E1, EnemyType::E4, 2, .7f));
	m_gameLevelVec.push_back(GameLevel(g_fGameLvUpTime*6, EnemyType::E5, EnemyType::E5, 1, .5f));//把这个当作是boss

	return true;
}

GameLevel GameLevelManager::getGameLevel() const
{
	//得到当前的游戏时间
	auto param = UIManager::getInstance()->GetValue(ControllerID::Game, GameEvent::GET_GAME_TIME);
	auto fGameTime = 0.f;
	if ( !param.isNull() )
	{
		fGameTime = param.asFloat();
	}
	fGameTime = floor(fGameTime);
	//得到周期时间
	auto fTime = (size_t)fGameTime % (size_t)m_gameLevelVec.size() * g_fGameLvUpTime;

	auto nLevel = (size_t)fTime / (size_t)g_fGameLvUpTime;

	log("nLeve = %d", nLevel);

	if ( nLevel > m_gameLevelVec.size() )
	{
		return m_gameLevelVec[0];
	}
	return m_gameLevelVec[nLevel];
}



