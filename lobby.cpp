#include "stdafx.h"
#include "lobby.h"

HRESULT lobby::init()
{


	IMAGEMANAGER->findImage("onoff")->setFrameX(0);
	IMAGEMANAGER->findImage("speed")->setFrameX(0);
	count = 0;
	a = 0;
	_rc[0] = RectMake(40, 100, 180, 100);
	_rc[1] = RectMake(40, 250, 180, 100);
	_rc[2] = RectMake(40, 400, 180, 100);
	_rc[3] = RectMake(350, 100, 285, 315);
	set_rc = RectMake(WINSIZEX - 110, 7, 36, 36);
	exit_rc = RectMake(WINSIZEX - 60, 7, 36, 36);
	gold_rc = RectMake(WINSIZEX - 296, 7, 170, 36);
	win = false;
	window = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 370, 290);
	ex = RectMake(window.right - 50, window.top, 50, 50);
	//sound = RectMake(window.left + 100, window.top + 50, 88, 80);

	//speed = RectMake(save.right + 180, sound.top, 88, 80);
	sound = RectMake(window.left + 50, window.top + 30, 88, 80);
	speed = RectMake(sound.right + 50, sound.top, 88, 80);
	save = RectMake(sound.left, sound.top + 80, 88, 80);
	_speed = 0;
	state = 0;
	onoff = true;


	//SOUNDMANAGER->play("브금_로비", 0.3f);

	return S_OK;
}

void lobby::release()
{
}

void lobby::update()
{

	if (state == 0)
	{
		count++;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_rc[0], _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				SCENEMANAGER->loadScene("stageMap");
			}
			if (PtInRect(&_rc[1], _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				SCENEMANAGER->loadScene("Shop");
			}
			if (PtInRect(&_rc[2], _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				SCENEMANAGER->loadScene("upgrade");
			}
			if (PtInRect(&set_rc, _ptMouse))
			{
				//설정창 띄움
			//	popup();
				SOUNDMANAGER->play("버튼");
				state = 1;
			}
			if (PtInRect(&exit_rc, _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				//종료창 띄움
				PostMessage(_hWnd, WM_DESTROY, 0, 0);
			}
		}
		if (count % 7 == 0)
		{
			a++;
			if (a == 11)
				a = 0;
			IMAGEMANAGER->findImage("hero_lobby")->setFrameX(a);
			IMAGEMANAGER->findImage("진")->setFrameX(a);
			IMAGEMANAGER->findImage("별")->setFrameX(a % 4);
		}
	}
	else if (state == 1)
	{
		//대충 사운드조절이라는 내용
		if (win == false)
		{
			SOUNDMANAGER->play("종이");
			win = true;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&ex, _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				win = false;
				state = 0;
			}
			if (PtInRect(&sound, _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				//소리 on off라는 내용
				if (onoff == true)
				{
					//IMAGEMANAGER->findImage("onoff")->setFrameX(1);
					SOUNDMANAGER->pause("브금_로비");
					onoff = false;
				}
				else
				{
					//IMAGEMANAGER->findImage("onoff")->setFrameX(0);
					SOUNDMANAGER->resume("브금_로비");
					onoff = true;
				}
			}
			if (PtInRect(&save, _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				//세이브한다는내용
				savePlayer();
			}
			if (PtInRect(&speed, _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				//속도
				_speed++;
				if (_speed > 2)
				{
					_speed = 0;
				}
				IMAGEMANAGER->findImage("speed")->setFrameX(_speed);
			}
		}
	}
	wsprintf(str, "%d", playerInfo::getSingleton()->gold);
}

void lobby::render()
{
	IMAGEMANAGER->findImage("bg")->render(getMemDC(), 0, 0);

	IMAGEMANAGER->findImage("줄")->render(getMemDC(), 45, 340);
	IMAGEMANAGER->findImage("줄")->render(getMemDC(), 173, 340);
	IMAGEMANAGER->findImage("줄")->render(getMemDC(), 45, 200);
	IMAGEMANAGER->findImage("줄")->render(getMemDC(), 173, 200);
	IMAGEMANAGER->findImage("줄")->render(getMemDC(), 45, 50);
	IMAGEMANAGER->findImage("줄")->render(getMemDC(), 173, 50);
	//IMAGEMANAGER->findImage("줄")->render(getMemDC(), 105, 0);
	//IMAGEMANAGER->findImage("줄")->render(getMemDC(), 233, 0);
	IMAGEMANAGER->findImage("popup")->render(getMemDC(), _rc[0].left, _rc[0].top);
	IMAGEMANAGER->findImage("popup")->render(getMemDC(), _rc[1].left, _rc[1].top);
	IMAGEMANAGER->findImage("popup")->render(getMemDC(), _rc[2].left, _rc[2].top);
	IMAGEMANAGER->findImage("st")->render(getMemDC(), _rc[0].left + 10, _rc[0].top);
	IMAGEMANAGER->findImage("shop")->render(getMemDC(), _rc[1].left + 10, _rc[1].top);
	IMAGEMANAGER->findImage("upgrade")->render(getMemDC(), _rc[2].left + 10, _rc[2].top);

	IMAGEMANAGER->findImage("box")->alphaRender(getMemDC(), 0, 0, 80);

	//_hero->render(getMemDC(), _rc[3].left, _rc[3].top);
	IMAGEMANAGER->findImage("hero_lobby")->frameRender(getMemDC(), _rc[3].left, _rc[3].top);
	//TextOut(getMemDC(), WINSIZEX / 2, 20, "로비(재혀기)", strlen("로비(재혀기)"));
	IMAGEMANAGER->findImage("setting")->render(getMemDC(), set_rc.left, set_rc.top);
	IMAGEMANAGER->findImage("goldbar")->render(getMemDC(), gold_rc.left, gold_rc.top);
	IMAGEMANAGER->findImage("exit")->render(getMemDC(), exit_rc.left, exit_rc.top);

	//textOutFont(getMemDC(), 450, 42, str, 50, RGB(255, 255, 255));
	//imageNum("숫자", getMemDC(), 570, 42, playerInfo::getSingleton()->gold, 26);
	imagescaleNum("숫자2", getMemDC(), WINSIZEX - 170, 14, playerInfo::getSingleton()->gold, 14, 0.5);

	if (state == 1)
	{
		popup();
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&save, _ptMouse))
				savePlayer();
		}
	}
	//IMAGEMANAGER->findImage("진")->frameRender(getMemDC(), WINSIZEX/2-200, WINSIZEY/2);



	//IMAGEMANAGER->findImage("별")->frameRender(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2 - 100);
	//IMAGEMANAGER->findImage("별")->setFrameX((a+1) % 4);
	//IMAGEMANAGER->findImage("별")->frameRender(getMemDC(), WINSIZEX / 2 - 70, WINSIZEY / 2 - 80);
	//IMAGEMANAGER->findImage("별")->setFrameX((a+3) % 4);
	//IMAGEMANAGER->findImage("별")->frameRender(getMemDC(), WINSIZEX / 2 +60, WINSIZEY / 2 - 100);

}

void lobby::popup()
{

	IMAGEMANAGER->findImage("window")->render(getMemDC(), window.left, window.top);
	IMAGEMANAGER->findImage("ex")->render(getMemDC(), ex.left, ex.top);

	//IMAGEMANAGER->findImage("onoff")->frameRender(getMemDC(), sound.left, sound.top);
	IMAGEMANAGER->findImage("button")->render(getMemDC(), sound.left, sound.top);
	if (onoff == true)
		textOutFont(getMemDC(), sound.left + 25, sound.top + 21, "ON", 35, RGB(0, 0, 0));
	else
		textOutFont(getMemDC(), sound.left + 20, sound.top + 21, "OFF", 35, RGB(0, 0, 0));

	textOutFont(getMemDC(), window.left + 20, window.bottom - 85, "SETTING", 80, RGB(0, 0, 0));

	//textOutFont(getMemDC(), sound.left-20, sound.top + 231, "SETTING", 95, RGB(0, 0, 0));

	//설정할 것 띄워야함(소리 등등)
	//게임속도
	//저장
	IMAGEMANAGER->findImage("button")->render(getMemDC(), speed.left, speed.top);
	IMAGEMANAGER->findImage("speed")->frameRender(getMemDC(), speed.left + 23, speed.top + 10);


	IMAGEMANAGER->findImage("button")->render(getMemDC(), save.left, save.top);

	textOutFont(getMemDC(), save.left + 15, save.top + 21, "SAVE", 35, RGB(0, 0, 0));
}
