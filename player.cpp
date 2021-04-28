#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init()
{
	//플레이어 이미지 초기화
	_rocket = IMAGEMANAGER->addImage("rocket", "rocket.bmp", WINSIZEX / 2, WINSIZEY - 100, 52, 64, true, RGB(255, 0, 255));
	//_rcPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 52, 64);
	
	//미사일 클래스 초기화
	_missile = new missile;
	_missile->init(10, 800);

	//폭탄 클래스 초기화
	_bomb = new bomb;
	_bomb->init(5, 600);


	return S_OK;
}

void player::release()
{
	//미사일 클래스 해제
	_missile->release();
	SAFE_DELETE(_missile);

	//폭탄 클래스 해제
	_bomb->release();
	SAFE_DELETE(_bomb);
}

void player::update()
{
	//이미지 바운딩박스로 충돌처리
	//RECT rc;
	//if(IntersectRect(&rc, &_rocket->boudingBox(), ))
	
	//플레이어 움직이기 & 화면밖으로 벗어나지 못하게
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rocket->getX() > 0)
	{
		_rocket->setX(_rocket->getX() - 5.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rocket->getX() < WINSIZEX)
	{
		_rocket->setX(_rocket->getX() + 5.0f);
	}
	//총알발사
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//총알클래스야 니꺼 발사시켜라~
		_missile->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}
	//폭탄발사
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		//폭탄클래스야 니꺼 발사시켜라~
		_bomb->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	//미사일 클래스 업데이트
	_missile->update();

	//폭탄 클래스 업데이트
	_bomb->update();


	//충돌
	RECT tttemp;
	for (int i = 0; i < eeenemyManager->getVMinion().size(); i++)
	{
				//system("pause");
		for (int j = 0; j < _missile->getMissile().size(); j++)
		{
			
			if (IntersectRect(&tttemp, &_getMissile()[j].rc, &eeenemyManager->getVMinion()[i]->getRect()))
			{
				eeenemyManager->removeMinion(i);
				getRemoveMissile(j);
			}
			if (i == eeenemyManager->getVMinion().size()) break;
		}
	}
	

}

void player::render()
{
	//플레이어 렌더
	_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());

	//미사일 클래스 렌더
	_missile->render();

	//폭탄 클래스 렌더
	_bomb->render();

}
