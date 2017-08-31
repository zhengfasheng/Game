#include "AirplaneLevelManager.h"
#include "GameConfig.h"

AirplaneLevelManager::AirplaneLevelManager() 
	:m_nAirplaneLevel(0),
	m_pAirplane(nullptr)
{
	
}

AirplaneLevelManager::~AirplaneLevelManager()
{
	m_airplaneLevelVec.clear();
	m_pAirplane = nullptr;
}

bool AirplaneLevelManager::init()
{
	initAirplaneLevel();
	return true;
}

void AirplaneLevelManager::initAirplaneLevel()
{
	//这里不考虑时间为小于0的问题，配置的时间自己算吧
	
	float fSpeed = g_fAirplaneShootSpeed;
	int   nPower = g_nPower;
	LevelUpType type = LevelUpType::ShootSpeed;
	int nFlag = 0;
	for (int i = 0; i < g_nAirplaneMaxLevel; i++)
	{
		nFlag = i / 3;
		if ( nFlag % 2 == 0 )
		{
			type = LevelUpType::ShootSpeed;
			m_airplaneLevelVec.push_back(AirplaneLevel(type, fSpeed, nPower));
			fSpeed += g_fAirplaneLvUpAddSpeed;
		}
		else
		{
			type = LevelUpType::Power;
			m_airplaneLevelVec.push_back(AirplaneLevel(type, fSpeed, nPower));
			nPower += g_nAirplaneLvUpAddPower;
		}

	}

}

void AirplaneLevelManager::leveUp()
{
	if ( m_nAirplaneLevel + 1 >= g_nAirplaneMaxLevel )
	{
		//已经是最大，不再增加
		log("---- Airplane is max ----");
		return;
	}
	m_nAirplaneLevel++;
	log("----------airplane level up to %d", m_nAirplaneLevel);
}

void AirplaneLevelManager::levelDown()
{
	if ( m_nAirplaneLevel - 1 < 0 )
	{
		return;
	}
	m_nAirplaneLevel--;
	log("----------airplane level down to %d", m_nAirplaneLevel);
}

void AirplaneLevelManager::recoverToDefault()
{
	m_nAirplaneLevel = 0;
}

const int AirplaneLevelManager::getLevel() const
{
	return m_nAirplaneLevel;
}

const AirplaneLevel& AirplaneLevelManager::getAirplaneLevelInfo(int nLevel)
{
	if ( nLevel < 0 || nLevel >= g_nAirplaneMaxLevel )
	{
		return m_airplaneLevelVec[0];
	}
	return m_airplaneLevelVec[nLevel];
}





