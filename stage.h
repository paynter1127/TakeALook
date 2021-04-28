#pragma once
#include "gameNode.h"
#include "character.h"
#include "stageInfo.h"
#include "tower.h"
#include "userSkillCombine.h"

//���� �̹���
struct tagDie
{
	image* img;
	int count;
	bool isDie;
	int x, y;
};

//ü�¹� ����ü
struct tagProgressBar
{
	progressBar* hpBar;
};

class stage : public gameNode
{
public:// < ���� ���� �� > =============================================================
	character* _character;
	stageInfo* _stageInfo;

	vector<vector<tagCharacter> > field_player;
	vector<vector<tagCharacter> > field_enemy;

	tagProgressBar init_hpBar;//ü�¹� �ʱ�ȭ
	vector<vector<tagProgressBar> > field_player_hpBar;
	vector<vector<tagProgressBar> > field_enemy_hpBar;

	vector<vector<tagDie> > field_player_die;
	vector<vector<tagDie> > field_enemy_die;
	
	//���� �̹���
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

	RECT line[3];   //���� 
	//�����
	bool isDrag[4];
	RECT sumNail[4]; //ĳ���� �����
	RECT sumNailSkill[3]; //��ų �����

	//=========================

	userSKillCombine* _userSkill;

	RECT miniMap;


	//===================



	//������������
	RECT stage1RECT;

	//ī�޶� ����
	RECT camara_rc;
	RECT end;

	bool check;
	int count;
	int hcount;
	int bcount;
	int exline;

	bool isplay;
	int getgold;

public:// < �Լ� ���� �� > =============================================================


	//ī�޶�
	void camera();

	//��ȯ�Լ�
	void summon_hero();
	void summon_worrior();
	void summon_archer();
	void summon_magician();
	void summon_AI();
	void summon_tower_AI(int lineNum, int x, int y);
	//void summon_castle(int x, int y, int x2, int y2);
	void summon_castle();

	void die();

	//�ķ�
	void food(int count);
	//���� �޸���
	void runEnemy(int lineNum);
	//�÷��̾� �޸���
	void runPlayer(int lineNum);

	//ü�¹� ����
	void hpBar(int lineNum, bool isPlayer, int sort);
	//ü�¹� ������Ʈ
	void updateHpBar();

	//�浹�Լ�
	void bump(int lineNum);
	void bumpCastle(int lineNum);//1,2���� ĳ�� �浹)
	//�÷��̾� ����
	void removeplayer(int lineNum);
	//��������
	void removeEnemy(int lineNum);

	//����
	void sortSound_player(int lineNum, int i);
	void sortSound_enemy(int lineNum, int i);

	HRESULT init();
	void release();
	void update();
	void render();

	stage() {}
	~stage() {}
};

