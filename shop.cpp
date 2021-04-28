#include "stdafx.h"
#include "shop.h"


HRESULT shop::init()
{
	ShowUpgrade = RectMake(WINSIZEX - 135, 60, 100, 40);

	ShopBG = RectMake(0, 0, WINSIZEX, 450);
	Setting = RectMake(0, 200, WINSIZEX, 200);
	Scroll = false;


	IMAGEMANAGER->addFrameImage("Meteor", "Skill_Meteor.bmp", 3230, 163, 19, 1);

	Count = 0;
	index = 0;

	IconSize = 200;
	iconSizeSet = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, IconSize * 1 / 4, IconSize * 1 / 4);
	iconSizeSet_X = WINSIZEX / 2;
	IconDistance = 500;

	MouseMovingPoint = 0;

	alpha = 255;
	BgAlpha = 255;
	Kcount = 5;
	//=================================================================

	BuyCheck = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 50, 300, 200);
	PopUp = false;

	Player_Gold = RectMake(WINSIZEX - 296, 7, 170, 36);


	//Yes = RectMake(BuyCheck.left + 50, BuyCheck.bottom - 45, 80, 40);
	//No = RectMake(BuyCheck.right - 120, BuyCheck.bottom - 45, 80, 40);



	//=================================================================

	Skill_getCount = RectMake(100, 5, 160, 40);

	//=========================디스트럭션&업그레이드 선택==================

	Distruction = RectMake(0, 450, WINSIZEX, 150);
	BuySkill = RectMake(Distruction.right - 150, Distruction.top + 10, 100, 100);


	iconSizeSet = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, IconSize * 1 / 4, IconSize * 1 / 4);

	if (!icon_Skill.empty()) icon_Skill.clear();

	//=====================블랙홀 아이콘 초기화===========================


	icon_BlackHole.x = WINSIZEX / 2;
	icon_BlackHole.y = WINSIZEY / 2;
	icon_BlackHole.IconSize = IconSize;
	icon_BlackHole.icon = RectMakeCenter(icon_BlackHole.x, icon_BlackHole.y, icon_BlackHole.IconSize, icon_BlackHole.IconSize);
	icon_BlackHole.Micon = RectMake(Skill_getCount.left, Skill_getCount.top, 40, 40);
	icon_BlackHole.scale = 1.0f;
	icon_BlackHole.Click = false;
	icon_BlackHole.ImageKey = "Icon_BlackHole";
	icon_BlackHole.MimageKey = "Micon_BlackHole";
	icon_BlackHole.BimageKey = "SkillBook_BlackHole";
	icon_BlackHole.Name = "블랙홀";
	icon_BlackHole.price = 3000;
	icon_BlackHole.Discription1 = "모든걸 빨아들이는 마법";
	icon_BlackHole.Discription2 = "범위 내의 적군을 모두 빨아들이고";
	icon_BlackHole.Discription3 = "다시 랜덤한 위치에 소환시킨다.";

	icon_Skill.push_back(icon_BlackHole);

	IMAGEMANAGER->addImage(icon_BlackHole.ImageKey, "Shop/Shop_Icon_BlackHole.bmp", IconSize, IconSize);
	IMAGEMANAGER->addImage(icon_BlackHole.MimageKey, "Shop/Shop_Icon_BlackHole_Mini.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(icon_BlackHole.BimageKey, "Shop/Shop_SkillBook_BlackHole.bmp", 40, 40, true, RGB(255, 0, 255));

	//===============메테오 아이콘 초기화=====================

	icon_Meteor.x = icon_BlackHole.x + IconDistance;
	icon_Meteor.y = WINSIZEY / 2;
	icon_Meteor.IconSize = IconSize;
	icon_Meteor.icon = RectMakeCenter(icon_Meteor.x, icon_Meteor.y, icon_Meteor.IconSize, icon_Meteor.IconSize);
	icon_Meteor.Micon = RectMake(Skill_getCount.left + 90, Skill_getCount.top, 40, 40);
	icon_Meteor.scale = 1.0f;
	icon_Meteor.ImageKey = "Icon_Meteor";
	icon_Meteor.MimageKey = "Micon_Meteor";
	icon_Meteor.BimageKey = "SkillBook_Meteor";
	icon_Meteor.Click = false;
	icon_Meteor.Name = "메테오";
	icon_Meteor.price = 6000;
	icon_Meteor.Discription1 = "모든걸 다 불태워버리는 마법";
	icon_Meteor.Discription2 = "전범위의 적들에게";
	icon_Meteor.Discription3 = "막대한 피해를 줄 수 있다.";
	icon_Skill.push_back(icon_Meteor);

	IMAGEMANAGER->addImage(icon_Meteor.ImageKey, "Shop/Shop_Icon_Meteor.bmp", IconSize, IconSize);
	IMAGEMANAGER->addImage(icon_Meteor.MimageKey, "Shop/Shop_Icon_Meteor_Mini.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(icon_Meteor.BimageKey, "Shop/Shop_SkillBook_Meteor.bmp", 40, 40, true, RGB(255, 0, 255));

	//===============회복 아이콘 초기화=====================

	icon_Heal.x = icon_Meteor.x + IconDistance;
	icon_Heal.y = WINSIZEY / 2;
	icon_Heal.IconSize = IconSize;
	icon_Heal.icon = RectMakeCenter(icon_Heal.x, icon_Heal.y, icon_Heal.IconSize, icon_Heal.IconSize);
	icon_Heal.Micon = RectMake(Skill_getCount.left + 180, Skill_getCount.top, 40, 40);
	icon_Heal.scale = 1.0f;
	icon_Heal.ImageKey = "Icon_Heal";
	icon_Heal.MimageKey = "Micon_Heal";
	icon_Heal.BimageKey = "SkillBook_Heal";
	icon_Heal.Click = false;
	icon_Heal.Name = "회복";
	icon_Heal.price = 4000;
	icon_Heal.Discription1 = "아군의 사기를 올려주는 마법";
	icon_Heal.Discription2 = "범위 내에 부딪힌 아군들의";
	icon_Heal.Discription3 = "체력을 회복시켜준다 ";
	icon_Skill.push_back(icon_Heal);

	IMAGEMANAGER->addImage(icon_Heal.ImageKey, "Shop/Shop_Icon_Heal.bmp", IconSize, IconSize);
	IMAGEMANAGER->addImage(icon_Heal.MimageKey, "Shop/Shop_Icon_Heal_Mini.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(icon_Heal.BimageKey, "Shop/Shop_SkillBook_Heal.bmp", 40, 40, true, RGB(255, 0, 255));


	//================================================================

	Count_BlackHole = 0;
	Count_Meteor = 0;
	Count_Heal = 0;

	Count_Skill.push_back(Count_BlackHole);
	Count_Skill.push_back(Count_Meteor);
	Count_Skill.push_back(Count_Heal);

	return S_OK;
}

void shop::release()
{
}

void shop::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&ShowUpgrade, _ptMouse))
		{
			SCENEMANAGER->loadScene("upgrade");
			SOUNDMANAGER->play("버튼");
		}
		if (PtInRect(&Setting, _ptMouse))
		{
			MouseMovingPoint = _ptMouse.x;
			Scroll = true;


		}

		for (int i = 0; i < icon_Skill.size(); i++)
		{
			if (icon_Skill[i].Click == true)
			{
				if (PtInRect(&BuySkill, _ptMouse))
				{

					SOUNDMANAGER->play("버튼");
					PopUp = true;
				}
			}
		}

		if (PopUp == true)
		{
			if (PtInRect(&Yes, _ptMouse))
			{
				for (int i = 0; i < icon_Skill.size(); i++)
				{
					if (icon_Skill[i].Click == true)
					{
						if (playerInfo::getSingleton()->gold >= icon_Skill[i].price)
						{
							playerInfo::getSingleton()->gold -= icon_Skill[i].price;


							getSkill();
							savePlayer();

							PopUp = false;
							SOUNDMANAGER->play("Buy_Skill");

							break;
						}
					}
				}
			}
			if (PtInRect(&No, _ptMouse))
			{
				SOUNDMANAGER->play("버튼");
				PopUp = false;
			}
		}

		if (PtInRect(&IMAGEMANAGER->findImage("Back")->boudingBox(), _ptMouse)) SCENEMANAGER->loadScene("lobby");
	}




	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (PtInRect(&Yes, _ptMouse))
		{

			SoundCheck = true;
		}

		Scroll = false;
	}


	Yes = RectMake(BuyCheck.left + 50, BuyCheck.bottom - 45, 80, 40);
	No = RectMake(BuyCheck.right - 120, BuyCheck.bottom - 45, 80, 40);


	iconScroll();


	if (PopUp == true) BgAlpha = 100;
	else BgAlpha = 255;

	for (int i = 0; i < icon_Skill.size(); i++)
	{
		if (IntersectRect(&NON, &icon_Skill[i].icon, &iconSizeSet)) icon_Skill[i].Click = true;
		else icon_Skill[i].Click = false;
	}


	IMAGEMANAGER->findImage("Meteor")->setFrameY(0);

	Count++;

	if (Count % Kcount == 0)
	{
		index++;

		//if (index < 4) Kcount = 5;
		//if (index > 4 && index < 12) Kcount = 1;
		//if (index > 12 && index < 19) Kcount = 5;

		if (index > 19)
		{

			index = 0;
		}
		IMAGEMANAGER->findImage("Meteor")->setFrameX(index);
	}


}

void shop::render()
{

	char Text[128];

	//Rectangle(getMemDC(), ShopBG);
	//Rectangle(getMemDC(), Setting);
	//Rectangle(getMemDC(), Skill_getCount);


	IMAGEMANAGER->alphaRender("Shop_BG", getMemDC(), ShopBG.left, ShopBG.top, BgAlpha);
	IMAGEMANAGER->alphaRender("상점 스크롤", getMemDC(), Setting.left, Setting.top, 110);
	IMAGEMANAGER->render("Discription", getMemDC(), Distruction.left, Distruction.top - 40);
	IMAGEMANAGER->alphaRender("테스트", getMemDC(), 0, 0, 200);
	IMAGEMANAGER->render("Back", getMemDC(), 4, 7);
	IMAGEMANAGER->render("goldbar", getMemDC(), Player_Gold.left, Player_Gold.top);

	imagescaleNum("숫자2", getMemDC(), WINSIZEX - 170, 14, playerInfo::getSingleton()->gold, 14, 0.5);


	//Rectangle(getMemDC(), ShowUpgrade);

	//IMAGEMANAGER->alphaRender("Upgrade_Load", getMemDC(), ShowUpgrade.left - 23, ShowUpgrade.top - 15, BgAlpha);
	IMAGEMANAGER->alphaRender("Shop_Load", getMemDC(), ShowUpgrade.left - 23, ShowUpgrade.top - 15, BgAlpha);


	for (int i = 0; i < icon_Skill.size(); i++)
	{


		if (i == 0) Count_Skill[i] = playerInfo::getSingleton()->num_skill1;
		if (i == 1) Count_Skill[i] = playerInfo::getSingleton()->num_skill2;
		if (i == 2) Count_Skill[i] = playerInfo::getSingleton()->num_skill3;


		//Rectangle(getMemDC(), icon_Skill[i].icon);
		IMAGEMANAGER->alphaRender(icon_Skill[i].ImageKey, getMemDC(), icon_Skill[i].icon.left, icon_Skill[i].icon.top, BgAlpha);

		//Rectangle(getMemDC(),icon_Skill[i].Micon);
		IMAGEMANAGER->render(icon_Skill[i].BimageKey, getMemDC(), icon_Skill[i].Micon.left, icon_Skill[i].Micon.top);
		IMAGEMANAGER->alphaRender(icon_Skill[i].MimageKey, getMemDC(), icon_Skill[i].Micon.left + 12, icon_Skill[i].Micon.top + 13, 255);

		textOutFont(getMemDC(), icon_Skill[i].Micon.left + 40, icon_Skill[i].Micon.top + 15, "x ", 20, RGB(150 * (icon_Skill.size() - i), 50 * (icon_Skill.size() - i), 50 * (icon_Skill.size() - i)));
		textOutFontNum(getMemDC(), icon_Skill[i].Micon.left + 55, icon_Skill[i].Micon.top + 15, Count_Skill[i], 20, RGB(150 * (icon_Skill.size() - i), 50 * (icon_Skill.size() - i), 50 * (icon_Skill.size() - i)));
		{
			if (icon_Skill[i].Click == true)
			{
				IMAGEMANAGER->render("Sign", getMemDC(), BuySkill.left - 5, BuySkill.top - 5); //구매 버튼 이미지 
				IMAGEMANAGER->render("Price", getMemDC(), BuySkill.left - 15, BuySkill.bottom); // 필요 요구 골드 창 이미지
				IMAGEMANAGER->render("Gold", getMemDC(), BuySkill.left + 5, BuySkill.bottom + 3); //  골드 이미지 

				textOutFont(getMemDC(), Distruction.left + 220, Distruction.top + 10, icon_Skill[i].Name.c_str(), 20);
				textOutFont(getMemDC(), Distruction.left + 130, Distruction.top + 50, icon_Skill[i].Discription1.c_str(), 20);
				textOutFont(getMemDC(), Distruction.left + 130, Distruction.top + 70, icon_Skill[i].Discription2.c_str(), 20);
				textOutFont(getMemDC(), Distruction.left + 130, Distruction.top + 90, icon_Skill[i].Discription3.c_str(), 20);

				textOutFontNum(getMemDC(), BuySkill.left + 30, BuySkill.bottom + 5, icon_Skill[i].price, 20, RGB(200, 200, 100));
			}
		}

	}
	if (PopUp == true)
	{
		//Rectangle(getMemDC(), BuyCheck);
		//Rectangle(getMemDC(), Yes);
		//Rectangle(getMemDC(), No);

		IMAGEMANAGER->render("Pop_Up", getMemDC(), BuyCheck.left, BuyCheck.top);
		IMAGEMANAGER->render("Yes", getMemDC(), Yes.left, Yes.top);
		IMAGEMANAGER->render("No", getMemDC(), No.left, No.top);
		textOutFont(getMemDC(), BuyCheck.left + 30, BuyCheck.top + 50, "업그레이드 하시겠습니까?", 25, RGB(255, 255, 0));
	}


	//Rectangle(getMemDC(), Distruction);
	//Rectangle(getMemDC(), BuySkill);

	//IMAGEMANAGER->frameRender("Meteor",getMemDC(), WINSIZEX / 2, 200);

}

void shop::iconScroll()
{
	if (Scroll == true)
	{
		for (int i = 0; i < icon_Skill.size(); i++) icon_Skill[i].x -= (_ptMouse.x - MouseMovingPoint) / 8;

		for (int i = 0; i < icon_Skill.size(); i++)
		{
			if (icon_Skill[i].x > WINSIZEX * 51 / 100)
			{
				if (i == 0) icon_Skill[i].x = WINSIZEX * 51 / 100;
				else icon_Skill[i].x = icon_Skill[i - 1].x + IconDistance;
			}
		}

		for (int i = icon_Skill.size() - 1; i > -1; i--)
		{
			if (i == 2 && icon_Skill[i].x < WINSIZEX * 49 / 100)
			{
				icon_Skill[i].x = WINSIZEX * 49 / 100;
			}
			if (i == 1) icon_Skill[i].x = icon_Skill[i + 1].x - IconDistance;
			if (i == 0) icon_Skill[i].x = icon_Skill[i + 1].x - IconDistance;

		}


		for (int i = 0; i < icon_Skill.size(); i++) icon_Skill[i].icon = RectMakeCenter(icon_Skill[i].x, icon_Skill[i].y, icon_Skill[i].IconSize, icon_Skill[i].IconSize);
	}
}

void shop::getSkill()
{
	for (int i = 0; i < icon_Skill.size(); i++)
	{


		if (icon_Skill[i].Click == true)
		{
			Count_Skill[i]++;

			if (i == 0) playerInfo::getSingleton()->num_skill1 = Count_Skill[i];
			if (i == 1) playerInfo::getSingleton()->num_skill2 = Count_Skill[i];
			if (i == 2) playerInfo::getSingleton()->num_skill3 = Count_Skill[i];


		}
	}
}
