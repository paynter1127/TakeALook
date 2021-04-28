#include "stdafx.h"
#include "imageTest.h"


HRESULT imageTest::init()
{
	_testImg = IMAGEMANAGER->addImage("�׽�Ʈ", "�ż���.bmp", 500, 500);

	//1. ��������
	//��׶��� �̹��� �� �������� ���� �ʱ�ȭ
	IMAGEMANAGER->addImage("��׶���", "�ż���.bmp", WINSIZEX, WINSIZEY);
	_loopX = _loopY = 0;


	//2. �����Ϸ���
	//�Ϲ��̹���, �������̹��� �� ���� �ʱ�ȭ
	_img = IMAGEMANAGER->addImage("�Լ�", "�Լ�.bmp", 118, 67, true, RGB(255, 0, 255));
	_frameImg = IMAGEMANAGER->addFrameImage("ȣ��", "ȣ��.bmp", 400.f, 400.f, 800, 264, 8, 2);
	_index = _count = 0;

	//3. ������Ʈ����
	_angle = 0.0f;

	return S_OK;
}

void imageTest::release()
{
}

void imageTest::update()
{
	//1. ��������
	//��׶��� ����
	//_loopX++;
	_loopX += 3;
	//_loopY--;

	//2. �����Ϸ���
	//������ �̹��� �ִϸ��̼�
	_count++;
	if (_count % 5 == 0)
	{
		_index++;
		if (_index > 7)
		{
			_index = 0;
		}
	}


	//3. ������Ʈ ����
	//������ ȭ�� ������ ���콺 ��ǥ�� ���ϱ�
	//_angle = getAngle(WINSIZEX / 2, WINSIZEY / 2, _ptMouse.x, _ptMouse.y);

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_angle += 0.05f;
	}

}

void imageTest::render()
{
	//1. ��������
	//������ų ��Ʈ�� ���� (ȭ�� ũ�⿵��)
	RECT rc = RectMake(100, 100, WINSIZEX - 200, WINSIZEY - 200);
	//IMAGEMANAGER->loopRender("��׶���", getMemDC(), &rc, _loopX, _loopY);

	//2. �����Ϸ���
	_img->render(getMemDC(), 100, 100);
	_img->scaleRender(getMemDC(), 300, 100, 1.5f);
	//������ �̹���
	//_frameImg->frameRender(getMemDC(), 100, 300, _index, 0);
	//_frameImg->scaleFrameRender(getMemDC(), 300, 300, _index, 0, 2.0f);

	//3. ������Ʈ����
	_img->rotateRender(getMemDC(), 600, 100, _angle);
	//������ �̹���
	_frameImg->rotateFrameRender(getMemDC(), 600, 300, _index, 0, _angle);

	//_testImg->rotateRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, _angle);

}
