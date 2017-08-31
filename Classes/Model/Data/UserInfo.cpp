#include "UserInfo.h"

UserInfo::UserInfo()
	:m_nScore(0)
	, m_nBestScore(0)
	, m_nCurrentDestroyEnemy(0)
	, m_nCurrentRebornTimes(0)
{

}


UserInfo::~UserInfo()
{

}

bool UserInfo::decode(const std::string& strMsg)
{
	//这里只是模拟下
	m_szName = "zheng fa sheng";
	m_sex = Sex::Male;
	m_nChips = 1000;
	return true;
}

bool UserInfo::encode(const std::string& strMsg)
{
	return true;
}

void UserInfo::reset()
{
	m_nScore = 0;
	m_nCurrentRebornTimes = 3;
	m_nCurrentDestroyEnemy = 0;
}
