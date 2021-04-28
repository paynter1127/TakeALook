#include "stdafx.h"
#include "stageMap.h"

HRESULT stageMap::init()
{

	_stage = new stage;
	_stage->init();

	_rc[0] = RectMake(160, 185, 80, 80);
	_rc[1] = RectMake(230, 240, 80, 140);
	_rc[2] = RectMake(335, 245, 80, 80);
	_rc[3] = RectMake(503, 297, 80, 80);
	_rc[4] = RectMake(528, 155, 80, 80);
	//lv_stage;

	loadPlayer();
	lv_stage = playerInfo::getSingleton()->lv_stage;
	stage_rc[0] = RectMake(150, 450, 50, 50);
	stage_rc[1] = RectMake(250, 450, 50, 50);
	stage_rc[2] = RectMake(350, 450, 50, 50);
	stage_rc[3] = RectMake(450, 450, 50, 50);
	stage_rc[4] = RectMake(550, 450, 50, 50);

	back_rc = RectMake(4, 7, 36, 36);

	count = 0;
	a = 7;
	state = 0;
	_alpha = 0;


	return S_OK;
}

void stageMap::release()
{
	_stage->release();
	SAFE_DELETE(_stage);
}

void stageMap::update()
{
	if (count == 1)
	{
		SOUNDMANAGER->play("지도");

	}
	count++;
	//if (KEYMANAGER->isToggleKey(VK_LBUTTON))   //지도펴기
	{
		if (count % 3 == 0)
		{
			a--;
			if (a < 0)
				a = 0;
			IMAGEMANAGER->findImage("stage_bg")->setFrameX(a);
		}
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 5; i++)
		{
			if (PtInRect(&_rc[i], _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				state = i + 1;
				break;
			}
		}
		if (PtInRect(&back_rc, _ptMouse))
		{
			SCENEMANAGER->loadScene("lobby");
		}
	}
	if (state != 0)
	{
		if (_a)
		{
			_alpha += 5;
			if (_alpha > 254)
			{
				_alpha = 255;
				_a = !(_a);
			}
		}

		else
		{
			_alpha -= 5;
			if (_alpha < 1)
			{
				_alpha = 0;
				_a = !(_a);
			}
		}
	}



}

void stageMap::render()
{
	//   _table->render(getMemDC(), 0, 0);
	if (state == 0)
	{
		IMAGEMANAGER->findImage("table")->render(getMemDC(), 0, 0);
		IMAGEMANAGER->findImage("stage_bg")->frameRender(getMemDC(), 70, 90);
		IMAGEMANAGER->findImage("box")->alphaRender(getMemDC(), 0, 0, 80);
		IMAGEMANAGER->findImage("back")->render(getMemDC(), 4, 7);

		if (KEYMANAGER->isToggleKey(VK_LSHIFT))
		{
			//IMAGEMANAGER->findImage("alpha")->alphaRender(getMemDC(), 67, 90, 200);
			Rectangle(getMemDC(), _rc[0]);
			Rectangle(getMemDC(), _rc[1]);
			Rectangle(getMemDC(), _rc[2]);
			Rectangle(getMemDC(), _rc[3]);
			Rectangle(getMemDC(), _rc[4]);
		}

	}

	else if (state == 1)
	{
		IMAGEMANAGER->findImage("table")->render(getMemDC(), 0, 0);

		IMAGEMANAGER->findImage("stage_bg")->frameRender(getMemDC(), 70, 90);

		//IMAGEMANAGER->findImage("alpha")->alphaRender(getMemDC(), 67, 90, 200);
		IMAGEMANAGER->findImage("stage1")->alphaRender(getMemDC(), 67, 88, _alpha);
		IMAGEMANAGER->findImage("box")->alphaRender(getMemDC(), 0, 0, 80);
		IMAGEMANAGER->findImage("back")->render(getMemDC(), 4, 7);

		//for (int i = 0; i < 5; i++)
		//{
		//   IMAGEMANAGER->findImage("stage_num")->setFrameX(i);
		//   IMAGEMANAGER->findImage("stage_num")->frameRender(getMemDC(), stage_rc[i].left, stage_rc[i].top);
		//}


		//num= 현재 스테이지 레벨
		stagenum(state, lv_stage);


		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 5; i++)
			{
				if (PtInRect(&stage_rc[i], _ptMouse))
				{
					SOUNDMANAGER->play("버튼");
					stagesel(state, lv_stage);
					break;
				}
			}
		}


		if (KEYMANAGER->isToggleKey(VK_LSHIFT))
		{
			Rectangle(getMemDC(), stage_rc[0]);
			Rectangle(getMemDC(), stage_rc[1]);
			Rectangle(getMemDC(), stage_rc[2]);
			Rectangle(getMemDC(), stage_rc[3]);
			Rectangle(getMemDC(), stage_rc[4]);
		}
	}
	else if (state == 2)
	{
		IMAGEMANAGER->findImage("table")->render(getMemDC(), 0, 0);

		IMAGEMANAGER->findImage("stage_bg")->frameRender(getMemDC(), 70, 90);

		//IMAGEMANAGER->findImage("alpha")->alphaRender(getMemDC(), 67, 90, 200);
		IMAGEMANAGER->findImage("stage2")->alphaRender(getMemDC(), 67, 90, _alpha);
		IMAGEMANAGER->findImage("box")->alphaRender(getMemDC(), 0, 0, 80);
		IMAGEMANAGER->findImage("back")->render(getMemDC(), 4, 7);

		stagenum(state, lv_stage);


		//for (int i = 0; i < 5; i++)
		//{
		//   IMAGEMANAGER->findImage("stage_num")->setFrameX(i);
		//   IMAGEMANAGER->findImage("stage_num")->frameRender(getMemDC(), stage_rc[i].left, stage_rc[i].top);
		//}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 5; i++)
			{
				if (PtInRect(&stage_rc[i], _ptMouse))
				{
					SOUNDMANAGER->play("버튼");
					stagesel(state, lv_stage);
					break;
				}
			}
		}
		if (KEYMANAGER->isToggleKey(VK_LSHIFT))
		{
			Rectangle(getMemDC(), stage_rc[0]);
			Rectangle(getMemDC(), stage_rc[1]);
			Rectangle(getMemDC(), stage_rc[2]);
			Rectangle(getMemDC(), stage_rc[3]);
			Rectangle(getMemDC(), stage_rc[4]);
		}
	}
	else if (state == 3)
	{
		IMAGEMANAGER->findImage("table")->render(getMemDC(), 0, 0);

		IMAGEMANAGER->findImage("stage_bg")->frameRender(getMemDC(), 70, 90);

		//IMAGEMANAGER->findImage("alpha")->alphaRender(getMemDC(), 67, 90, 200);
		IMAGEMANAGER->findImage("stage3")->alphaRender(getMemDC(), 67, 90, _alpha);
		IMAGEMANAGER->findImage("box")->alphaRender(getMemDC(), 0, 0, 80);
		IMAGEMANAGER->findImage("back")->render(getMemDC(), 4, 7);

		stagenum(state, lv_stage);
		//for (int i = 0; i < 5; i++)
		//{
		//   IMAGEMANAGER->findImage("stage_num")->setFrameX(i);
		//   IMAGEMANAGER->findImage("stage_num")->frameRender(getMemDC(), stage_rc[i].left, stage_rc[i].top);
		//}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 5; i++)
			{
				if (PtInRect(&stage_rc[i], _ptMouse))
				{
					SOUNDMANAGER->play("버튼");
					stagesel(state, lv_stage);
					break;
				}
			}
		}
		if (KEYMANAGER->isToggleKey(VK_LSHIFT))
		{
			Rectangle(getMemDC(), stage_rc[0]);
			Rectangle(getMemDC(), stage_rc[1]);
			Rectangle(getMemDC(), stage_rc[2]);
			Rectangle(getMemDC(), stage_rc[3]);
			Rectangle(getMemDC(), stage_rc[4]);
		}
	}
	else if (state == 4)
	{
		IMAGEMANAGER->findImage("table")->render(getMemDC(), 0, 0);

		IMAGEMANAGER->findImage("stage_bg")->frameRender(getMemDC(), 70, 90);

		//IMAGEMANAGER->findImage("alpha")->alphaRender(getMemDC(), 67, 90, 200);
		IMAGEMANAGER->findImage("stage4")->alphaRender(getMemDC(), 67, 90, _alpha);
		IMAGEMANAGER->findImage("box")->alphaRender(getMemDC(), 0, 0, 80);
		IMAGEMANAGER->findImage("back")->render(getMemDC(), 4, 7);

		stagenum(state, lv_stage);
		//for (int i = 0; i < 5; i++)
		//{
		//   IMAGEMANAGER->findImage("stage_num")->setFrameX(i);
		//   IMAGEMANAGER->findImage("stage_num")->frameRender(getMemDC(), stage_rc[i].left, stage_rc[i].top);
		//}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 5; i++)
			{
				if (PtInRect(&stage_rc[i], _ptMouse))
				{
					SOUNDMANAGER->play("버튼");
					stagesel(state, lv_stage);
					break;
				}
			}
		}
		if (KEYMANAGER->isToggleKey(VK_LSHIFT))
		{
			Rectangle(getMemDC(), stage_rc[0]);
			Rectangle(getMemDC(), stage_rc[1]);
			Rectangle(getMemDC(), stage_rc[2]);
			Rectangle(getMemDC(), stage_rc[3]);
			Rectangle(getMemDC(), stage_rc[4]);
		}
	}
	else if (state == 5)
	{
		IMAGEMANAGER->findImage("table")->render(getMemDC(), 0, 0);

		IMAGEMANAGER->findImage("stage_bg")->frameRender(getMemDC(), 70, 90);

		//IMAGEMANAGER->findImage("alpha")->alphaRender(getMemDC(), 67, 90, 200);
		IMAGEMANAGER->findImage("stage5")->alphaRender(getMemDC(), 67, 90, _alpha);
		IMAGEMANAGER->findImage("box")->alphaRender(getMemDC(), 0, 0, 80);
		IMAGEMANAGER->findImage("back")->render(getMemDC(), 4, 7);

		stagenum(state, lv_stage);
		//for (int i = 0; i < 5; i++)
		//{
		//   IMAGEMANAGER->findImage("stage_num")->setFrameX(i);
		//   IMAGEMANAGER->findImage("stage_num")->frameRender(getMemDC(), stage_rc[i].left, stage_rc[i].top);
		//}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 5; i++)
			{
				if (PtInRect(&stage_rc[i], _ptMouse))
				{
					SOUNDMANAGER->play("버튼");
					stagesel(state, lv_stage);
					break;
				}
			}
		}
		if (KEYMANAGER->isToggleKey(VK_LSHIFT))
		{
			Rectangle(getMemDC(), stage_rc[0]);
			Rectangle(getMemDC(), stage_rc[1]);
			Rectangle(getMemDC(), stage_rc[2]);
			Rectangle(getMemDC(), stage_rc[3]);
			Rectangle(getMemDC(), stage_rc[4]);
		}
	}

	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//   if (PtInRect(&back_rc, _ptMouse))
	//   {
	//      SCENEMANAGER->loadScene("lobby");
	//   }
	//}


	//sprintf(buf, "%d %d", _ptMouse.x, _ptMouse.y);
	//TextOut(getMemDC(), 0, 0, buf, strlen(buf));

	

}

void stageMap::stagenum(int state, int num)
{
	int a = num / 5;
	int b = num % 5;

	for (int i = 0; i < 5; i++)
	{
		if (state > a + 1)
		{
			//자물쇠 렌더하면됨
			IMAGEMANAGER->findImage("stage_num")->setFrameX(i);
			IMAGEMANAGER->findImage("stage_num")->frameRender(getMemDC(), stage_rc[i].left, stage_rc[i].top);
			IMAGEMANAGER->findImage("lock")->render(getMemDC(), stage_rc[i].left, stage_rc[i].top);

		}
		else if (state == a + 1)
		{
			if (i > b)
			{
				//자물쇠 렌더하면됨
				IMAGEMANAGER->findImage("stage_num")->setFrameX(i);
				IMAGEMANAGER->findImage("stage_num")->frameRender(getMemDC(), stage_rc[i].left, stage_rc[i].top);
				IMAGEMANAGER->findImage("lock")->render(getMemDC(), stage_rc[i].left, stage_rc[i].top);
			}
			else
			{
				IMAGEMANAGER->findImage("stage_num")->setFrameX(i);
				IMAGEMANAGER->findImage("stage_num")->frameRender(getMemDC(), stage_rc[i].left, stage_rc[i].top);
			}
		}
		if (state < a + 1)
		{
			IMAGEMANAGER->findImage("stage_num")->setFrameX(i);
			IMAGEMANAGER->findImage("stage_num")->frameRender(getMemDC(), stage_rc[i].left, stage_rc[i].top);
		}
	}
}

void stageMap::stagesel(int state, int num)
{
	int a = num / 5;
	int b = num % 5;


	for (int i = 0; i < 5; i++)
	{
		if (state > a + 1)
		{
			//잠겨서 못들어간다는 내용
		}
		if (state == a + 1)
		{
			if (i > b)
			{
				//잠겨서 못들어간다는 내용
			}
			else
			{
				SOUNDMANAGER->stop("브금_로비");
				SOUNDMANAGER->play("브금_스테이지", 0.1f);
				SCENEMANAGER->loadScene("stage");
			}
		}
		if (state < a + 1)
		{
			SOUNDMANAGER->stop("브금_로비");
			SOUNDMANAGER->play("브금_스테이지", 0.1f);
			SCENEMANAGER->loadScene("stage");
		}
	}
}