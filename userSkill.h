#pragma once
#include "gameNode.h"




class userSkill : public gameNode
{
public:// < ���� ���� �� > =============================================================


	//=================================

	int Count; //��ų ������ ������ ī��Ʈ
	int index; //��ų ������ ������ �ε���


	int Ccount; //��ų ������ ������ ������ ī��Ʈ
	int Cindex; //��ų ������ ������ ������ �ε���
	float Cscale; //������ ũ�� ������ float


	POINT Meteor_Coordinates; //���׿� ��ġ ����

	POINT Meteor;
	RECT icon_Meteor;		 //�ϴ� ��ũ���� ���׿�
	RECT drag_icon_Meteor;	//�巡�׽� ���ܿ��� ������ 
	bool drag_Meteor; //������ �巡�� 
	bool Use_Meteor;  //��� ����

	int Meteor_Count; //���׿� �������� Ƚ��

	RECT Damage; //������ ���� �ִ� ��Ʈ

	//==========================



public:// < �Լ� ���� �� > =============================================================





	HRESULT init();
	void release();
	void update();
	void render();

	userSkill() {}
	~userSkill() {}
};

