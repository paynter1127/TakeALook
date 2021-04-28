#pragma once
#include "gameNode.h"


struct tagIcon2
{
	int x;
	int y;
	RECT icon;
	RECT Micon;
	int IconSize;
	float scale;
	bool Click;
	string ImageKey;
	string MimageKey;
	string BimageKey;
	string Name;
	int price;

	string Discription1;
	string Discription2;
	string Discription3;

};



class shop : public gameNode
{
public:// < ���� ���� �� > =============================================================

	RECT ShowUpgrade; //����->���׷��̵� ������ ���ư��� ���� ��Ʈ 


	RECT NON; //�浹Ȯ�ο� ��Ʈ


	RECT iconSizeSet;
	float iconSizeSet_X;
	int IconSize;
	int IconDistance;

	RECT ShopBG;	//���׷��̵� ��׶���
	RECT Setting;	//���׷��̵� �ڿ� ������ �������� ��Ʈ
	bool Scroll;	//��ũ���ؼ� ĳ���� ��Ʈ �������¿뵵
	long MouseMovingPoint; //��ũ���Ҷ� ���콺�� �����ϴ� ����

	int alpha;
	int BgAlpha;

	int Count;
	int index;
	int Kcount;
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	RECT BuyCheck;
	RECT Yes;
	RECT No;
	bool PopUp;

	int SoundCount;
	bool SoundCheck;
	//�ѤѤѤѤѤѤѤѵ�Ʈ����& ���׷��̵� ���äѤѤѤѤѤѤ�

	RECT Distruction;
	RECT ShowStat;
	RECT BuySkill;
	RECT Player_Gold;

	RECT Skill_getCount;

	int Count_BlackHole;
	int Count_Meteor;
	int Count_Heal;

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	tagIcon2 icon_BlackHole;
	tagIcon2 icon_Meteor;
	tagIcon2 icon_Heal;

	vector<tagIcon2> icon_Skill;
	vector<int>  Count_Skill;

public:// < �Լ� ���� �� > =============================================================






	HRESULT init();
	void release();
	void update();
	void render();

	void iconScroll();
	void getSkill();

	shop() {}
	~shop() {}
};

