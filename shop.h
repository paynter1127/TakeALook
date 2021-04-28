#pragma once
#include "gameNode.h"


struct tagIcon2
{
	int x;
	int y;
	RECT icon;
	RECT Micon;
	int IconSize;
	float scale;
	bool Click;
	string ImageKey;
	string MimageKey;
	string BimageKey;
	string Name;
	int price;

	string Discription1;
	string Discription2;
	string Discription3;

};



class shop : public gameNode
{
public:// < 변수 선언 부 > =============================================================

	RECT ShowUpgrade; //상점->업그레이드 쪽으로 돌아가기 위한 렉트 


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

	int Count;
	int index;
	int Kcount;
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	RECT BuyCheck;
	RECT Yes;
	RECT No;
	bool PopUp;

	int SoundCount;
	bool SoundCheck;
	//ㅡㅡㅡㅡㅡㅡㅡㅡ디스트럭션& 업그레이드 선택ㅡㅡㅡㅡㅡㅡㅡ

	RECT Distruction;
	RECT ShowStat;
	RECT BuySkill;
	RECT Player_Gold;

	RECT Skill_getCount;

	int Count_BlackHole;
	int Count_Meteor;
	int Count_Heal;

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	tagIcon2 icon_BlackHole;
	tagIcon2 icon_Meteor;
	tagIcon2 icon_Heal;

	vector<tagIcon2> icon_Skill;
	vector<int>  Count_Skill;

public:// < 함수 선언 부 > =============================================================






	HRESULT init();
	void release();
	void update();
	void render();

	void iconScroll();
	void getSkill();

	shop() {}
	~shop() {}
};

