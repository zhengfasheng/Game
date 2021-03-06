#pragma once
#include <string>
// image 
static const std::string s_bg01 = "bg01.jpg";
static const std::string s_loading = "loading.png";//加载界面用
static const std::string s_ship01 = "ship01.png";
static const std::string s_menu = "menu.png";
static const std::string s_logo = "logo.png";
static const std::string s_cocos2dx = "cocos2d-html5.png";
static const std::string s_gameOver = "gameOver.png";
static const std::string s_menuTitle = "menuTitle.png";
static const std::string s_enemy = "Enemy.png";
static const std::string s_flare = "flare.jpg";
static const std::string s_bullet = "bullet.png";
static const std::string s_explosion = "explosion.png";
static const std::string s_explode1 = "explode1.jpg";
static const std::string s_explode2 = "explode2.jpg";
static const std::string s_explode3 = "explode3.jpg";
static const std::string s_hit = "hit.jpg";
static const std::string s_arial14 = "arial-14.png";
static const std::string s_pause = "pause.png";
static const std::string s_play = "play.png";
static const std::string s_loadingbar = "slider_bar_active_9patch.png";//加载界面用，

static const int g_nTotalResource = 18;//那个进度条没有算进去一进去就直接用了

// font
static const char* s_font = "fonts/bitmapFontTest.fnt";
static const char* s_arial14_fnt = "fonts/arial-14.fnt";//字体

// music
static const char* s_bgMusic = "bgMusic.mp3";
static const char* s_mainMainMusic = "mainMainMusic.mp3";

// sound effect
static const char* s_buttonEffect = "buttonEffet.mp3";
static const char* s_explodeEffect = "explodeEffect.mp3";
static const char* s_fireEffect = "fireEffect.mp3";
static const char* s_shipDestroyEffect = "shipDestroyEffect.mp3";

//tmx
static const char* s_level01 = "level01.tmx";

//plist
static const char* s_Enemy_plist = "Enemy.plist";
static const char* s_explosion_plist = "explosion.plist";
static const char* s_bullet_plist = "bullet.plist";

//key
//子弹
//自己的子弹key
static const char* s_myBullet = "W1.png";
//敌机的子弹key
static const char* s_enemybullet = "W2.png";

//敌机类型的纹理名称key
static const std::vector<char*> g_enemyTextureNameVec = 
{
	"E0.png",
	"E1.png",
	"E2.png",
	"E3.png",
	"E4.png",
	"E5.png",
};
