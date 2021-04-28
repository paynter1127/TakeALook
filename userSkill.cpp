#include "stdafx.h"
#include "userSkill.h"

HRESULT userSkill::init()
{

	//Meteor.x = 550;
	//Meteor.y = 530;

	icon_Meteor = RectMakeCenter(594, 558, 70, 70);
	drag_icon_Meteor = RectMakeCenter(594, 558, 70, 70);

	drag_Meteor = false;
	Use_Meteor = false;

	Count = index = 0;
	Ccount = Cindex = 0;
	Cscale = 0.3f;


	Meteor.x = 0;
	Meteor.y = 0;

	Meteor_Count = 0;

	IMAGEMANAGER->addFrameImage("Meteor", "Skill_Meteor2.bmp", 3230 * 2, 163 * 2, 19, 1);
	IMAGEMANAGER->addFrameImage("Meteor_Circle", "Skill_Meteor_Circle.bmp", 2880, 145, 6, 1);

	Meteor_Coordinates.x = RND->range(Meteor.x - 100, Meteor.x + 400);
	Meteor_Coordinates.y = RND->range(IMAGEMANAGER->findImage("Meteor_Circle")->getY() - 50, IMAGEMANAGER->findImage("Meteor_Circle")->getY() + 50);

	Damage = RectMakeCenter(Meteor_Coordinates.x, IMAGEMANAGER->findImage("Meteor")->boudingBox().bottom, 60, 60);

	

	return S_OK;
}

void userSkill::release()
{
}

void userSkill::update()
{


	if (drag_Meteor == true) drag_icon_Meteor = RectMakeCenter(_ptMouse.x, _ptMouse.y, 60, 60);

	if (Use_Meteor == true)
	{

		if (Cscale > 1.48f)
		{
			Count++;
			if (Count % 3 == 0)
			{
				index--;

				IMAGEMANAGER->findImage("Meteor")->setFrameY(0);

				if (index == 3) Damage = RectMakeCenter(Meteor_Coordinates.x + 300, Meteor_Coordinates.y + 300,300,300);
				else Damage = RectMakeCenter(-50, 50, 200, 200);


				if (index < 0)
				{
					SOUNDMANAGER->play("사운드_메테오");
					index = 19;

					Meteor_Count++;

					Meteor_Coordinates.x = RND->range(Meteor.x - 100, Meteor.x + 400);
					Meteor_Coordinates.y = RND->range(IMAGEMANAGER->findImage("Meteor_Circle")->getY() - 50, IMAGEMANAGER->findImage("Meteor_Circle")->getY() + 70);


				}
				IMAGEMANAGER->findImage("Meteor")->setFrameX(index);
			}
		}
		Ccount++;

		if (Ccount % 3 == 0)
		{
			Cindex++;

			IMAGEMANAGER->findImage("Meteor_Circle")->setFrameY(0);

			if (Meteor_Count < 13)
			{
				if (Cscale < 1.5f) Cscale += 0.05f;
				else Cscale = 1.5f;
			}
			if (Meteor_Count > 13) Cscale -= 0.05f;


			if (Cindex > 6)
			{
				
				Cindex = 0;
			}
			IMAGEMANAGER->findImage("Meteor_Circle")->setFrameX(Cindex);
		}
	}

	if (Use_Meteor == true && Cscale < 0)
	{
		Cscale = 0.3f;
		Meteor_Count = 0;
		Use_Meteor = false;
	}


}

void userSkill::render()
{
	//Rectangle(getMemDC(), icon_Meteor);

	if (drag_Meteor == true) 		IMAGEMANAGER->findImage("Micon_Meteor2")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
	//Rectangle(getMemDC(), drag_icon_Meteor);


	if (Use_Meteor == true)
	{
		IMAGEMANAGER->scaleFrameRender("Meteor_Circle", getMemDC(),
			Meteor.x, Meteor.y,
			IMAGEMANAGER->findImage("Meteor_Circle")->getFrameX(), IMAGEMANAGER->findImage("Meteor_Circle")->getFrameY(),
			Cscale);

		if (Cscale > 1.48f)
		{
			IMAGEMANAGER->frameRender("Meteor", getMemDC(),
				Meteor_Coordinates.x + 100,
				Meteor_Coordinates.y);
			//IMAGEMANAGER->findImage("Meteor_Circle")->getY() + IMAGEMANAGER->findImage("Meteor_Circle")->getHeight() / 2);
		}
	}


}
