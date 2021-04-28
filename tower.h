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
	//����
	int lv; //����
	int hp; //ü��

	int maxhp; //�ִ�ü��

	int att;  //���ݷ�
	float att_spd;  //����
	
	int price;    //�������� 

	//��ũ����
	char str_name[128];
	char str_des[128];

	//�ൿ 
	int state;

	float x, y; //����

	RECT rc; //�浹 ��Ʈ

	image* img; //�̹���



	int frame_count;  //ĳ���Ͱ� �����̰ų� �ҋ� ���� ī��Ʈ



};

class tower : public gameNode
{
public:// < ���� ���� �� > =============================================================

	tagTower Tower[2];
	vector<tagTower> field_Tower[3];
	vector<tagTower> field_enemyTower[3];
	vector<tagTowerprogressBar>_ToweHP[3];//��Ÿ�� ü�¹� ���������ֱ�


public:// < �Լ� ���� �� > =============================================================





	HRESULT init();
	void release();
	
	//�÷��̾� ü�¹�
	void TowerHpBar(float x, float y, int i);
	tower() {}
	~tower() {}
};

