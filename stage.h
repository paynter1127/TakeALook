#pragma once
#include "gameNode.h"
#include "character.h"
#include "stageInfo.h"
#include "tower.h"
#include "userSkillCombine.h"

//다이 이미지
struct tagDie
{
	image* img;
	int count;
	bool isDie;
	int x, y;
};

//체력바 구조체
struct tagProgressBar
{
	progressBar* hpBar;
};

class stage : public gameNode
{
public:// < 변수 선언 부 > =============================================================
	character* _character;
	stageInfo* _stageInfo;

	vector<vector<tagCharacter> > field_player;
	vector<vector<tagCharacter> > field_enemy;

	tagProgressBar init_hpBar;//체력바 초기화
	vector<vector<tagProgressBar> > field_player_hpBar;
	vector<vector<tagProgressBar> > field_enemy_hpBar;

	vector<vector<tagDie> > field_player_die;
	vector<vector<tagDie> > field_enemy_die;
	
	//다이 이미지
	tagDie hero_die;
	tagDie worrior_die;
	tagDie archer_die;
	tagDie magician_die;
	tagDie tower_die;
	tagDie castle_die;
	tagDie hero_enemy_die;
	tagDie worrior_enemy_die;
	tagDie archer_enemy_die;
	tagDie magician_enemy_die;
	tagDie tower_enemy_die;
	tagDie castle_enemy_die;

	int playerfood;
	int enemyfood;

	RECT line[3];   //라인 
	//썸네일
	bool isDrag[4];
	RECT sumNail[4]; //캐릭터 썸네일
	RECT sumNailSkill[3]; //스킬 썸네일

	//=========================

	userSKillCombine* _userSkill;

	RECT miniMap;


	//===================



	//스테이지상자
	RECT stage1RECT;

	//카메라 상자
	RECT camara_rc;
	RECT end;

	bool check;
	int count;
	int hcount;
	int bcount;
	int exline;

	bool isplay;
	int getgold;

public:// < 함수 선언 부 > =============================================================


	//카메라
	void camera();

	//소환함수
	void summon_hero();
	void summon_worrior();
	void summon_archer();
	void summon_magician();
	void summon_AI();
	void summon_tower_AI(int lineNum, int x, int y);
	//void summon_castle(int x, int y, int x2, int y2);
	void summon_castle();

	void die();

	//식량
	void food(int count);
	//적군 달리기
	void runEnemy(int lineNum);
	//플레이어 달리기
	void runPlayer(int lineNum);

	//체력바 생성
	void hpBar(int lineNum, bool isPlayer, int sort);
	//체력바 업데이트
	void updateHpBar();

	//충돌함수
	void bump(int lineNum);
	void bumpCastle(int lineNum);//1,2라인 캐슬 충돌)
	//플레이어 삭제
	void removeplayer(int lineNum);
	//적군삭제
	void removeEnemy(int lineNum);

	//사운드
	void sortSound_player(int lineNum, int i);
	void sortSound_enemy(int lineNum, int i);

	HRESULT init();
	void release();
	void update();
	void render();

	stage() {}
	~stage() {}
};

