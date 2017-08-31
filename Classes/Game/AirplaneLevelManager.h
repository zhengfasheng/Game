#pragma once
#include <vector>

enum class LevelUpType
{
	ShootSpeed,//发射子弹速度增加
	Power,//子弹威力
};

class AirplaneLevel
{
	LevelUpType m_type; //升级类型
	float m_fShootSpeed;//发射速度
	int m_nPower;//子弹威力
public:
	AirplaneLevel(LevelUpType type, float fShootSpeed, int nPower)
		:m_type(type), m_fShootSpeed(fShootSpeed), m_nPower(nPower){}

	const LevelUpType getType() const
	{
		return m_type;
	}

	const float getShootSpeed() const
	{
		return m_fShootSpeed;
	}

	const int getPower() const
	{
		return m_nPower;
	}

};

class Airplane;

class AirplaneLevelManager
{
private:
	AirplaneLevelManager();
public:
	~AirplaneLevelManager();

	virtual bool init( );

	//飞机升级
	void leveUp();

	//飞机降级(当飞机被击毁后，降至原来的1/2等级)
	void levelDown();

	//恢复默认
	void recoverToDefault();

	//得到当前飞机等级 
	const int getLevel() const;

	//设置当前要管理的飞机（即被管理者）
	void setAirplane(Airplane* pAirplane);

	const AirplaneLevel& getAirplaneLevelInfo( int nLevel );

private:

	void initAirplaneLevel();

private:

	std::vector<AirplaneLevel> m_airplaneLevelVec;

	//当前飞机的等级，如果重新开始记得恢复等级
	int m_nAirplaneLevel;

	//被管理者
	Airplane* m_pAirplane;

	friend class GameController;
};