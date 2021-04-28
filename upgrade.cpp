#include "stdafx.h"
#include "upgrade.h"


HRESULT upgrade::init()
{



	if (icon_Class.size() > 0) icon_Class.clear();
	if (icon_Object.size() > 0) icon_Object.clear();

	//================================���׷��̵� �⺻ ����===============

	ShopBG = RectMake(0, 0, WINSIZEX, 450);
	Setting = RectMake(0, 200, WINSIZEX, 200);
	Scroll = false;

	IconSize = 200;
	iconSizeSet = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, IconSize * 1 / 4, IconSize * 1 / 4);
	iconSizeSet_X = WINSIZEX / 2;
	IconDistance = 500;

	Player_Gold = RectMake(WINSIZEX - 296, 7, 170, 36);

	MouseMovingPoint = 0;


	ShowUnitUpgrade = true;
	UnitUpgradeRc = RectMake(0, 80, 100, 40);

	ShowObjectUpgrade = false;
	ObjectUpgradeRc = RectMake(0, UnitUpgradeRc.bottom + 20, 100, 40);


	ShowLv = RectMake(100, 5, 160, 40);


	ShowShop = RectMake(WINSIZEX - 135, 60, 100, 40);


	alpha = 255;
	BgAlpha = 255;

	//=========================��Ʈ����&���׷��̵� ����==================

	Distruction = RectMake(0, 450, WINSIZEX, 150);
	ShowStat = RectMake(Distruction.right - 400, Distruction.top, 250, 150);
	Upgrade = RectMake(ShowStat.right, Distruction.top + 10, 100, 100);


	LoadData = false;
	gold = 0;

	UpgradeCheck = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 50, 300, 200);
	PopUp = false;
	Yes = RectMake(UpgradeCheck.left + 50, UpgradeCheck.bottom - 45, 80, 40);
	No = RectMake(UpgradeCheck.right - 120, UpgradeCheck.bottom - 45, 80, 40);


	//========================================================================================================
	//								��							��
	//========================================================================================================

	ZeroMemory(&Unit_Stat, sizeof(tagUnitStat));


	//===============���� ������ �ʱ�ȭ=====================

	icon_Warrior.x = WINSIZEX / 2;
	icon_Warrior.y = WINSIZEY / 2;
	icon_Warrior.IconSize = IconSize;
	icon_Warrior.icon = RectMakeCenter(icon_Warrior.x, icon_Warrior.y, icon_Warrior.IconSize, icon_Warrior.IconSize);
	icon_Warrior.Micon = RectMake(ShowLv.left, ShowLv.top, 40, 40);
	icon_Warrior.scale = 1.0f;
	icon_Warrior.Click = false;
	icon_Warrior.ImageKey = "Icon_Warrior";
	icon_Warrior.MImageKey = "Micon_Warrior";
	icon_Warrior.Class = "����";
	icon_Warrior.Discrption1 = "�ձ� ���� �Ҽ� ���� ����";
	icon_Warrior.Discrption2 = "������ ü���� �������";
	icon_Warrior.Discrption3 = "���������� �Ʊ��� ��ȣ�ϴ� ������ �Ѵ�.";

	icon_Class.push_back(icon_Warrior);

	WorriorStat.Lv = 1;
	WorriorStat.Hp = 14;
	WorriorStat.att = 4;
	WorriorStat.price = 100;
	WorriorStat.priceUp = 100;
	Unit_Stat.push_back(WorriorStat);


	//===============�ü� ������ �ʱ�ȭ=====================

	icon_Archor.x = icon_Warrior.x + IconDistance;
	icon_Archor.y = WINSIZEY / 2;
	icon_Archor.IconSize = IconSize;
	icon_Archor.icon = RectMakeCenter(icon_Archor.x, icon_Archor.y, icon_Archor.IconSize, icon_Archor.IconSize);
	icon_Archor.Micon = RectMake(ShowLv.left + 90, ShowLv.top, 40, 40);
	icon_Archor.scale = 1.0f;
	icon_Archor.ImageKey = "Icon_Archor";
	icon_Archor.MImageKey = "Micon_Archor";
	icon_Archor.Click = false;
	icon_Archor.Class = "�ü�";
	icon_Archor.Discrption1 = "�ձ� ���� �Ҽ� ���Ÿ� �ú�";
	icon_Archor.Discrption2 = "����� ����� ����������";
	icon_Archor.Discrption3 = "���� �ӵ��� �շ��ؼ� �Ʊ��� �������ش�.";
	icon_Class.push_back(icon_Archor);

	ArchorStat.Lv = 1;
	ArchorStat.Hp = 4;
	ArchorStat.att = 6;
	ArchorStat.price = 120;
	ArchorStat.priceUp = 120;
	Unit_Stat.push_back(ArchorStat);



	//===============������ ������ �ʱ�ȭ=====================

	icon_Mage.x = icon_Archor.x + IconDistance;
	icon_Mage.y = WINSIZEY / 2;
	icon_Mage.IconSize = IconSize;
	icon_Mage.icon = RectMakeCenter(icon_Mage.x, icon_Mage.y, icon_Mage.IconSize, icon_Mage.IconSize);
	icon_Mage.Micon = RectMake(ShowLv.left + 180, ShowLv.top, 40, 40);
	icon_Mage.scale = 1.0f;
	icon_Mage.ImageKey = "Icon_Mage";
	icon_Mage.MImageKey = "Micon_Mage";
	icon_Mage.Click = false;
	icon_Mage.Class = "������";
	icon_Mage.Discrption1 = "�ձ� ���� ��� �Ҽ� ���Ÿ� ������";
	icon_Mage.Discrption2 = "���� ���� �ɷ��� ���ϰ� ������";
	icon_Mage.Discrption3 = "������ ������ ���� �Ʊ��� ȭ���� ����Ѵ�.";
	icon_Class.push_back(icon_Mage);

	MageStat.Lv = 1;
	MageStat.Hp = 4;
	MageStat.att = 10;
	MageStat.price = 200;
	MageStat.priceUp = 200;
	Unit_Stat.push_back(MageStat);


	//===============������ ������ �ʱ�ȭ=====================

	icon_Hero.x = icon_Mage.x + IconDistance;
	icon_Hero.y = WINSIZEY / 2;
	icon_Hero.IconSize = IconSize;
	icon_Hero.icon = RectMakeCenter(icon_Hero.x, icon_Hero.y, icon_Hero.IconSize, icon_Hero.IconSize);
	icon_Hero.Micon = RectMake(ShowLv.left + 270, ShowLv.top, 40, 40);
	icon_Hero.scale = 1.0f;
	icon_Hero.ImageKey = "Icon_Hero";
	icon_Hero.MImageKey = "Micon_Hero";
	icon_Hero.Click = false;
	icon_Hero.Class = "����";
	icon_Hero.Discrption1 = "�ձ� ���� �屺";
	icon_Hero.Discrption2 = "���� �Ⱓ���� ���忡�� �׾ƿ� �Ƿ�����";
	icon_Hero.Discrption3 = "�Ʊ����� �¸��� ������ �������ش�.";
	icon_Class.push_back(icon_Hero);

	HeroStat.Lv = 1;
	HeroStat.Hp = 30;
	HeroStat.att = 7;
	HeroStat.price = 500;
	HeroStat.priceUp = 500;
	Unit_Stat.push_back(HeroStat);



	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	Worrior_Up.Lv = 1;
	Worrior_Up.Hp = 2;
	Worrior_Up.att = 1;

	Archor_Up.Lv = 1;
	Archor_Up.Hp = 2;
	Archor_Up.att = 1;

	Mage_Up.Lv = 1;
	Mage_Up.Hp = 1;
	Mage_Up.att = 2;

	Hero_Up.Lv = 1;
	Hero_Up.Hp = 3;
	Hero_Up.att = 2;

	Unit_Up.push_back(Worrior_Up);
	Unit_Up.push_back(Archor_Up);
	Unit_Up.push_back(Mage_Up);
	Unit_Up.push_back(Hero_Up);


	Cassle_Up.Lv = 1;
	Cassle_Up.Hp = 40;
	Cassle_Up.priceUp = 1000;

	Tower_Up.Lv = 1;
	Tower_Up.Hp = 40;
	Tower_Up.att = 1;
	Tower_Up.priceUp = 400;

	Object_Up.push_back(Cassle_Up);
	Object_Up.push_back(Tower_Up);

	//===================================================

	//========================================================================================================
	//								��			��			��
	//========================================================================================================


	//==============================================

	icon_Cassle.x = WINSIZEX / 2;
	icon_Cassle.y = WINSIZEY / 2;
	icon_Cassle.IconSize = IconSize;
	icon_Cassle.icon = RectMakeCenter(icon_Cassle.x, icon_Cassle.y, icon_Cassle.IconSize, icon_Cassle.IconSize);
	icon_Cassle.Micon = RectMake(ShowLv.left, ShowLv.top, 40, 40);
	icon_Cassle.scale = 1.0f;
	icon_Cassle.ImageKey = "Icon_Cassle";
	icon_Cassle.MImageKey = "Micon_Cassle";
	icon_Cassle.Click = false;
	icon_Cassle.Class = "��";
	icon_Cassle.Discrption1 = "�ձ� ����";
	icon_Cassle.Discrption2 = "�Ʊ��� ��������";
	icon_Cassle.Discrption3 = "��� �߿����� ����ϰ��ִ�.";
	icon_Object.push_back(icon_Cassle);

	CassleStat.Lv = 1;
	CassleStat.Hp = 400; //���� 40����
	CassleStat.att = 0;
	CassleStat.price = 1000; //���� 1000���� 
	CassleStat.priceUp = 1000;
	Object_Stat.push_back(CassleStat);


	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	icon_Tower.x = icon_Cassle.x + IconDistance;
	icon_Tower.y = WINSIZEY / 2;
	icon_Tower.IconSize = IconSize;
	icon_Tower.icon = RectMakeCenter(icon_Tower.x, icon_Tower.y, icon_Tower.IconSize, icon_Tower.IconSize);
	icon_Tower.Micon = RectMake(ShowLv.left + 90, ShowLv.top, 40, 40);
	icon_Tower.scale = 1.0f;
	icon_Tower.ImageKey = "Icon_Tower";
	icon_Tower.MImageKey = "Micon_Tower";
	icon_Tower.Click = false;
	icon_Tower.Class = "Ÿ��";
	icon_Tower.Discrption1 = "�ձ� ���Էθ� ��Ű�� �ִ� ����";
	icon_Tower.Discrption2 = "������ �����ϴ� ����� ����������";
	icon_Tower.Discrption3 = "�����Ÿ����� �ٰ��� ������ ó���Ѵ�.";
	icon_Object.push_back(icon_Tower);

	TowerStat.Lv = 1;
	TowerStat.Hp = 100; //���� 40����
	TowerStat.att = 10; //���� 1����
	TowerStat.price = 400; //���� 400����
	TowerStat.priceUp = 400;
	Object_Stat.push_back(TowerStat);


	BuySound = false;

	return S_OK;
}

void upgrade::release()
{
}

void upgrade::update()
{
	//������ ���̺�ε�


	//���콺�� Ŭ��
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		RECT NON;

		if (PtInRect(&UnitUpgradeRc, _ptMouse))
		{
			SOUNDMANAGER->play("��ư");
			ShowUnitUpgrade = true;
			ShowObjectUpgrade = false;
		}
		//���� ���׷��̵� ��� ���� 

		if (PtInRect(&ObjectUpgradeRc, _ptMouse))
		{
			SOUNDMANAGER->play("��ư");
			ShowUnitUpgrade = false;
			ShowObjectUpgrade = true;
		}
		//������Ʈ ���׷��̵� ��� ����

		if (PtInRect(&ShowShop, _ptMouse))
		{
			SCENEMANAGER->loadScene("Shop");
			SOUNDMANAGER->play("��ư");
		}
		//���׷��̵�->��  �� �̵� 

		if (PopUp == false)
		{
			if (PtInRect(&Setting, _ptMouse))
			{

				MouseMovingPoint = _ptMouse.x;
				Scroll = true;
			}
		}
		//��ũ�� ��� 

		for (int i = 0; i < icon_Class.size(); i++)
		{
			if (ShowUnitUpgrade == true && icon_Class[i].Click == true && Unit_Stat[i].Lv < 10)
			{
				if (PtInRect(&Upgrade, _ptMouse))
				{
					SOUNDMANAGER->play("��ư");
					PopUp = true;
				}
			}
		}
		//���� ���׷��̵� ����϶�, ���׷��̵� ��ư ������ �˾�â ����

		for (int i = 0; i < icon_Object.size(); i++)
		{
			if (ShowObjectUpgrade == true && icon_Object[i].Click == true && Object_Stat[i].Lv < 10)
			{
				if (PtInRect(&Upgrade, _ptMouse))
				{
					SOUNDMANAGER->play("��ư");
					PopUp = true;
				}
			}
		}
		//������Ʈ ���׷��̵� ����϶�, ���׷��̵� ��ư ������ �˾�â ����

		if (PopUp == true)
		{

			if (PtInRect(&Yes, _ptMouse))
			{
				if (ShowUnitUpgrade == true)
				{
					for (int i = 0; i < icon_Class.size(); i++)
					{
						if (icon_Class[i].Click == true)
						{
							if (playerInfo::getSingleton()->gold >= Unit_Stat[i].price)
							{
								playerInfo::getSingleton()->gold -= Unit_Stat[i].price;


								Upgrade_Unit(i); //���׷��̵� �Լ� 
								savePlayer();

								PopUp = false;	//�˾�â �ݱ�
								SOUNDMANAGER->play("Buy_Upgrade");	//����

								break;
							}
						}
					}
				}
				else if (ShowObjectUpgrade == true)
				{
					for (int i = 0; i < icon_Object.size(); i++)
					{
						if (icon_Object[i].Click == true && Object_Stat[i].Lv < 10)
						{
							if (playerInfo::getSingleton()->gold >= Object_Stat[i].price)
							{
								playerInfo::getSingleton()->gold -= Object_Stat[i].price;


								Upgrade_Object(i); //���׷��̵� �Լ� 
								savePlayer();

								PopUp = false;	//�˾�â �ݱ�
								SOUNDMANAGER->play("Buy_Upgrade");	//����

								break;
							}
						}
					}

				}

			}
			if (PtInRect(&No, _ptMouse))
			{
				SOUNDMANAGER->play("��ư");
				PopUp = false; //�˾�â �ݱ�
			}
		}
		//�˾�â���� ���׷��̵� Yes or No ��ȣ�ۿ� 

		if (PtInRect(&IMAGEMANAGER->findImage("Back")->boudingBox(), _ptMouse))
		{
			SCENEMANAGER->loadScene("lobby");
			SOUNDMANAGER->play("��ư");
		}
		//���׷��̵� �� -> �κ� �� 
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) Scroll = false;
	//���콺 L��ư ��� ��ũ�� ��� ����

	//if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	//{
	//	if (PopUp == true)
	//	{

	//		Upgrade_Unit(i);
	//		PopUp = false;
	//	}

	//}
	//�˾�â���� ���ͷ� ���׷��̵� 


	iconScroll(); //������ ��ũ�� �Լ� 


	if (ShowUnitUpgrade == true)
	{
		for (int i = 0; i < icon_Class.size(); i++)
		{
			if (IntersectRect(&NON, &icon_Class[i].icon, &iconSizeSet))
			{
				icon_Class[i].Click = true;
			}
			else icon_Class[i].Click = false;
		}
	}
	//���� ���׷��̵� ��Ͽ��� ��� ������ ��Ʈ�� �浹�� �ɷ�ġ �߰� ����� bool��

	if (ShowObjectUpgrade == true)
	{
		for (int i = 0; i < icon_Object.size(); i++)
		{
			if (IntersectRect(&NON, &icon_Object[i].icon, &iconSizeSet))
			{
				icon_Object[i].Click = true;
			}
			else icon_Object[i].Click = false;
		}
	}
	//������Ʈ ���׷��̵� ��Ͽ��� ��� ������ ��Ʈ�� �浹�� �ɷ�ġ �߰� ����� bool��


	alpha -= 4; //ȭ��ǥ ���İ� ����


	if (PopUp == true) BgAlpha = 100; //�˾�â ������ ��׶��� �̹��� ���İ� �����ֱ�
	else BgAlpha = 255;				  //�˾�â �ȶ����� ���� ������ 


}

void upgrade::render()
{
	//========================�⺻����=================================

	//Rectangle(getMemDC(), ShopBG);
	//Rectangle(getMemDC(), Setting);

	IMAGEMANAGER->alphaRender("Upgrade_BG", getMemDC(), ShopBG.left, ShopBG.top, BgAlpha);
	IMAGEMANAGER->alphaRender("���� ��ũ��", getMemDC(), Setting.left, Setting.top, 80);
	IMAGEMANAGER->alphaRender("�׽�Ʈ", getMemDC(), 0, 0, 150);
	IMAGEMANAGER->render("Back", getMemDC(), 4, 7);
	IMAGEMANAGER->render("goldbar", getMemDC(), Player_Gold.left, Player_Gold.top);

	//Rectangle(getMemDC(), UnitUpgradeRc);

	IMAGEMANAGER->alphaRender("Unit_Info", getMemDC(), UnitUpgradeRc.left - 3, UnitUpgradeRc.top - 4, BgAlpha);

	//	Rectangle(getMemDC(), ObjectUpgradeRc);

	IMAGEMANAGER->alphaRender("Object_Info", getMemDC(), ObjectUpgradeRc.left - 3, ObjectUpgradeRc.top - 4, BgAlpha);

	//Rectangle(getMemDC(), ShowShop);
	//IMAGEMANAGER->alphaRender("Shop_Load", getMemDC(), ShowShop.left - 23, ShowShop.top - 15, BgAlpha);
	IMAGEMANAGER->alphaRender("Upgrade_Load", getMemDC(), ShowShop.left - 23, ShowShop.top - 15, BgAlpha);
	//Rectangle(getMemDC(), Distruction);
	//Rectangle(getMemDC(), Upgrade);
	//Rectangle(getMemDC(), ShowStat);

	IMAGEMANAGER->render("Discription", getMemDC(), Distruction.left, Distruction.top - 40);



	//TextOut(getMemDC(), WINSIZEX / 2, 20, "���׷��̵�(������)", strlen("���׷��̵�(������)"));

	//=================================================================
	char CLASS[128] = {};

	//Rectangle(getMemDC(), ShowLv);



	if (ShowUnitUpgrade == true)
	{
		for (int i = 0; i < icon_Class.size(); i++)
		{
			//Rectangle(getMemDC(), icon_Class[i].icon);
			IMAGEMANAGER->alphaRender(icon_Class[i].ImageKey, getMemDC(), icon_Class[i].icon.left, icon_Class[i].icon.top, BgAlpha);
		}


		for (int i = 0; i < icon_Class.size(); i++)
		{
			//Rectangle(getMemDC(), icon_Class[i].Micon);
			IMAGEMANAGER->render(icon_Class[i].MImageKey, getMemDC(), icon_Class[i].Micon.left, icon_Class[i].Micon.top);
			textOutFont(getMemDC(), icon_Class[i].Micon.right + 10, icon_Class[i].Micon.top + 10, itoa(Unit_Stat[i].Lv, CLASS, 10), "Lv %s", 20, RGB(0, 200, 200));

		}

		for (int i = 0; i < icon_Class.size(); i++)
		{
			if (i == 0) Unit_Stat[i].Lv = playerInfo::getSingleton()->lv_worrior;
			else if (i == 1) Unit_Stat[i].Lv = playerInfo::getSingleton()->lv_archer;
			else if (i == 2) Unit_Stat[i].Lv = playerInfo::getSingleton()->lv_megician;
			else if (i == 3) Unit_Stat[i].Lv = playerInfo::getSingleton()->lv_hero;

			if (IntersectRect(&NON, &icon_Class[i].icon, &iconSizeSet))
			{

				textOutFont(getMemDC(), ShowStat.left + 30, ShowStat.top + 10, " ��  ��	: ", 20);	//Ŭ���� �̸�
				textOutFont(getMemDC(), ShowStat.left + 30, ShowStat.top + 50, " ü  ��	: ", 20);	//Ŭ���� �̸�
				textOutFont(getMemDC(), ShowStat.left + 30, ShowStat.top + 90, " ���ݷ�	: ", 20); 	//Ŭ���� �̸�


				textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 10, Show_Unit_Stat(i, Unit_Stat[i].Lv).Lv, 20); //����
				textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 50, Show_Unit_Stat(i, Unit_Stat[i].Lv).Hp, 20); //ü��
				textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 90, Show_Unit_Stat(i, Unit_Stat[i].Lv).att, 20); //���ݷ�


				IMAGEMANAGER->alphaRender("ȭ��ǥ", getMemDC(), ShowStat.left + 130, ShowStat.top + 10, alpha);
				IMAGEMANAGER->alphaRender("ȭ��ǥ", getMemDC(), ShowStat.left + 130, ShowStat.top + 50, alpha);
				IMAGEMANAGER->alphaRender("ȭ��ǥ", getMemDC(), ShowStat.left + 130, ShowStat.top + 90, alpha);

				if (Unit_Stat[i].Lv < MAXUPGRADE)
				{
					textOutFontNum(getMemDC(), ShowStat.right - 80, ShowStat.top + 10, Show_Unit_Stat(i, Unit_Stat[i].Lv).Lv + Unit_Up[i].Lv, 20);	// ���� ����	
					textOutFontNum(getMemDC(), ShowStat.right - 80, ShowStat.top + 50, Show_Unit_Stat(i, Unit_Stat[i].Lv).Hp + Unit_Up[i].Hp, 20);	// ���� ���� ü��
					textOutFontNum(getMemDC(), ShowStat.right - 80, ShowStat.top + 90, Show_Unit_Stat(i, Unit_Stat[i].Lv).att + Unit_Up[i].att, 20);	// ���� ���� ���ݷ�


					textOutFont(getMemDC(), ShowStat.right - 50, ShowStat.top + 10, itoa(Unit_Up[i].Lv, CLASS, 10), "[+%s]", 20);	//���� ����ġ
					textOutFont(getMemDC(), ShowStat.right - 50, ShowStat.top + 50, itoa(Unit_Up[i].Hp, CLASS, 10), "[+%s]", 20);	//ü�� ����ġ
					textOutFont(getMemDC(), ShowStat.right - 50, ShowStat.top + 90, itoa(Unit_Up[i].att, CLASS, 10), "[+%s]", 20);	//���ݷ� ����ġ
				}

				else
				{
					textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 10, "MAX", 20);	//���� MAX 
					textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 50, "MAX", 20);	//ü�� MAX
					textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 90, "MAX", 20);	//���ݷ� MAX
				}
			}
		}
		for (int i = 0; i < icon_Class.size(); i++)
		{

			if (IntersectRect(&NON, &icon_Class[i].icon, &iconSizeSet))
			{
				if (Unit_Stat[i].Lv < MAXUPGRADE)
				{


					IMAGEMANAGER->render("Sign", getMemDC(), Upgrade.left - 5, Upgrade.top - 5); //���� ��ư �̹��� 
					IMAGEMANAGER->render("Price", getMemDC(), Upgrade.left - 15, Upgrade.bottom); // �ʿ� �䱸 ��� â �̹���
					IMAGEMANAGER->render("Gold", getMemDC(), Upgrade.left + 5, Upgrade.bottom + 3); //  ��� �̹��� 
					textOutFontNum(getMemDC(), Upgrade.left + 30, Upgrade.bottom + 5, Show_Unit_Stat(i, Unit_Stat[i].Lv).price, 20, RGB(200, 200, 100)); //�䱸 ��� 
				}


				textOutFont(getMemDC(), Distruction.left + 220, Distruction.top, icon_Class[i].Class.c_str(), 20); //���� Ŭ���� ��
				textOutFont(getMemDC(), Distruction.left + 130, Distruction.top + 50, icon_Class[i].Discrption1.c_str(), 20);
				textOutFont(getMemDC(), Distruction.left + 130, Distruction.top + 70, icon_Class[i].Discrption2.c_str(), 20);
				textOutFont(getMemDC(), Distruction.left + 130, Distruction.top + 90, icon_Class[i].Discrption3.c_str(), 20);


			}
		}


	}

	if (ShowObjectUpgrade == true)
	{
		for (int i = 0; i < icon_Object.size(); i++)
		{
			//Rectangle(getMemDC(), icon_Object[i].icon);
			IMAGEMANAGER->alphaRender(icon_Object[i].ImageKey, getMemDC(), icon_Object[i].icon.left, icon_Object[i].icon.top, BgAlpha);
			IMAGEMANAGER->render(icon_Object[i].MImageKey, getMemDC(), icon_Object[i].Micon.left, icon_Object[i].Micon.top);
			textOutFont(getMemDC(), icon_Object[i].Micon.right + 10, icon_Object[i].Micon.top + 10, itoa(Object_Stat[i].Lv, CLASS, 10), "Lv %s", 20, RGB(0, 200, 200));

		}

		char OBJECT[128] = {};

		for (int i = 0; i < icon_Object.size(); i++)
		{
			if (i == 0) Object_Stat[i].Lv = playerInfo::getSingleton()->lv_castle;
			if (i == 1) Object_Stat[i].Lv = playerInfo::getSingleton()->lv_tower;

			if (IntersectRect(&NON, &icon_Object[i].icon, &iconSizeSet))
			{

				textOutFont(getMemDC(), Distruction.left + 220, Distruction.top + 10, icon_Object[i].Class.c_str(), 20);
				textOutFont(getMemDC(), Distruction.left + 130, Distruction.top + 50, icon_Object[i].Discrption1.c_str(), 20);
				textOutFont(getMemDC(), Distruction.left + 130, Distruction.top + 70, icon_Object[i].Discrption2.c_str(), 20);
				textOutFont(getMemDC(), Distruction.left + 130, Distruction.top + 90, icon_Object[i].Discrption3.c_str(), 20);


				if (i == 0)
				{

					textOutFont(getMemDC(), ShowStat.left + 25, ShowStat.top + 30, " ��  �� : ", 20);
					textOutFont(getMemDC(), ShowStat.left + 25, ShowStat.top + 90, " ü  �� : ", 20);

					textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 30, Show_Object_Stat(i, Object_Stat[i].Lv).Lv, 20);
					textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 90, Show_Object_Stat(i, Object_Stat[i].Lv).Hp, 20);


					IMAGEMANAGER->alphaRender("ȭ��ǥ", getMemDC(), ShowStat.left + 130, ShowStat.top + 30, alpha);
					IMAGEMANAGER->alphaRender("ȭ��ǥ", getMemDC(), ShowStat.left + 130, ShowStat.top + 90, alpha);

				}
				else
				{

					textOutFont(getMemDC(), ShowStat.left + 25, ShowStat.top + 10, " ��  ��	: ", 20);	//Ŭ���� �̸�
					textOutFont(getMemDC(), ShowStat.left + 25, ShowStat.top + 50, " ü  ��	: ", 20);	//Ŭ���� �̸�
					textOutFont(getMemDC(), ShowStat.left + 25, ShowStat.top + 90, " ���ݷ�	: ", 20); 	//Ŭ���� �̸�


					textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 10, Show_Object_Stat(i, Object_Stat[i].Lv).Lv, 20);
					textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 50, Show_Object_Stat(i, Object_Stat[i].Lv).Hp, 20);
					textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 90, Show_Object_Stat(i, Object_Stat[i].Lv).att, 20); //���ݷ�


					IMAGEMANAGER->alphaRender("ȭ��ǥ", getMemDC(), ShowStat.left + 130, ShowStat.top + 10, alpha);
					IMAGEMANAGER->alphaRender("ȭ��ǥ", getMemDC(), ShowStat.left + 130, ShowStat.top + 50, alpha);
					IMAGEMANAGER->alphaRender("ȭ��ǥ", getMemDC(), ShowStat.left + 130, ShowStat.top + 90, alpha);
				}


				if (i == 0)
				{
					if (Object_Stat[i].Lv < MAXUPGRADE)
					{
						textOutFontNum(getMemDC(), ShowStat.right - 85, ShowStat.top + 30, Show_Object_Stat(i, Object_Stat[i].Lv).Lv + Object_Up[i].Lv, 20);
						textOutFontNum(getMemDC(), ShowStat.right - 90, ShowStat.top + 90, Show_Object_Stat(i, Object_Stat[i].Lv).Hp + Object_Up[i].Hp, 20);

						textOutFont(getMemDC(), ShowStat.right - 45, ShowStat.top + 30, itoa(Object_Up[i].Lv, CLASS, 10), "[+%s]", 20);
						textOutFont(getMemDC(), ShowStat.right - 50, ShowStat.top + 90, itoa(Object_Up[i].Hp, CLASS, 10), "[+%s]", 20);
					}
					else
					{
						textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 30, "MAX", 20);
						textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 90, "MAX", 20);
					}
				}
				else
				{
					if (Object_Stat[i].Lv < MAXUPGRADE)
					{
						textOutFontNum(getMemDC(), ShowStat.right - 85, ShowStat.top + 10, Show_Object_Stat(i, Object_Stat[i].Lv).Lv + Object_Up[i].Lv, 20);
						textOutFontNum(getMemDC(), ShowStat.right - 85, ShowStat.top + 50, Show_Object_Stat(i, Object_Stat[i].Lv).Hp + Object_Up[i].Hp, 20);
						textOutFontNum(getMemDC(), ShowStat.right - 85, ShowStat.top + 90, Show_Object_Stat(i, Object_Stat[i].Lv).att + Object_Up[i].att, 20);

						textOutFont(getMemDC(), ShowStat.right - 45, ShowStat.top + 10, itoa(Object_Up[i].Lv, CLASS, 10), "[+%s]", 20);
						textOutFont(getMemDC(), ShowStat.right - 50, ShowStat.top + 50, itoa(Object_Up[i].Hp, CLASS, 10), "[+%s]", 20);
						textOutFont(getMemDC(), ShowStat.right - 45, ShowStat.top + 90, itoa(Object_Up[i].att, CLASS, 10), "[+%s]", 20);

					}

					else
					{
						textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 10, "MAX", 20);
						textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 50, "MAX", 20);
						textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 90, "MAX", 20);

					}

				}

				if (Object_Stat[i].Lv < MAXUPGRADE)
				{
					IMAGEMANAGER->render("Sign", getMemDC(), Upgrade.left - 5, Upgrade.top - 5); //���� ��ư �̹��� 
					IMAGEMANAGER->render("Price", getMemDC(), Upgrade.left - 15, Upgrade.bottom); // �ʿ� �䱸 ��� â �̹���
					IMAGEMANAGER->render("Gold", getMemDC(), Upgrade.left + 5, Upgrade.bottom + 3); //  ��� �̹��� 
					textOutFontNum(getMemDC(), Upgrade.left + 30, Upgrade.bottom + 5, Show_Object_Stat(i, Object_Stat[i].Lv).price, 20, RGB(200, 200, 100)); //�䱸 ��� 

				}


			}
		}
	}

	//Rectangle(getMemDC(), iconSizeSet);


	if (PopUp == true)
	{
		//Rectangle(getMemDC(), UpgradeCheck);
		//Rectangle(getMemDC(), Yes);
		//Rectangle(getMemDC(), No);
		IMAGEMANAGER->render("Pop_Up", getMemDC(), UpgradeCheck.left, UpgradeCheck.top);
		IMAGEMANAGER->render("Yes", getMemDC(), Yes.left - 3, Yes.top);
		IMAGEMANAGER->render("No", getMemDC(), No.left - 3, No.top);
		textOutFont(getMemDC(), UpgradeCheck.left + 30, UpgradeCheck.top + 50, "���׷��̵� �Ͻðڽ��ϱ�?", 25, RGB(255, 255, 0));
	}

	loadPlayer();

	imagescaleNum("����2", getMemDC(), WINSIZEX - 170, 14, playerInfo::getSingleton()->gold, 14, 0.5);

}

void upgrade::iconScroll()
{
	if (Scroll == true)
	{
		if (ShowUnitUpgrade == true)
		{

			for (int i = 0; i < icon_Class.size(); i++) icon_Class[i].x -= (_ptMouse.x - MouseMovingPoint) / 8;

			for (int i = 0; i < icon_Class.size(); i++)
			{
				if (icon_Class[i].x > WINSIZEX * 51 / 100)
				{
					if (i == 0) icon_Class[i].x = WINSIZEX * 51 / 100;
					else icon_Class[i].x = icon_Class[i - 1].x + IconDistance;
				}
			}

			for (int i = icon_Class.size() - 1; i > -1; i--)
			{
				if (i == 3 && icon_Class[i].x < WINSIZEX * 49 / 100)
				{
					icon_Class[i].x = WINSIZEX * 49 / 100;
				}
				if (i == 2) icon_Class[i].x = icon_Class[i + 1].x - IconDistance;
				if (i == 1) icon_Class[i].x = icon_Class[i + 1].x - IconDistance;
				if (i == 0) icon_Class[i].x = icon_Class[i + 1].x - IconDistance;
			}


			for (int i = 0; i < icon_Class.size(); i++) icon_Class[i].icon = RectMakeCenter(icon_Class[i].x, icon_Class[i].y, icon_Class[i].IconSize, icon_Class[i].IconSize);
		}

		if (ShowObjectUpgrade == true)
		{
			for (int i = 0; i < icon_Object.size(); i++) icon_Object[i].x -= (_ptMouse.x - MouseMovingPoint) / 8;

			for (int i = 0; i < icon_Object.size(); i++)
			{
				if (icon_Object[i].x > WINSIZEX * 51 / 100)
				{
					if (i == 0) icon_Object[i].x = WINSIZEX * 51 / 100;
					else icon_Object[i].x = icon_Object[i - 1].x + IconDistance;
				}
			}

			for (int i = icon_Object.size() - 1; i > -1; i--)
			{
				if (i == 1 && icon_Object[i].x < WINSIZEX * 49 / 100) icon_Object[i].x = WINSIZEX * 49 / 100;
				if (i == 0) icon_Object[i].x = icon_Object[i + 1].x - IconDistance;
			}


			for (int i = 0; i < icon_Object.size(); i++) icon_Object[i].icon = RectMakeCenter(icon_Object[i].x, icon_Object[i].y, icon_Object[i].IconSize, icon_Object[i].IconSize);
		}


	}

}

void upgrade::Upgrade_Unit(int Num)
{


	Unit_Stat[Num].Lv = Unit_Stat[Num].Lv + Unit_Up[Num].Lv;
	Unit_Stat[Num].Hp = Unit_Stat[Num].Hp + Unit_Up[Num].Hp;
	Unit_Stat[Num].att = Unit_Stat[Num].att + Unit_Up[Num].att;

	Unit_Stat[Num].price = Unit_Stat[Num].price + Unit_Stat[Num].priceUp;

	if (Num == 0) playerInfo::getSingleton()->lv_worrior++;
	if (Num == 1) playerInfo::getSingleton()->lv_archer++;
	if (Num == 2) playerInfo::getSingleton()->lv_megician++;
	if (Num == 3) playerInfo::getSingleton()->lv_hero++;


}

void upgrade::Upgrade_Object(int Num)
{




	Object_Stat[Num].Lv = Object_Stat[Num].Lv + Object_Up[Num].Lv;
	Object_Stat[Num].Hp = Object_Stat[Num].Hp + Object_Up[Num].Hp;
	Object_Stat[Num].att = Object_Stat[Num].att + Object_Up[Num].att;

	Object_Stat[Num].price += Object_Up[Num].priceUp;

	if (Num == 0) playerInfo::getSingleton()->lv_castle++;
	if (Num == 1) playerInfo::getSingleton()->lv_tower++;
}

tagUnitStat upgrade::Show_Unit_Stat(int Num, int Lv)
{
	tagUnitStat a;


	if (Num == 0)
	{
		a.Lv = Lv;
		a.Hp = 14 + 2 * Lv;
		a.att = 4 + Lv;
		a.price = 100 * Lv;
	}
	if (Num == 1)
	{
		a.Lv = Lv;
		a.Hp = 4 + 2 * Lv;
		a.att = 6 + Lv;
		a.price = 120 * Lv;
	}
	if (Num == 2)
	{
		a.Lv = Lv;
		a.Hp = 4 + Lv;
		a.att = 10 + 2 * Lv;
		a.price = 200 * Lv;
	}
	if (Num == 3)
	{
		a.Lv = Lv;
		a.Hp = 30 + 2 * Lv;
		a.att = 4 + 2 * Lv;
		a.price = 500 * Lv;
	}


	return a;
}

tagUnitStat upgrade::Show_Object_Stat(int Num, int Lv)
{
	tagUnitStat a;


	if (Num == 0)
	{
		a.Lv = Lv;
		a.Hp = 400 + 40 * (Lv - 1);
		a.att = 0;
		a.price = 1000 * Lv;
	}
	if (Num == 1)
	{
		a.Lv = Lv;
		a.Hp = 100 + 40 * Lv;
		a.att = 10 + Lv;
		a.price = 400 * Lv;
	}



	return a;
}




