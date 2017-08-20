#include "GameConfig.h"

GameConfig::GameConfig()
	:m_screenSize(320,480)
	, m_bIsShowFPS(false)
{
	readConfig();
}

GameConfig::~GameConfig()
{
	
}

float GameConfig::getScreenWidth()
{
	return m_screenSize.width;
}

float GameConfig::getScreenHeight()
{
	return m_screenSize.height;
}

bool GameConfig::isShowFPS()
{
	return m_bIsShowFPS;
}

void GameConfig::readConfig()
{
	auto pDict = __Dictionary::createWithContentsOfFile("config.plist");
	if ( pDict )
	{
		auto pWidth = (__String*)pDict->objectForKey("width");
		auto pHeight = (__String*)pDict->objectForKey("height");
		auto pIsShowFPS = (__String*)pDict->objectForKey("is_show_fps");
		if ( pWidth )
		{
			m_screenSize.width = pWidth->floatValue();
		}
		if ( pHeight )
		{
			m_screenSize.height = pHeight->floatValue();
		}
		if ( pIsShowFPS )
		{
			m_bIsShowFPS = pIsShowFPS->boolValue();
		}
	}
}

