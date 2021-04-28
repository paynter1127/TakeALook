#include "stdafx.h"
#include "stageInfo.h"

HRESULT stageInfo::init()
{
	chapter1_stage1.lv_castle = 1;
	chapter1_stage1.lv_tower = 1;
	chapter1_stage1.lv_worrior = 1;
	chapter1_stage1.lv_archer = 1;
	chapter1_stage1.lv_megician = 1;
	chapter1_stage1.lv_hero = 1;
	chapter1_stage1.reward_gold = 3000;
	
	//위에 레벨 초기화해준 에너미들 이미지 초기화 아래에 해주십셔
	//이 후 우리는 stage 불러 올때 stageInfo 에 저장된 정보를 로드하여 출력해줄겁니다.
	chapter1_stage1.img = IMAGEMANAGER->findImage("배경1"); //1챕터 스테이지 1
	chapter1_stage2.img = IMAGEMANAGER->findImage("배경2"); //1챕터 스테이지 2
	chapter1_stage5.img = IMAGEMANAGER->findImage("배경5"); //1챕터 스테이지 5
	chapter2_stage1.img = IMAGEMANAGER->findImage("배경6"); //2챕터 스테이지 1

	return S_OK;
}

void stageInfo::release()
{
}
