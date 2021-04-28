#pragma once
#include "gameNode.h"




class userSkill : public gameNode
{
public:// < 변수 선언 부 > =============================================================


	//=================================

	int Count; //스킬 프레임 렌더용 카운트
	int index; //스킬 프레임 렌더용 인덱스


	int Ccount; //스킬 마법진 프레임 렌더용 카운트
	int Cindex; //스킬 마법진 프레임 렌더용 인덱스
	float Cscale; //마법진 크기 조절용 float


	POINT Meteor_Coordinates; //메테오 위치 조절

	POINT Meteor;
	RECT icon_Meteor;		 //하단 디스크립션 메테오
	RECT drag_icon_Meteor;	//드래그시 땅겨오는 아이콘 
	bool drag_Meteor; //아이콘 드래그 
	bool Use_Meteor;  //사용 여부

	int Meteor_Count; //메테오 떨어지는 횟수

	RECT Damage; //데미지 판정 주는 렉트

	//==========================



public:// < 함수 선언 부 > =============================================================





	HRESULT init();
	void release();
	void update();
	void render();

	userSkill() {}
	~userSkill() {}
};

