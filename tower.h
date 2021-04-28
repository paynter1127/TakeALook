#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum Towerstate { IDLE, TowerATTACK, TowerDIE };
struct tagTowerprogressBar
{
	progressBar* _TowerHp;
	image* _HPimage;

};

struct tagTower
{
	//스텟
	int lv; //레벨
	int hp; //체력

	int maxhp; //최대체력

	int att;  //공격력
	float att_spd;  //공속
	
	int price;    //상점가격 

	//디스크립션
	char str_name[128];
	char str_des[128];

	//행동 
	int state;

	float x, y; //중점

	RECT rc; //충돌 렉트

	image* img; //이미지



	int frame_count;  //캐릭터가 움직이거나 할떄 돌릴 카운트



};

class tower : public gameNode
{
public:// < 변수 선언 부 > =============================================================

	tagTower Tower[2];
	vector<tagTower> field_Tower[3];
	vector<tagTower> field_enemyTower[3];
	vector<tagTowerprogressBar>_ToweHP[3];//적타워 체력바 라인정해주기


public:// < 함수 선언 부 > =============================================================





	HRESULT init();
	void release();
	
	//플레이어 체력바
	void TowerHpBar(float x, float y, int i);
	tower() {}
	~tower() {}
};

