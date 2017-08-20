/******************************************************************************
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
 *  Email:zheng_fasheng@outlook.com
 *
 *  Date:2016/7/29 22:28
 *
 *  Summary:游戏数据库接口定义，把要加载的表id，跟相关配置信息写在此
 *  
 ******************************************************************************/
#pragma once
#include "DataBaseDefine.h"

DBC_BEGIN

enum TableID
{
	TextConfig,//文字配置表
	ImageConfig,//图片配置表
	AnimateConfig,//序列帧动画配置表
	ArmatureConfig,//骨骼动画配置表,需要提前加载资源
};

static TableConfig g_tableConfig[] = {
	{ TableID::TextConfig, "TextConfig.txt", "config" },
	{ TableID::ImageConfig, "ImageConfig.txt", "config" },
	{ TableID::AnimateConfig, "AnimateConfig.txt","config" },
	TableConfig(TableID::ArmatureConfig, "ArmatureConfig.txt","config" ),
};

DBC_END