#pragma once
#include "singletonBase.h"
class randomFunction :
	public singletonBase <randomFunction>
{
public:
	HRESULT init();
	void release();

	//���� 1�� �������� ��������
	int range(int num);
	//���� 2�� ������ �� �������� ��������
	int range(int fromNum, int toNum);
	//�Ǽ� 1�� �������� ��������
	float range(float num);
	//�Ǽ� 2�� ������ �� �������� ��������
	float range(float fromNum, float toNum);

	randomFunction() {}
	~randomFunction() {}
};

