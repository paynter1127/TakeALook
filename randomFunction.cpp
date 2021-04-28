#include "stdafx.h"
#include "randomFunction.h"

HRESULT randomFunction::init()
{
	//�����õ� �ʱ�ȭ
	//srand(time(NULL));
	srand(GetTickCount());
	return S_OK;
}

void randomFunction::release()
{
}

int randomFunction::range(int num)
{
	return rand() % num;
}

int randomFunction::range(int fromNum, int toNum)
{
	return rand() % (toNum - fromNum + 1) + fromNum;
}

float randomFunction::range(float num)
{
	//rand() => 0 ~ 32767
	//RAND_MAX => 32767
	//rand() / RAND_MAX => ���� ����(0.0 ~ 1.0f)
	return ((float)rand() / (float)RAND_MAX) * num;
}

float randomFunction::range(float fromNum, float toNum)
{
	float rnd = (float)rand() / (float)RAND_MAX;
	return (rnd * (toNum - fromNum) + 1);
}
