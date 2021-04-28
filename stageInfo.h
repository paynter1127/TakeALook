#pragma once
#include "gameNode.h"
//�� �������� ������ ������ �δ� Ŭ����

struct tagStageInfo
{
	image* img;

	//Ÿ�� ����
	int lv_castle;
	int lv_tower;
	//ĳ���� ����
	int lv_worrior;
	int lv_archer;
	int lv_megician;
	int lv_hero;
	
	//����(���)
	int reward_gold;
};

class stageInfo : public gameNode
{
public:// < ���� ���� �� > =============================================================
	tagStageInfo chapter1_stage1; //1é�� �������� 1
	tagStageInfo chapter1_stage2; //1é�� �������� 2
	tagStageInfo chapter1_stage5; //1é�� �������� 10
	tagStageInfo chapter2_stage1; //2é�� �������� 1



public:// < �Լ� ���� �� > =============================================================
	HRESULT init();
	void release();

	stageInfo() {}
	~stageInfo() {}
};

