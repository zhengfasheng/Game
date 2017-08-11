#include "SoundHelper.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"


/** @brief	存储玩家音效开关的key. */
static const char* g_szAudioStatusKey = "g_szAudioStatusKey";
static const char* g_szAudioVolumeKey = "g_szAudioVolumeKey";
/** @brief	存储玩家背景音乐开关key. */
static const char* g_szBackgroundMusicStatusKey = "g_szBackgroundMusicStatusKey";
static const char* g_szBackgroundMusicVolumeKey = "g_szBackgroundMusicVolumeKey";

USING_NS_CC;
using namespace CocosDenshion;
SoundHelper::SoundHelper()
	: m_bIsAudioOn(true)
	, m_bIsBackgroundOn(true)
	, m_fAudioVolume(1.0f)
	, m_fBackgroundVolume(1.0f)
	, m_backgroundType(BackgroundMusicType::Welcome)
{

}

SoundHelper::~SoundHelper()
{

}

void SoundHelper::init()
{
	read();
}

void SoundHelper::preloadBackgroundMusic()
{

}

void SoundHelper::playBackgroundMusic(BackgroundMusicType type, bool bIsLoop /*= true*/)
{
	auto szBackgroundPath = getBackgroundPath(type);
	if ( m_bIsBackgroundOn && szBackgroundPath)
	{
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(m_fBackgroundVolume);
		SimpleAudioEngine::getInstance()->playBackgroundMusic(szBackgroundPath, bIsLoop);
	}
}

void SoundHelper::stopBackgroundMusic()
{
	if ( m_bIsBackgroundOn )
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
}

void SoundHelper::pauseBackgroundMusic()
{
	if ( m_bIsBackgroundOn )
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
}

void SoundHelper::resumeBackgroundMusic()
{
	if ( m_bIsBackgroundOn)
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

bool SoundHelper::isBackgroundMusicOn()
{
	return m_bIsBackgroundOn;
}

void SoundHelper::setBackgroundMusic(bool bIsOn)
{
	if ( m_bIsBackgroundOn = bIsOn)
	{
		return;
	}
	m_bIsBackgroundOn = bIsOn;
	if ( bIsOn )
	{
		playBackgroundMusic(m_backgroundType);
	}
	else
	{
		stopBackgroundMusic();
	}
	save();
}

float SoundHelper::getBackgroundMusicVolume()
{
	return m_fBackgroundVolume;
}

void SoundHelper::setBackgroundMusicVolume(float fVolume)
{
	m_fBackgroundVolume = fVolume;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(fVolume);
}

void SoundHelper::preloadAudio()
{

}

unsigned int SoundHelper::playAudio(AudioType type, bool bIsLoop /*= false*/)
{
	auto szAudioPath = getAudioPath(type);
	if ( m_bIsAudioOn && szAudioPath)
	{
		return SimpleAudioEngine::getInstance()->playEffect(szAudioPath, bIsLoop);
	}
	return 0;
}

void SoundHelper::stopAudio(unsigned int nAudioID)
{
	if ( m_bIsAudioOn )
	{
		SimpleAudioEngine::getInstance()->stopEffect(nAudioID);
	}
}

void SoundHelper::stopAllAudio()
{
	if ( m_bIsAudioOn )
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
}

void SoundHelper::pauseAudio(unsigned int nAudioID)
{
	if ( m_bIsAudioOn )
	{
		SimpleAudioEngine::getInstance()->pauseEffect(nAudioID);
	}
}

void SoundHelper::pauseAllAudio()
{
	if ( m_bIsAudioOn )
	{
		SimpleAudioEngine::getInstance()->pauseAllEffects();
	}
}

void SoundHelper::resumeAudio(unsigned int nAudioID)
{
	if ( m_bIsAudioOn )
	{
		SimpleAudioEngine::getInstance()->resumeEffect(nAudioID);
	}
}

void SoundHelper::resumeAllAudio()
{
	if ( m_bIsAudioOn )
	{
		SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
}

bool SoundHelper::isAudioOn()
{
	return m_bIsAudioOn;
}

void SoundHelper::setAudio(bool bIsOn)
{
	if (m_bIsAudioOn == bIsOn)
	{
		return;
	}
	m_bIsAudioOn = bIsOn;
	if ( bIsOn )
	{
		resumeAllAudio();
	}
	else
	{
		stopAllAudio();
	}
	save();
}

float SoundHelper::getAudioVolume()
{
	return m_fAudioVolume;
}

void SoundHelper::setAudioVolume(float fVolume)
{
	m_fAudioVolume = fVolume;
	SimpleAudioEngine::getInstance()->setEffectsVolume(fVolume);
}

void SoundHelper::save()
{
	auto pUser = UserDefault::getInstance();
	CCLOG("%s", pUser->getXMLFilePath());
	pUser->setBoolForKey(g_szAudioStatusKey, m_bIsAudioOn);
	pUser->setBoolForKey(g_szBackgroundMusicStatusKey, m_bIsBackgroundOn);
	pUser->setFloatForKey(g_szAudioVolumeKey, m_fAudioVolume);
	pUser->setFloatForKey(g_szBackgroundMusicVolumeKey, m_fBackgroundVolume);
}

void SoundHelper::read()
{
	auto pUser = UserDefault::getInstance();
	CCLOG("%s", pUser->getXMLFilePath());
	m_bIsAudioOn = pUser->getBoolForKey(g_szAudioStatusKey, true);
	m_bIsBackgroundOn = pUser->getBoolForKey(g_szBackgroundMusicStatusKey, true);
	m_fAudioVolume = pUser->getFloatForKey(g_szAudioVolumeKey, 0.7f);
	m_fBackgroundVolume = pUser->getFloatForKey(g_szBackgroundMusicVolumeKey, 1.0f);
}

const char* SoundHelper::getBackgroundPath(BackgroundMusicType type)
{
	return"";
}

const char* SoundHelper::getAudioPath(AudioType type)
{
	return "";
}


