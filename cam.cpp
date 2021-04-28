#include "stdafx.h"
#include "cam.h"

HRESULT cam::init()
{
	//��׶��� �̹��� �ʱ�ȭ
	_img = IMAGEMANAGER->addImage("�ż���", "�ż���.bmp", WINSIZEX, WINSIZEY);

	//ī�޶� ��Ʈ ��ġ �ʱ�ȭ
	_rcCam = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, CAMSIZEX, CAMSIZEY);

	return S_OK;
}

void cam::release()
{
}

void cam::update()
{
	//�����̽� ��� ���� �̹��� �̵�
	if (KEYMANAGER->isToggleKey(VK_SPACE))
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_img->setX(_img->getX() + 5.0f);
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_img->setX(_img->getX() - 5.0f);
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_img->setY(_img->getY() + 5.0f);
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_img->setY(_img->getY() - 5.0f);
		}
	}
	else //ī�޶� �̵�
	{
		//ī�޶� �̵� �� ȭ������� ������ �ʵ��� ó��
		if (KEYMANAGER->isStayKeyDown('A') && _rcCam.left > 0)
		{
			_rcCam.left -= 5;
			_rcCam.right -= 5;
		}
		if (KEYMANAGER->isStayKeyDown('D') && _rcCam.right < WINSIZEX)
		{
			_rcCam.left += 5;
			_rcCam.right += 5;
		}
		if (KEYMANAGER->isStayKeyDown('W') && _rcCam.top > 0)
		{
			_rcCam.top -= 5;
			_rcCam.bottom -= 5;
		}
		if (KEYMANAGER->isStayKeyDown('S') && _rcCam.bottom < WINSIZEY)
		{
			_rcCam.top += 5;
			_rcCam.bottom += 5;
		}

	}
}

void cam::render()
{
	//��׶���
	_img->render(getMemDC(), _rcCam.left, _rcCam.top, _img->getX() + _rcCam.left, _img->getY() + _rcCam.top, CAMSIZEX, CAMSIZEY);

	//RECT rc = RectMake(100, 100, 100, 100);
	//FrameRect(getMemDC(), rc, RGB(255, 255, 0));
	//��� �ִ� ��Ʈ �����ֱ�
	FrameRect(getMemDC(), _rcCam, RGB(255, 255, 0));

}
