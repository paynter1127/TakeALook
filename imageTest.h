#pragma once
#include "gameNode.h"

class imageTest : public gameNode
{
private:
	image* _testImg;
	//1. �������� (��׶��� �̹��� ����)
	int _loopX, _loopY;

	//2. �����Ϸ��� (�̹��� ũ��)
	//�����̹������� �۰��ϸ� ���� �����ϱ� ũ�� Ȯ������� ����� �Ұ�!!
	image* _img;		//�Ϲ� �̹���
	image* _frameImg;	//������ �̹���
	int _index, _count;	//������ �̹��� �ִϸ��̼ǿ�

	//3. ������Ʈ���� (�̹��� ����)
	//���� �ִ� �̹����� ����
	float _angle;		//ȸ�� ����

public:
	HRESULT init();
	void release();
	void update();
	void render();

	imageTest() {}
	~imageTest() {}
};

