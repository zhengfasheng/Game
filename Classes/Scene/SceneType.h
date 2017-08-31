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
 *  Date:2017/8/19 0:35
 *
 *  Summary:场景类型
 *  
 ******************************************************************************/
#pragma once

enum class SceneType
{
	Invalid = -1,//无效
	Resource,//资源加载场景（这是一个过渡的场景，用于两个场景之间切换，资源的释放与加载）
	Start,//开始场景
	Game,//游戏场景
	About,//关于场景
	Setting,//设置场景
	GameOver,//游戏结束 
};