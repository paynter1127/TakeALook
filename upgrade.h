#pragma once
#include "gameNode.h"
#include "character.h"

#define MAXUPGRADE 10


struct tagUnitStat
{
	int Lv;
	int Hp;
	int att;
	int price;
	int priceUp;
};

struct tagIcon
{
	int x;
	int y;
	RECT icon;
	RECT Micon;
	int IconSize;
	float scale;
	bool Click;
	string ImageKey;
	string MImageKey;
	string Class;

	string Discrption1;
	string Discrption2;
	string Discrption3;

};


class upgrade : public gameNode
{
public:// < ���� ���� �� > =============================================================

	RECT ShowShop;


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
	//�ѤѤѤѤѤѤѤѵ�Ʈ����& ���׷��̵� ���äѤѤѤѤѤѤ�

	RECT Distruction;
	RECT ShowStat;
	RECT Upgrade;
	RECT Player_Gold;

	RECT UpgradeCheck;
	RECT Yes;
	RECT No;
	bool PopUp;

	RECT ShowLv;

	bool BuySound;
	//=====================================����=======================================

	bool ShowUnitUpgrade;
	RECT UnitUpgradeRc;

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�


	tagUnitStat WorriorStat;	//���� ���� �ö󰡴��� Ȯ���ϱ� ���켭 ������ ����ü
	tagUnitStat ArchorStat;
	tagUnitStat MageStat;
	tagUnitStat HeroStat;

	vector<tagUnitStat> Unit_Stat;

	tagUnitStat Worrior_Up;
	tagUnitStat Archor_Up;
	tagUnitStat Mage_Up;
	tagUnitStat Hero_Up;

	vector<tagUnitStat> Unit_Up;

	bool LoadData; //���� ������ ���� �ֵ� ������ �ҷ����� ���� bool����
				   //���������� ���Խ� ��ȯ (���� �̿ϼ� �׽�Ʈ��)
	int gold;	   //Playerinfo�� �� ��带 �ҷ�����, �����ϱ� ���� ����

	//�ѤѤѤѤѤѤѤѤѤѾ����ܤѤѤѤѤѤѤѤѤ� 
	tagIcon icon_Warrior;
	tagIcon icon_Archor;
	tagIcon icon_Mage;
	tagIcon icon_Hero;

	vector<tagIcon> icon_Class;// 0=���� , 1=�ü�, 2=������, 3=����


	//===================================�ǹ� ���׷��̵�===============================

	bool ShowObjectUpgrade;
	RECT ObjectUpgradeRc;

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	tagIcon icon_Cassle;
	tagIcon icon_Tower;

	vector<tagIcon> icon_Object;

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	tagUnitStat CassleStat;
	tagUnitStat TowerStat;

	tagUnitStat Cassle_Up;
	tagUnitStat Tower_Up;

	vector<tagUnitStat> Object_Stat;
	vector<tagUnitStat> Object_Up;


public:// < �Լ� ���� �� > =============================================================


	HRESULT init();
	void release();
	void update();
	void render();

	void iconScroll();
	void Upgrade_Unit(int Num);
	void Upgrade_Object(int Num);

	tagUnitStat Show_Unit_Stat(int Num, int Lv);
	tagUnitStat Show_Object_Stat(int Num, int Lv);

	upgrade() {}
	~upgrade() {}
};

