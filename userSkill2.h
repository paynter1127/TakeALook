#pragma once
#include "gameNode.h"


enum skillstate
{
	NOT = 1,
	PICK,
	EAT,
	EXIT,
	ING
};


class userSkill2 :
	public gameNode
{
public:
	int Count; //��ų ������ ������ ī��Ʈ
	int index; //��ų ������ ������ �ε���


	int Ccount; //��ų ������ ������ ������ ī��Ʈ
	int Cindex; //��ų ������ ������ ������ �ε���
	float Cscale; //������ ũ�� ������ float


	POINT Meteor_Coordinates; //���׿� ��ġ ����

	RECT icon_Meteor;		 //�ϴ� ��ũ���� ���׿�
	RECT drag_icon_Meteor;	//�巡�׽� ���ܿ��� ������ 
	bool drag_Meteor; //������ �巡�� 
	bool Use_Meteor;  //��� ����

	RECT Damage; //������ ���� �ִ� ��Ʈ

	RECT exit;
	skillstate now;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	userSkill2() {}
	~userSkill2() {}
};

