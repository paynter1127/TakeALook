#include "stdafx.h"
#include "title.h"

HRESULT title::init()
{

	count = 0;
	check = false;
	//SOUNDMANAGER->play("p1");
	
	SOUNDMANAGER->play("브금_타이틀", 0.3f);
	

	return S_OK;
}

void title::release()
{
}

void title::update()
{
	

	count++;
	if (IMAGEMANAGER->findImage("monster")->getX() > WINSIZEX / 2 + 000)
		IMAGEMANAGER->findImage("monster")->setX(IMAGEMANAGER->findImage("monster")->getX() - 10);
	if (IMAGEMANAGER->findImage("hero")->getX() < -350)
		IMAGEMANAGER->findImage("hero")->setX(IMAGEMANAGER->findImage("hero")->getX() + 10);

	if (count == 150)
	{
		IMAGEMANAGER->findImage("start")->setX(WINSIZEX / 2 - 80);
		IMAGEMANAGER->findImage("start")->setY(WINSIZEY / 2 + 36);
		rc = RectMake(IMAGEMANAGER->findImage("start")->getX(), IMAGEMANAGER->findImage("start")->getY(), 204, 138);

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&rc, _ptMouse))
			//if (_ptMouse.x > _start->getX() && _ptMouse.x<_start->getX() + _start->getWidth() &&
			//	_ptMouse.y>_start->getY() && _ptMouse.y < _start->getY() + _start->getHeight())
		{
			check = true;
			SOUNDMANAGER->play("버튼");
			//SCENEMANAGER->loadScene("로딩화면");
			SOUNDMANAGER->stop("브금_타이틀");
			SOUNDMANAGER->play("브금_로비", 0.2f);
			SCENEMANAGER->loadScene("lobby");
		}
	}
}

void title::render()
{
	IMAGEMANAGER->findImage("title_bg")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("monster")->render(getMemDC(), IMAGEMANAGER->findImage("monster")->getX(), IMAGEMANAGER->findImage("monster")->getY());
	IMAGEMANAGER->findImage("hero")->render(getMemDC(), IMAGEMANAGER->findImage("hero")->getX(), IMAGEMANAGER->findImage("hero")->getY());
	IMAGEMANAGER->findImage("start")->render(getMemDC(), IMAGEMANAGER->findImage("start")->getX(), IMAGEMANAGER->findImage("start")->getY());
	//TextOut(getMemDC(), WINSIZEX / 2, 20, "로비(재혀기)", strlen("로비(재혀기)"));

	//textOutFont(getMemDC(), 280, 060, "TINY", 100, RGB(255, 255, 255));
	//textOutFont(getMemDC(), 280, 160, "HERO", 100, RGB(255, 255, 255));
	IMAGEMANAGER->findImage("title")->render(getMemDC(), 230, 60);
}
