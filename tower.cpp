#include "stdafx.h"
#include "tower.h"

HRESULT tower::init()
{

	//ZeroMemory(&Tower[0], sizeof(tagTower));
	ZeroMemory(&Tower[1], sizeof(tagTower));




	Tower[1].img = IMAGEMANAGER->addImage("利鸥况","利鸥况.bmp", 100, 300, 120, 120, true, RGB(255, 0, 255));
	Tower[1].lv = 1;
	Tower[1].hp = 100 + 40 * Tower[1].lv;
	Tower[1].maxhp = 100 + 40 * Tower[1].lv;
	Tower[1].att = 10 + Tower[1].lv;
	Tower[1].att_spd = 0.8f;
	Tower[1].price = 400 * Tower[1].lv;
	Tower[1].state = IDLE;
	Tower[1].x = 150;
	Tower[1].y = 350;
	Tower[1].rc = RectMakeCenter(Tower[1].x, Tower[1].y, 120, 120);




	return S_OK;
}

void tower::release()
{
}



void tower::TowerHpBar(float x, float y, int i)
{
	tagTowerprogressBar TowerHp;
	ZeroMemory(&TowerHp, sizeof(tagTowerprogressBar));
	TowerHp._TowerHp = new progressBar;
	TowerHp._TowerHp->init("PlayerprogressBarFront", "progressBarBack", Tower[1].img->getX(), Tower[1].img->getY(), 50, 10);


	x = Tower[1].img->getX();
	y = Tower[1].img->getY();
	TowerHp._TowerHp->setGauge(Tower[1].hp, Tower[1].maxhp);

	_ToweHP[i].push_back(TowerHp);
}
