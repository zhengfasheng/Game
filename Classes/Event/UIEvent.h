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
 *  Date:2017/7/29 17:19
 *
 *  Summary: 界面事件名定义
 *  
 ******************************************************************************/
#pragma once
#include <string>

namespace UIEvent
{
	//开始场景事件
	/** @brief	新游戏 */
	const std::string EVENT_START_NEW_GAME = "EVENT_START_NEW_GAME";
	/** @brief	打开关于 */
	const std::string EVENT_OPEN_ABOUT = "EVENT_OPEN_ABOUT";
	/** @brief	打开设置 */
	const std::string EVENT_OPENT_SETTING = "EVENT_OPENT_SETTING";
	
}