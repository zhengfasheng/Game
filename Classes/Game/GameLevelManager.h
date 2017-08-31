#pragma once
#include "GameConfig.h"

//��Ϸ�ȼ�
class GameLevel
{
	float m_fNeedTime;//��Ϸʱ�䣨������೤ʱ�����֣�
	EnemyType m_minType;//���ַɻ�����С����
	EnemyType m_maxType;//���ַɻ����������
	int   m_nMaxCount;//ͬһʱ����󴴽��л�����
	float m_fInterval;//�����л����ʱ��
public:
	GameLevel(float fTime, EnemyType minType, EnemyType maxType, int nCount, float fInterval);

	//�õ������л�������
	const int getMaxCount() const ;

	//�õ���Ҫ����Ϸʱ��
	const float getNeedTime() const;

	//�õ������л�����С����
	const EnemyType getMinType() const;

	//�õ������л����������
	const EnemyType getMaxType() const;

	//�õ������л��ļ��ʱ��
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