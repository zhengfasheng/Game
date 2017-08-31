#pragma once
#include "GameConfig.h"

//游戏等级
class GameLevel
{
	float m_fNeedTime;//游戏时间（即间隔多长时间后出现）
	EnemyType m_minType;//出现飞机的最小类型
	EnemyType m_maxType;//出现飞机的最大类型
	int   m_nMaxCount;//同一时间最大创建敌机个数
	float m_fInterval;//产生敌机间隔时间
public:
	GameLevel(float fTime, EnemyType minType, EnemyType maxType, int nCount, float fInterval);

	//得到产生敌机最大个数
	const int getMaxCount() const ;

	//得到需要的游戏时长
	const float getNeedTime() const;

	//得到产生敌机的最小类型
	const EnemyType getMinType() const;

	//得到产生敌机的最大类型
	const EnemyType getMaxType() const;

	//得到产生敌机的间隔时间
	const float getInterval() const;

};

class GameController;
class GameLevelManager
{
private:

	GameLevelManager( );
	~GameLevelManager();

	GameLevel getGameLevel() const;

protected:

	virtual bool init();

private:

	std::vector<GameLevel> m_gameLevelVec;

	friend class GameController;
};