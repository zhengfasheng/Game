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
 *  Date:2017/8/23 21:28
 *
 *  Summary:…Ë÷√øÿ÷∆∆˜
 *  
 ******************************************************************************/
#pragma once
#include "UIViewController.h"

USING_UI;
class SettingController : public UIViewController
{
public:
	SettingController();
	virtual ~SettingController();

	virtual UIView* createView(UIViewControllerDelegate* pDelegate) override;

	DECLARE_HANDLER(onGoBack);
	DECLARE_HANDLER(onBackgroundMusicChange);
	DECLARE_HANDLER(onAudioChange);

	EVENT_HANDLER_BEGIN
		EVENT_HANDLER(UIEvent::EVENT_SETTING_GO_GACK, onGoBack);
		EVENT_HANDLER(UIEvent::EVENT_SETTING_CHANGE_BACKGROUND_MUSIC_STATUS, onBackgroundMusicChange);
		EVENT_HANDLER(UIEvent::EVENT_SETTING_CHANGE_AUDIO_STATUS, onAudioChange);
	EVENT_HANDLER_END
};