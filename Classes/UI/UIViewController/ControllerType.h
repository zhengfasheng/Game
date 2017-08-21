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
 *  Date:2017/7/28 22:09
 *
 *  Summary: 控制器id
 *  
 ******************************************************************************/
#pragma once

enum class ControllerID
{
	Min,
	Invalid = Min,
	Start,//开始
	About,//关于
	Max
};

//State 中view 在场景中显示的层级
enum SceneZOder
{
	Normal = 10000,//其它所有非通知形
	Notice = 20000 //如tips , MessageBox loading animation
};