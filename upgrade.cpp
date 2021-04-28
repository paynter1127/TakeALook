#include "stdafx.h"
#include "upgrade.h"


HRESULT upgrade::init()
{



	if (icon_Class.size() > 0) icon_Class.clear();
	if (icon_Object.size() > 0) icon_Object.clear();

	//================================업그레이드 기본 세팅===============

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

	//=========================디스트럭션&업그레이드 선택==================

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
	//								유							닛
	//========================================================================================================

	ZeroMemory(&Unit_Stat, sizeof(tagUnitStat));


	//===============전사 아이콘 초기화=====================

	icon_Warrior.x = WINSIZEX / 2;
	icon_Warrior.y = WINSIZEY / 2;
	icon_Warrior.IconSize = IconSize;
	icon_Warrior.icon = RectMakeCenter(icon_Warrior.x, icon_Warrior.y, icon_Warrior.IconSize, icon_Warrior.IconSize);
	icon_Warrior.Micon = RectMake(ShowLv.left, ShowLv.top, 40, 40);
	icon_Warrior.scale = 1.0f;
	icon_Warrior.Click = false;
	icon_Warrior.ImageKey = "Icon_Warrior";
	icon_Warrior.MImageKey = "Micon_Warrior";
	icon_Warrior.Class = "전사";
	icon_Warrior.Discrption1 = "왕국 기사단 소속 근접 보병";
	icon_Warrior.Discrption2 = "강인한 체력을 기반으로";
	icon_Warrior.Discrption3 = "최전선에서 아군을 수호하는 역할을 한다.";

	icon_Class.push_back(icon_Warrior);

	WorriorStat.Lv = 1;
	WorriorStat.Hp = 14;
	WorriorStat.att = 4;
	WorriorStat.price = 100;
	WorriorStat.priceUp = 100;
	Unit_Stat.push_back(WorriorStat);


	//===============궁수 아이콘 초기화=====================

	icon_Archor.x = icon_Warrior.x + IconDistance;
	icon_Archor.y = WINSIZEY / 2;
	icon_Archor.IconSize = IconSize;
	icon_Archor.icon = RectMakeCenter(icon_Archor.x, icon_Archor.y, icon_Archor.IconSize, icon_Archor.IconSize);
	icon_Archor.Micon = RectMake(ShowLv.left + 90, ShowLv.top, 40, 40);
	icon_Archor.scale = 1.0f;
	icon_Archor.ImageKey = "Icon_Archor";
	icon_Archor.MImageKey = "Micon_Archor";
	icon_Archor.Click = false;
	icon_Archor.Class = "궁수";
	icon_Archor.Discrption1 = "왕국 기사단 소속 원거리 궁병";
	icon_Archor.Discrption2 = "재빠른 몸놀림을 갖고있으며";
	icon_Archor.Discrption3 = "빠른 속도로 합류해서 아군을 지원해준다.";
	icon_Class.push_back(icon_Archor);

	ArchorStat.Lv = 1;
	ArchorStat.Hp = 4;
	ArchorStat.att = 6;
	ArchorStat.price = 120;
	ArchorStat.priceUp = 120;
	Unit_Stat.push_back(ArchorStat);



	//===============마법사 아이콘 초기화=====================

	icon_Mage.x = icon_Archor.x + IconDistance;
	icon_Mage.y = WINSIZEY / 2;
	icon_Mage.IconSize = IconSize;
	icon_Mage.icon = RectMakeCenter(icon_Mage.x, icon_Mage.y, icon_Mage.IconSize, icon_Mage.IconSize);
	icon_Mage.Micon = RectMake(ShowLv.left + 180, ShowLv.top, 40, 40);
	icon_Mage.scale = 1.0f;
	icon_Mage.ImageKey = "Icon_Mage";
	icon_Mage.MImageKey = "Micon_Mage";
	icon_Mage.Click = false;
	icon_Mage.Class = "마법사";
	icon_Mage.Discrption1 = "왕국 마법 길드 소속 원거리 마법사";
	icon_Mage.Discrption2 = "고도의 마법 능력을 지니고 있으며";
	icon_Mage.Discrption3 = "강력한 마법을 통해 아군의 화력을 담당한다.";
	icon_Class.push_back(icon_Mage);

	MageStat.Lv = 1;
	MageStat.Hp = 4;
	MageStat.att = 10;
	MageStat.price = 200;
	MageStat.priceUp = 200;
	Unit_Stat.push_back(MageStat);


	//===============마법사 아이콘 초기화=====================

	icon_Hero.x = icon_Mage.x + IconDistance;
	icon_Hero.y = WINSIZEY / 2;
	icon_Hero.IconSize = IconSize;
	icon_Hero.icon = RectMakeCenter(icon_Hero.x, icon_Hero.y, icon_Hero.IconSize, icon_Hero.IconSize);
	icon_Hero.Micon = RectMake(ShowLv.left + 270, ShowLv.top, 40, 40);
	icon_Hero.scale = 1.0f;
	icon_Hero.ImageKey = "Icon_Hero";
	icon_Hero.MImageKey = "Micon_Hero";
	icon_Hero.Click = false;
	icon_Hero.Class = "영웅";
	icon_Hero.Discrption1 = "왕국 기사단 장군";
	icon_Hero.Discrption2 = "오랜 기간동안 전장에서 쌓아온 실력으로";
	icon_Hero.Discrption3 = "아군에게 승리의 발판을 마련해준다.";
	icon_Class.push_back(icon_Hero);

	HeroStat.Lv = 1;
	HeroStat.Hp = 30;
	HeroStat.att = 7;
	HeroStat.price = 500;
	HeroStat.priceUp = 500;
	Unit_Stat.push_back(HeroStat);



	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

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
	//								구			조			물
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
	icon_Cassle.Class = "성";
	icon_Cassle.Discrption1 = "왕국 본진";
	icon_Cassle.Discrption2 = "아군의 본진으로";
	icon_Cassle.Discrption3 = "모든 중요기능을 담당하고있다.";
	icon_Object.push_back(icon_Cassle);

	CassleStat.Lv = 1;
	CassleStat.Hp = 400; //업당 40증가
	CassleStat.att = 0;
	CassleStat.price = 1000; //업당 1000증가 
	CassleStat.priceUp = 1000;
	Object_Stat.push_back(CassleStat);


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	icon_Tower.x = icon_Cassle.x + IconDistance;
	icon_Tower.y = WINSIZEY / 2;
	icon_Tower.IconSize = IconSize;
	icon_Tower.icon = RectMakeCenter(icon_Tower.x, icon_Tower.y, icon_Tower.IconSize, icon_Tower.IconSize);
	icon_Tower.Micon = RectMake(ShowLv.left + 90, ShowLv.top, 40, 40);
	icon_Tower.scale = 1.0f;
	icon_Tower.ImageKey = "Icon_Tower";
	icon_Tower.MImageKey = "Micon_Tower";
	icon_Tower.Click = false;
	icon_Tower.Class = "타워";
	icon_Tower.Discrption1 = "왕국 진입로를 지키고 있는 망루";
	icon_Tower.Discrption2 = "성으로 진입하는 길목을 막고있으며";
	icon_Tower.Discrption3 = "사정거리내에 다가온 적들을 처리한다.";
	icon_Object.push_back(icon_Tower);

	TowerStat.Lv = 1;
	TowerStat.Hp = 100; //업당 40증가
	TowerStat.att = 10; //업당 1증가
	TowerStat.price = 400; //업당 400증가
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
	//데이터 세이브로드


	//마우스로 클릭
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		RECT NON;

		if (PtInRect(&UnitUpgradeRc, _ptMouse))
		{
			SOUNDMANAGER->play("버튼");
			ShowUnitUpgrade = true;
			ShowObjectUpgrade = false;
		}
		//유닛 업그레이드 목록 띄우기 

		if (PtInRect(&ObjectUpgradeRc, _ptMouse))
		{
			SOUNDMANAGER->play("버튼");
			ShowUnitUpgrade = false;
			ShowObjectUpgrade = true;
		}
		//오브젝트 업그레이드 목록 띄우기

		if (PtInRect(&ShowShop, _ptMouse))
		{
			SCENEMANAGER->loadScene("Shop");
			SOUNDMANAGER->play("버튼");
		}
		//업그레이드->샵  씬 이동 

		if (PopUp == false)
		{
			if (PtInRect(&Setting, _ptMouse))
			{

				MouseMovingPoint = _ptMouse.x;
				Scroll = true;
			}
		}
		//스크롤 기능 

		for (int i = 0; i < icon_Class.size(); i++)
		{
			if (ShowUnitUpgrade == true && icon_Class[i].Click == true && Unit_Stat[i].Lv < 10)
			{
				if (PtInRect(&Upgrade, _ptMouse))
				{
					SOUNDMANAGER->play("버튼");
					PopUp = true;
				}
			}
		}
		//유닛 업그레이드 목록일때, 업그레이드 버튼 누를시 팝업창 띄우기

		for (int i = 0; i < icon_Object.size(); i++)
		{
			if (ShowObjectUpgrade == true && icon_Object[i].Click == true && Object_Stat[i].Lv < 10)
			{
				if (PtInRect(&Upgrade, _ptMouse))
				{
					SOUNDMANAGER->play("버튼");
					PopUp = true;
				}
			}
		}
		//오브젝트 업그레이드 목록일때, 업그레이드 버튼 누를시 팝업창 띄우기

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


								Upgrade_Unit(i); //업그레이드 함수 
								savePlayer();

								PopUp = false;	//팝업창 닫기
								SOUNDMANAGER->play("Buy_Upgrade");	//사운드

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


								Upgrade_Object(i); //업그레이드 함수 
								savePlayer();

								PopUp = false;	//팝업창 닫기
								SOUNDMANAGER->play("Buy_Upgrade");	//사운드

								break;
							}
						}
					}

				}

			}
			if (PtInRect(&No, _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				PopUp = false; //팝업창 닫기
			}
		}
		//팝업창에서 업그레이드 Yes or No 상호작용 

		if (PtInRect(&IMAGEMANAGER->findImage("Back")->boudingBox(), _ptMouse))
		{
			SCENEMANAGER->loadScene("lobby");
			SOUNDMANAGER->play("버튼");
		}
		//업그레이드 씬 -> 로비 씬 
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) Scroll = false;
	//마우스 L버튼 뗴면 스크롤 기능 종료

	//if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	//{
	//	if (PopUp == true)
	//	{

	//		Upgrade_Unit(i);
	//		PopUp = false;
	//	}

	//}
	//팝업창에서 엔터로 업그레이드 


	iconScroll(); //아이콘 스크롤 함수 


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
	//유닛 업그레이드 목록에서 가운데 가상의 렉트랑 충돌시 능력치 뜨게 만드는 bool값

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
	//오브젝트 업그레이드 목록에서 가운데 가상의 렉트랑 충돌시 능력치 뜨게 만드는 bool값


	alpha -= 4; //화살표 알파값 조정


	if (PopUp == true) BgAlpha = 100; //팝업창 떴을때 백그라운드 이미지 알파값 낮춰주기
	else BgAlpha = 255;				  //팝업창 안떴을때 원래 색으로 


}

void upgrade::render()
{
	//========================기본설정=================================

	//Rectangle(getMemDC(), ShopBG);
	//Rectangle(getMemDC(), Setting);

	IMAGEMANAGER->alphaRender("Upgrade_BG", getMemDC(), ShopBG.left, ShopBG.top, BgAlpha);
	IMAGEMANAGER->alphaRender("상점 스크롤", getMemDC(), Setting.left, Setting.top, 80);
	IMAGEMANAGER->alphaRender("테스트", getMemDC(), 0, 0, 150);
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



	//TextOut(getMemDC(), WINSIZEX / 2, 20, "업그레이드(형주이)", strlen("업그레이드(형주이)"));

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

				textOutFont(getMemDC(), ShowStat.left + 30, ShowStat.top + 10, " 레  벨	: ", 20);	//클래스 이름
				textOutFont(getMemDC(), ShowStat.left + 30, ShowStat.top + 50, " 체  력	: ", 20);	//클래스 이름
				textOutFont(getMemDC(), ShowStat.left + 30, ShowStat.top + 90, " 공격력	: ", 20); 	//클래스 이름


				textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 10, Show_Unit_Stat(i, Unit_Stat[i].Lv).Lv, 20); //레벨
				textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 50, Show_Unit_Stat(i, Unit_Stat[i].Lv).Hp, 20); //체력
				textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 90, Show_Unit_Stat(i, Unit_Stat[i].Lv).att, 20); //공격력


				IMAGEMANAGER->alphaRender("화살표", getMemDC(), ShowStat.left + 130, ShowStat.top + 10, alpha);
				IMAGEMANAGER->alphaRender("화살표", getMemDC(), ShowStat.left + 130, ShowStat.top + 50, alpha);
				IMAGEMANAGER->alphaRender("화살표", getMemDC(), ShowStat.left + 130, ShowStat.top + 90, alpha);

				if (Unit_Stat[i].Lv < MAXUPGRADE)
				{
					textOutFontNum(getMemDC(), ShowStat.right - 80, ShowStat.top + 10, Show_Unit_Stat(i, Unit_Stat[i].Lv).Lv + Unit_Up[i].Lv, 20);	// 다음 레벨	
					textOutFontNum(getMemDC(), ShowStat.right - 80, ShowStat.top + 50, Show_Unit_Stat(i, Unit_Stat[i].Lv).Hp + Unit_Up[i].Hp, 20);	// 다음 레벨 체력
					textOutFontNum(getMemDC(), ShowStat.right - 80, ShowStat.top + 90, Show_Unit_Stat(i, Unit_Stat[i].Lv).att + Unit_Up[i].att, 20);	// 다음 레벨 공격력


					textOutFont(getMemDC(), ShowStat.right - 50, ShowStat.top + 10, itoa(Unit_Up[i].Lv, CLASS, 10), "[+%s]", 20);	//레벨 증가치
					textOutFont(getMemDC(), ShowStat.right - 50, ShowStat.top + 50, itoa(Unit_Up[i].Hp, CLASS, 10), "[+%s]", 20);	//체력 증가치
					textOutFont(getMemDC(), ShowStat.right - 50, ShowStat.top + 90, itoa(Unit_Up[i].att, CLASS, 10), "[+%s]", 20);	//공격력 증가치
				}

				else
				{
					textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 10, "MAX", 20);	//레벨 MAX 
					textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 50, "MAX", 20);	//체력 MAX
					textOutFont(getMemDC(), ShowStat.right - 70, ShowStat.top + 90, "MAX", 20);	//공격력 MAX
				}
			}
		}
		for (int i = 0; i < icon_Class.size(); i++)
		{

			if (IntersectRect(&NON, &icon_Class[i].icon, &iconSizeSet))
			{
				if (Unit_Stat[i].Lv < MAXUPGRADE)
				{


					IMAGEMANAGER->render("Sign", getMemDC(), Upgrade.left - 5, Upgrade.top - 5); //구매 버튼 이미지 
					IMAGEMANAGER->render("Price", getMemDC(), Upgrade.left - 15, Upgrade.bottom); // 필요 요구 골드 창 이미지
					IMAGEMANAGER->render("Gold", getMemDC(), Upgrade.left + 5, Upgrade.bottom + 3); //  골드 이미지 
					textOutFontNum(getMemDC(), Upgrade.left + 30, Upgrade.bottom + 5, Show_Unit_Stat(i, Unit_Stat[i].Lv).price, 20, RGB(200, 200, 100)); //요구 골드 
				}


				textOutFont(getMemDC(), Distruction.left + 220, Distruction.top, icon_Class[i].Class.c_str(), 20); //유닛 클래스 명
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

					textOutFont(getMemDC(), ShowStat.left + 25, ShowStat.top + 30, " 레  벨 : ", 20);
					textOutFont(getMemDC(), ShowStat.left + 25, ShowStat.top + 90, " 체  력 : ", 20);

					textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 30, Show_Object_Stat(i, Object_Stat[i].Lv).Lv, 20);
					textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 90, Show_Object_Stat(i, Object_Stat[i].Lv).Hp, 20);


					IMAGEMANAGER->alphaRender("화살표", getMemDC(), ShowStat.left + 130, ShowStat.top + 30, alpha);
					IMAGEMANAGER->alphaRender("화살표", getMemDC(), ShowStat.left + 130, ShowStat.top + 90, alpha);

				}
				else
				{

					textOutFont(getMemDC(), ShowStat.left + 25, ShowStat.top + 10, " 레  벨	: ", 20);	//클래스 이름
					textOutFont(getMemDC(), ShowStat.left + 25, ShowStat.top + 50, " 체  력	: ", 20);	//클래스 이름
					textOutFont(getMemDC(), ShowStat.left + 25, ShowStat.top + 90, " 공격력	: ", 20); 	//클래스 이름


					textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 10, Show_Object_Stat(i, Object_Stat[i].Lv).Lv, 20);
					textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 50, Show_Object_Stat(i, Object_Stat[i].Lv).Hp, 20);
					textOutFontNum(getMemDC(), ShowStat.left + 90, ShowStat.top + 90, Show_Object_Stat(i, Object_Stat[i].Lv).att, 20); //공격력


					IMAGEMANAGER->alphaRender("화살표", getMemDC(), ShowStat.left + 130, ShowStat.top + 10, alpha);
					IMAGEMANAGER->alphaRender("화살표", getMemDC(), ShowStat.left + 130, ShowStat.top + 50, alpha);
					IMAGEMANAGER->alphaRender("화살표", getMemDC(), ShowStat.left + 130, ShowStat.top + 90, alpha);
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
					IMAGEMANAGER->render("Sign", getMemDC(), Upgrade.left - 5, Upgrade.top - 5); //구매 버튼 이미지 
					IMAGEMANAGER->render("Price", getMemDC(), Upgrade.left - 15, Upgrade.bottom); // 필요 요구 골드 창 이미지
					IMAGEMANAGER->render("Gold", getMemDC(), Upgrade.left + 5, Upgrade.bottom + 3); //  골드 이미지 
					textOutFontNum(getMemDC(), Upgrade.left + 30, Upgrade.bottom + 5, Show_Object_Stat(i, Object_Stat[i].Lv).price, 20, RGB(200, 200, 100)); //요구 골드 

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
		textOutFont(getMemDC(), UpgradeCheck.left + 30, UpgradeCheck.top + 50, "업그레이드 하시겠습니까?", 25, RGB(255, 255, 0));
	}

	loadPlayer();

	imagescaleNum("숫자2", getMemDC(), WINSIZEX - 170, 14, playerInfo::getSingleton()->gold, 14, 0.5);

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




