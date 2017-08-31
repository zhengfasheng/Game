#pragma once
//��Ϸ�Ļ�������
#include "cocos2d.h"
#include "Singleton.h"
USING_NS_CC;

//static cocos2d::Size designResolutionSize = cocos2d::Size(320, 480);
//static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
//static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

//���key

//�����߷�
const static char* g_szBestScoreKey = "bestScore";
//��ҵı�������
const static char* g_szBackMusicKey = "backMusic";
//��ҵ���Ч
const static char* g_szAudioKey = "audio";

//��Ϸ�¼�����������
const static char* g_szEventListenerName = "Game Event Listener";

//���ӷ����¼�����
const static char* g_szEventAddScore = "Add Score";

//ɾ���ӵ��¼�����
const static char* g_szEventDeleteMyBullet = "Delete My Bullet";

//ɾ���л�
const static char* g_szEventDeleteEnemy = "Delete Enemy";

//��ҷɻ�ûѪ֪ͨ
const static char* g_szEventPlayerPlaneDestroy = "Player Plane Destroy";

//��ҷɻ�����֪ͨ
const static char* g_szEventPlayerPlaneReborn = "Player Plane Reborn";

//�ɻ�����
const static char* g_szEventLvUp = "Lv Up";

//��ը��Ч������
const static char* g_szExplosion = "Explosion";
//��ը��Ч��һ֡��
const static char* g_szExplosionFirstFrame = "explosion_01.png";

//�ӵ�����
//�Լ���
const static char* g_szLeftBullet = "Left Bullet";
const static char* g_szRightBullet = "Right Bullet";
//�л���
const static char* g_szEnemyBullet = "Enemy Bullet";

//������������key
static const char* g_szAboutChinese = "about_chinese";
static const char* g_szAboutEnglish = "about_english";

//����λ��

//�ɻ�����λ��
static Rect g_planeRect[] =
{
	{ 0, 0, 60, 38 },
	{ 0, 45, 60, 38 },
	{ 60, 0, 60, 38 }
};

//�˵���ť���
static const float g_fMenuWidth = 126.0f;
static const float g_fMenuHeight = 33.0f;//�˵���ť�߶�

//���ڱ���
static Rect g_aboutRect{ 0, 36, 100, 34 };
//���ñ���
static Rect g_settingRect{ 0, 0, 134, 34 };
//�ӵ���ɻ�֮ǰ�Ĳ�ֵ
static const float g_fBulletOffset = 13.0f;



//��Ϸ����

//��ͬʱ�����������ٸ��л�
//����ݶ�3ֻ
const static int g_nMaxCreateEnemy = 3;

//�ɻ�����ʱ����ʱ���Ż��ܵ��������˺�
const static int g_fAttackedTime = 3.0f;

//��Ϸ�����ƶ��ٶ�
static const int g_fMapMoveSpeed = 3.0f;
//��ղ�ڴ��ƶ��ľ���
static const int g_fSkyMoveDistance = 48.0f;
//��ͼ��ÿ���ƶ��ľ���
static const int g_fMapMoveDiatance = 200.0f;

//�ɻ�����������
static const int g_nMaxLife = 3;

//Ĭ�Ϲ�����
static const int g_nPower = 1;

//�ӵ�Ĭ���ٶ�(0.1s�ƶ�100����λ)
static const float g_fBulletSpeed = 80 / 0.1f;

//Ĭ�ϵл��ӵ���С�����ٶ�(ֵС�ķ����ٶȿ�,�����Ƕ����뷢���ӵ�����˼)
static const float g_fMinShootSpeed = 0.8f;
static const float g_fMaxShootSpeed = 2.f;
//�л�Ĭ���ƶ��ٶ�(1���ƶ�300.0f)()
static const float g_fMinMoveSpeed = 80.f;
static const float g_fMaxMoveSpeed = 150.f;

//�Ƿ���ʾfps
static bool g_bIsShowFPS = false;

//�ɻ�Ĭ�ϳ���λ��
static Vec2 g_defaultPlanePosition{ 160, 60 };

//�ɻ�Ĭ������ֵ
static int g_nHP = 20;

//�ɻ���Ĭ������ٶ�(���ڵл���СĬ������ٶȵ�0.5)
static float g_fAirplaneShootSpeed = 0.2f;

//�ɻ��ȼ�����ʱ���ӵ��ٶ�(˵��һ�£����ʱ���Ǵ��뷢���ӵ��ļ��ʱ��)
static float g_fAirplaneLvUpAddSpeed = -0.01f;
 
//�ɻ��ȼ�����ʱ���ӵ��ӵ�����
static int g_nAirplaneLvUpAddPower = 2;

//�ɻ����ȼ�
static int g_nAirplaneMaxLevel = 15;

//��ɱ���ٵл���ɻ���һ��
static int g_nKillEnemyLvUp = 2;

//ÿ����������һ���Ѷ�
static float g_fGameLvUpTime = 20.0f;


//��Ϸ�������
enum class OpViewZOrder
{
	MyPlane,//�Լ��ķɻ�
	Bullet,//�ӵ�
	Enemy,//�л�
	Explode,//��ը��Ч
	Effect,//��Ч
};

//��������
enum class AttackModel
{
	Normal,//��ͨ���Լ�Ĭ��Ϊ��ͨ���л������Լ�ս�����Եķ����䣩
	LockTarget,//����Ŀ��λ��
	Boss,//boss�������ܣ�����Ļ��2/3���ϵĵط�����ƶ�
};

//�л�����
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

//�л��ƶ�����
enum class EnemyMoveType
{
	MoveToProtagonist,//������ҷɻ���λ��һֱ�ɳ� 
	MoveToEnd,//һֱ���·�
	MoveToLeftOrRight,//����Ļ�����ƶ��������
	MoveToPosThenLeftOrRigth,//��ֱ�ƶ���һ��λ�ã�Ȼ�������ƶ�����2�κ��Ƴ���Ļ
	MoveBoss,//Ŀǰ��Ϸֻһ�����͵�boss��˭����Ȥ�����Լ���
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

//�ӵ�Ĭ�Ϲ����뾶
float attackScope();
