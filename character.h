#pragma once
#include "gameNode.h"
#include "progressBar.h"
//캐릭터 만드는 부분(아군 3종, 적군 3종, 영웅1종 씩)
enum state { RUN, ATTACK, DIE };
enum sort { WORRIOR, ARCHER, MAGICIAN, BOSS, TOWER, CASTLE };




//캐릭터 구조체
struct tagCharacter
{
	int sort;

	//스텟
	int lv; //레벨
	int hp; //체력
	int maxhp; //최대체력
	int att;  //공격력
	float att_spd;  //공속
	float run_spd; //이속
	int price;    //상점가격 

	//디스크립션
	char str_name[128];
	char str_des[128];

	//행동 
	int state;
	float x, y; //중점
	RECT rc; //충돌 렉트
	image* img; //이미지
	RECT rc_attRange; //공격 범위
	bool fire;
	bool fire_motion;
	RECT rc_att;
	image* img_att;
	image* img_weapon;//무기
	float angle; //회전 각
	bool isDown; //회전 방향
	
	bool isHit;

	int frame_count;  //캐릭터가 움직이거나 할떄 돌릴 카운트
	float gravity; //중력 값


	float Mx; //미니맵용 추가한거 
	

	//스킬
	
};


class character : public gameNode
{
public:// < 변수 선언 부 > =============================================================

	//캐릭터 선언(0은 아군 / 1은 적군)
	tagCharacter hero[2];
	tagCharacter worrior[2];
	tagCharacter archer[2];
	tagCharacter magician[2];
	
	//케슬, 타워 캐릭터 선언
	tagCharacter castle[2];
	tagCharacter tower[2];

	image* bgimage;

	//월드 프레임 카운트
	int count;

public:// < 함수 선언 부 > =============================================================

	HRESULT init();
	void release();
	
	character() {}
	~character() {}
};

