#pragma once
#include <vector>

enum class LevelUpType
{
	ShootSpeed,//�����ӵ��ٶ�����
	Power,//�ӵ�����
};

class AirplaneLevel
{
	LevelUpType m_type; //��������
	float m_fShootSpeed;//�����ٶ�
	int m_nPower;//�ӵ�����
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

	//�ɻ�����
	void leveUp();

	//�ɻ�����(���ɻ������ٺ󣬽���ԭ����1/2�ȼ�)
	void levelDown();

	//�ָ�Ĭ��
	void recoverToDefault();

	//�õ���ǰ�ɻ��ȼ� 
	const int getLevel() const;

	//���õ�ǰҪ����ķɻ������������ߣ�
	void setAirplane(Airplane* pAirplane);

	const AirplaneLevel& getAirplaneLevelInfo( int nLevel );

private:

	void initAirplaneLevel();

private:

	std::vector<AirplaneLevel> m_airplaneLevelVec;

	//��ǰ�ɻ��ĵȼ���������¿�ʼ�ǵûָ��ȼ�
	int m_nAirplaneLevel;

	//��������
	Airplane* m_pAirplane;

	friend class GameController;
};