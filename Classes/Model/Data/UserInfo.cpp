#include "UserInfo.h"

UserInfo::UserInfo()
{

}


UserInfo::~UserInfo()
{

}

bool UserInfo::decode(const std::string& strMsg)
{
	//����ֻ��ģ����
	m_szName = "zheng fa sheng";
	m_sex = Sex::Male;
	m_nChips = 1000;
	return true;
}

bool UserInfo::encode(const std::string& strMsg)
{
	return true;
}
