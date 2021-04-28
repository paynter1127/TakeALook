#pragma once
#include "gameNode.h"
#include "progressBar.h"
//ĳ���� ����� �κ�(�Ʊ� 3��, ���� 3��, ����1�� ��)
enum state { RUN, ATTACK, DIE };
enum sort { WORRIOR, ARCHER, MAGICIAN, BOSS, TOWER, CASTLE };




//ĳ���� ����ü
struct tagCharacter
{
	int sort;

	//����
	int lv; //����
	int hp; //ü��
	int maxhp; //�ִ�ü��
	int att;  //���ݷ�
	float att_spd;  //����
	float run_spd; //�̼�
	int price;    //�������� 

	//��ũ����
	char str_name[128];
	char str_des[128];

	//�ൿ 
	int state;
	float x, y; //����
	RECT rc; //�浹 ��Ʈ
	image* img; //�̹���
	RECT rc_attRange; //���� ����
	bool fire;
	bool fire_motion;
	RECT rc_att;
	image* img_att;
	image* img_weapon;//����
	float angle; //ȸ�� ��
	bool isDown; //ȸ�� ����
	
	bool isHit;

	int frame_count;  //ĳ���Ͱ� �����̰ų� �ҋ� ���� ī��Ʈ
	float gravity; //�߷� ��


	float Mx; //�̴ϸʿ� �߰��Ѱ� 
	

	//��ų
	
};


class character : public gameNode
{
public:// < ���� ���� �� > =============================================================

	//ĳ���� ����(0�� �Ʊ� / 1�� ����)
	tagCharacter hero[2];
	tagCharacter worrior[2];
	tagCharacter archer[2];
	tagCharacter magician[2];
	
	//�ɽ�, Ÿ�� ĳ���� ����
	tagCharacter castle[2];
	tagCharacter tower[2];

	image* bgimage;

	//���� ������ ī��Ʈ
	int count;

public:// < �Լ� ���� �� > =============================================================

	HRESULT init();
	void release();
	
	character() {}
	~character() {}
};

