#pragma once
#include "gameNode.h"
#include "bullet.h"


//적 매니저 상호참조를 위한 클래스 전방 선언
class enemyManager;

class player : public gameNode
{
private:
	image* _rocket;		//로켓(플레이어) 이미지
	//RECT _rcPlayer;
	missile* _missile;	//미사일 클래스
	bomb* _bomb;		//폭탄 클래스

	enemyManager* eeenemyManager; //동적할당하면 안된다

public:
	HRESULT init();
	void release();
	void update();
	void render();

	vector<tagBullet> _getMissile() { return _missile->getMissile(); }
	//missile* _getMissile() { return _missile; }
	void getRemoveMissile(int index) { return _missile->removeMissile(index); }
	RECT getRc() { return _rocket->boudingBox(); };

	player() {}
	~player() {}


	void setEm(enemyManager *em) { eeenemyManager = em; }
};

