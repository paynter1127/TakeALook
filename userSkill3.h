#pragma once
#include "gameNode.h"



class userSkill3 :
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


public:


	HRESULT init();
	void release();
	void update();
	void render();

	userSkill3() {}
	~userSkill3() {}
};


