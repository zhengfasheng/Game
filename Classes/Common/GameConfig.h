#pragma once
//游戏的基本配置
#include "cocos2d.h"
#include "Singleton.h"
USING_NS_CC;

//static cocos2d::Size designResolutionSize = cocos2d::Size(320, 480);
//static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
//static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

//相关key

//玩家最高分
const static char* g_szBestScoreKey = "bestScore";
//玩家的背景音乐
const static char* g_szBackMusicKey = "backMusic";
//玩家的音效
const static char* g_szAudioKey = "audio";

//游戏事件监听器名称
const static char* g_szEventListenerName = "Game Event Listener";

//增加分数事件名称
const static char* g_szEventAddScore = "Add Score";

//删除子弹事件名称
const static char* g_szEventDeleteMyBullet = "Delete My Bullet";

//删除敌机
const static char* g_szEventDeleteEnemy = "Delete Enemy";

//玩家飞机没血通知
const static char* g_szEventPlayerPlaneDestroy = "Player Plane Destroy";

//玩家飞机重生通知
const static char* g_szEventPlayerPlaneReborn = "Player Plane Reborn";

//飞机升级
const static char* g_szEventLvUp = "Lv Up";

//爆炸特效动画名
const static char* g_szExplosion = "Explosion";
//爆炸特效第一帧名
const static char* g_szExplosionFirstFrame = "explosion_01.png";

//子弹名称
//自己的
const static char* g_szLeftBullet = "Left Bullet";
const static char* g_szRightBullet = "Right Bullet";
//敌机的
const static char* g_szEnemyBullet = "Enemy Bullet";

//描述文字中文key
static const char* g_szAboutChinese = "about_chinese";
static const char* g_szAboutEnglish = "about_english";

//纹理位置

//飞机纹理位置
static Rect g_planeRect[] =
{
	{ 0, 0, 60, 38 },
	{ 0, 45, 60, 38 },
	{ 60, 0, 60, 38 }
};

//菜单按钮宽度
static const float g_fMenuWidth = 126.0f;
static const float g_fMenuHeight = 33.0f;//菜单按钮高度

//关于标题
static Rect g_aboutRect{ 0, 36, 100, 34 };
//设置标题
static Rect g_settingRect{ 0, 0, 134, 34 };
//子弹与飞机之前的差值
static const float g_fBulletOffset = 13.0f;



//游戏参数

//在同时刻最大产生多少个敌机
//这个暂定3只
const static int g_nMaxCreateEnemy = 3;

//飞机出生时多少时间后才会受到攻击的伤害
const static int g_fAttackedTime = 3.0f;

//游戏界面移动速度
static const int g_fMapMoveSpeed = 3.0f;
//天空层第次移动的距离
static const int g_fSkyMoveDistance = 48.0f;
//地图层每次移动的距离
static const int g_fMapMoveDiatance = 200.0f;

//飞机和生命次数
static const int g_nMaxLife = 3;

//默认攻击力
static const int g_nPower = 1;

//子弹默认速度(0.1s移动100个单位)
static const float g_fBulletSpeed = 80 / 0.1f;

//默认敌机子弹最小发射速度(值小的发射速度快,这里是多少秒发射子弹的意思)
static const float g_fMinShootSpeed = 0.8f;
static const float g_fMaxShootSpeed = 2.f;
//敌机默认移动速度(1秒移动300.0f)()
static const float g_fMinMoveSpeed = 80.f;
static const float g_fMaxMoveSpeed = 150.f;

//是否显示fps
static bool g_bIsShowFPS = false;

//飞机默认出现位置
static Vec2 g_defaultPlanePosition{ 160, 60 };

//飞机默认生命值
static int g_nHP = 20;

//飞机的默认射击速度(等于敌机最小默认射击速度的0.5)
static float g_fAirplaneShootSpeed = 0.2f;

//飞机等级增加时增加的速度(说明一下，这个时间是代码发射子弹的间隔时间)
static float g_fAirplaneLvUpAddSpeed = -0.01f;
 
//飞机等级增加时增加的子弹威力
static int g_nAirplaneLvUpAddPower = 2;

//飞机最大等级
static int g_nAirplaneMaxLevel = 15;

//击杀多少敌机后飞机升一级
static int g_nKillEnemyLvUp = 2;

//每隔多少增加一次难度
static float g_fGameLvUpTime = 20.0f;


//游戏相关类型
enum class OpViewZOrder
{
	MyPlane,//自己的飞机
	Bullet,//子弹
	Enemy,//敌机
	Explode,//爆炸特效
	Effect,//特效
};

//攻击类型
enum class AttackModel
{
	Normal,//普通（自己默认为普通，敌机根据自己战机所对的方向发射）
	LockTarget,//锁定目标位置
	Boss,//boss攻击技能，在屏幕的2/3以上的地方随机移动
};

//敌机类型
enum class EnemyType
{
	Min,
	E0 = Min,
	E1,
	E2,
	E3,
	E4,
	E5,
	Max = E5,
};

//敌机移动类型
enum class EnemyMoveType
{
	MoveToProtagonist,//飞向玩家飞机的位置一直飞出 
	MoveToEnd,//一直往下飞
	MoveToLeftOrRight,//从屏幕中央移动到左或右
	MoveToPosThenLeftOrRigth,//垂直移动到一定位置，然后左右移动来回2次后移出屏幕
	MoveBoss,//目前游戏只一个类型的boss，谁有兴趣可以自己加
};

class GameConfig
{
	GameConfig();
public:
	~GameConfig();
	IMPLEMENT_SINGLETON(GameConfig);

	float getScreenWidth();

	float getScreenHeight();

	bool isShowFPS();

private:

	void readConfig();

private:

	Size m_screenSize;
	bool m_bIsShowFPS;
};

//子弹默认攻击半径
float attackScope();
