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
	
	//���� ���� �ʱ�ȭ���� ���ʹ̵� �̹��� �ʱ�ȭ �Ʒ��� ���ֽʼ�
	//�� �� �츮�� stage �ҷ� �ö� stageInfo �� ����� ������ �ε��Ͽ� ������̴ٰϴ�.
	chapter1_stage1.img = IMAGEMANAGER->findImage("���1"); //1é�� �������� 1
	chapter1_stage2.img = IMAGEMANAGER->findImage("���2"); //1é�� �������� 2
	chapter1_stage5.img = IMAGEMANAGER->findImage("���5"); //1é�� �������� 5
	chapter2_stage1.img = IMAGEMANAGER->findImage("���6"); //2é�� �������� 1

	return S_OK;
}

void stageInfo::release()
{
}
