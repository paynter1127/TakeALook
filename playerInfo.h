#pragma once
#include "singletonBase.h"

class playerInfo : public singletonBase<playerInfo>
{
public:// < 변수 선언 부 > =============================================================
	//소지금
	int gold;
	//타워 레벨
	int lv_castle;
	int lv_tower;
	//캐릭터 레벨
	int lv_worrior;
	int lv_archer;
	int lv_megician;
	int lv_hero;
	//스킬 레벨
	int num_skill1;
	int num_skill2;
	int num_skill3;
	

	// < 추가 변수 > =============================================================
	//스테이지
	int lv_stage;


public:// < 함수 선언 부 > =============================================================
	HRESULT init();
	void release();
	void update();


	playerInfo() {}
	~playerInfo() {}
};

