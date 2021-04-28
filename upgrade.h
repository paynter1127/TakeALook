#pragma once
#include "gameNode.h"
#include "character.h"

#define MAXUPGRADE 10


struct tagUnitStat
{
	int Lv;
	int Hp;
	int att;
	int price;
	int priceUp;
};

struct tagIcon
{
	int x;
	int y;
	RECT icon;
	RECT Micon;
	int IconSize;
	float scale;
	bool Click;
	string ImageKey;
	string MImageKey;
	string Class;

	string Discrption1;
	string Discrption2;
	string Discrption3;

};


class upgrade : public gameNode
{
public:// < 변수 선언 부 > =============================================================

	RECT ShowShop;


	RECT NON; //충돌확인용 렉트


	RECT iconSizeSet;
	float iconSizeSet_X;
	int IconSize;
	int IconDistance;

	RECT ShopBG;	//업그레이드 백그라운드
	RECT Setting;	//업그레이드 뒤에 검은색 반투명한 렉트
	bool Scroll;	//스크롤해서 캐릭터 렉트 가져오는용도
	long MouseMovingPoint; //스크롤할때 마우스값 저장하는 변수

	int alpha;
	int BgAlpha;
	//ㅡㅡㅡㅡㅡㅡㅡㅡ디스트럭션& 업그레이드 선택ㅡㅡㅡㅡㅡㅡㅡ

	RECT Distruction;
	RECT ShowStat;
	RECT Upgrade;
	RECT Player_Gold;

	RECT UpgradeCheck;
	RECT Yes;
	RECT No;
	bool PopUp;

	RECT ShowLv;

	bool BuySound;
	//=====================================유닛=======================================

	bool ShowUnitUpgrade;
	RECT UnitUpgradeRc;

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ


	tagUnitStat WorriorStat;	//유닛 스텟 올라가는지 확인하기 위헤서 선언한 구조체
	tagUnitStat ArchorStat;
	tagUnitStat MageStat;
	tagUnitStat HeroStat;

	vector<tagUnitStat> Unit_Stat;

	tagUnitStat Worrior_Up;
	tagUnitStat Archor_Up;
	tagUnitStat Mage_Up;
	tagUnitStat Hero_Up;

	vector<tagUnitStat> Unit_Up;

	bool LoadData; //상점 페이지 들어가면 애들 정보를 불러오기 위한 bool변수
				   //상점페이지 돌입시 변환 (아직 미완성 테스트용)
	int gold;	   //Playerinfo에 들어간 골드를 불러오고, 대입하기 위한 변수

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ아이콘ㅡㅡㅡㅡㅡㅡㅡㅡㅡ 
	tagIcon icon_Warrior;
	tagIcon icon_Archor;
	tagIcon icon_Mage;
	tagIcon icon_Hero;

	vector<tagIcon> icon_Class;// 0=전사 , 1=궁수, 2=마법사, 3=영웅


	//===================================건물 업그레이드===============================

	bool ShowObjectUpgrade;
	RECT ObjectUpgradeRc;

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	tagIcon icon_Cassle;
	tagIcon icon_Tower;

	vector<tagIcon> icon_Object;

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	tagUnitStat CassleStat;
	tagUnitStat TowerStat;

	tagUnitStat Cassle_Up;
	tagUnitStat Tower_Up;

	vector<tagUnitStat> Object_Stat;
	vector<tagUnitStat> Object_Up;


public:// < 함수 선언 부 > =============================================================


	HRESULT init();
	void release();
	void update();
	void render();

	void iconScroll();
	void Upgrade_Unit(int Num);
	void Upgrade_Object(int Num);

	tagUnitStat Show_Unit_Stat(int Num, int Lv);
	tagUnitStat Show_Object_Stat(int Num, int Lv);

	upgrade() {}
	~upgrade() {}
};

