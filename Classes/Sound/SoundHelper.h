/******************************************************************************
 * Copyright (c) 2017 . All rights reserved.
 *
 *
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  Author:Zheng Fasheng
 *  
 *  Email:zheng_fasheng@qq.com
 *
 *  Date:2017/8/12 1:17
 *
 *  Summary:…˘“Ù∞Ô÷˙
 *  
 ******************************************************************************/
#pragma once

#include "common.h"

class SoundHelper
{
	SoundHelper();
public:
	IMPLEMENT_SINGLETON(SoundHelper);
	virtual ~SoundHelper();

	enum class BackgroundMusicType
	{
		Min = -1,
		BackMusic,//±≥æ∞“Ù¿÷
		GameBackMusic,//”Œœ∑±≥æ∞“Ù¿÷
		Max
	};

	enum class AudioType
	{
		Min = -1,
		Fire,//¥Ú◊”µØ…˘“Ù
		PlaneDestroy,//∑…ª˙±¨’®
		EnemyDestroy,//µ–ª˙±¨’®
		Button,//∞¥≈•…˘“Ù
		Max
	};

	virtual void init();

	virtual void preloadBackgroundMusic();
	virtual void playBackgroundMusic(BackgroundMusicType type, bool bIsLoop = true);
	virtual void stopBackgroundMusic();
	virtual bool isPlayingBackgroundMusic();
	virtual void pauseBackgroundMusic();
	virtual void resumeBackgroundMusic();
	virtual bool isBackgroundMusicOn();
	virtual void setBackgroundMusic(bool bIsOn);
	virtual float getBackgroundMusicVolume();
	virtual void setBackgroundMusicVolume( float fVolume);

	virtual void preloadAudio();
	virtual void playAudio(AudioType type, bool bIsLoop = false);
	virtual void stopAudio(unsigned int nAudioID);
	virtual void stopAllAudio();
	virtual void pauseAudio(unsigned int nAudioID);
	virtual void pauseAllAudio();
	virtual void resumeAudio(unsigned int nAudioID);
	virtual void resumeAllAudio();
	virtual bool isAudioOn();
	virtual void setAudio(bool bIsOn);
	virtual float getAudioVolume();
	virtual void setAudioVolume(float fVolume);

protected:

	virtual void save();
	virtual void read();

	const char* getBackgroundPath(BackgroundMusicType type);
	const char* getAudioPath(AudioType type);

protected:

	bool m_bIsAudioOn;
	bool m_bIsBackgroundOn;
	float m_fBackgroundVolume;
	float m_fAudioVolume;
	BackgroundMusicType m_backgroundType;

	unsigned int m_nCurrentAudioId;
};