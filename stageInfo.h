#pragma once
#include "gameNode.h"
//각 스테이지 정보를 저장해 두는 클래스

struct tagStageInfo
{
	image* img;

	//타워 레벨
	int lv_castle;
	int lv_tower;
	//캐릭터 레벨
	int lv_worrior;
	int lv_archer;
	int lv_megician;
	int lv_hero;
	
	//보상(골드)
	int reward_gold;
};

class stageInfo : public gameNode
{
public:// < 변수 선언 부 > =============================================================
	tagStageInfo chapter1_stage1; //1챕터 스테이지 1
	tagStageInfo chapter1_stage2; //1챕터 스테이지 2
	tagStageInfo chapter1_stage5; //1챕터 스테이지 10
	tagStageInfo chapter2_stage1; //2챕터 스테이지 1



public:// < 함수 선언 부 > =============================================================
	HRESULT init();
	void release();

	stageInfo() {}
	~stageInfo() {}
};

