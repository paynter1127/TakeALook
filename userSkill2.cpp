#include "stdafx.h"
#include "userSkill2.h"


HRESULT userSkill2::init()
{
	icon_Meteor = RectMakeCenter(675, 558, 70, 70);
	drag_icon_Meteor = RectMakeCenter(675, 558, 70, 70);

	now = NOT;
	drag_Meteor = false;
	Use_Meteor = false;


	Count = index = 0;
	//Ccount = Cindex = 0;
	Cscale = 0.3f;

	//Damage = RectMakeCenter(Meteor_Coordinates.x, IMAGEMANAGER->findImage("Áø2")->boudingBox().bottom, 60, 60);


	return S_OK;
}

void userSkill2::release()
{
}

void userSkill2::update()
{
	if (now == 2)
	{
		//drag_icon_Meteor = RectMakeCenter(_ptMouse.x, _ptMouse.y, 150, 108);
		IMAGEMANAGER->findImage("BlackHole")->setFrameX(index);
		IMAGEMANAGER->findImage("BlackHole2")->setFrameX(index);
	}

	if (now == 3||now==4)
	{
		//drag_icon_Meteor = RectMakeCenter(_ptMouse.x, _ptMouse.y, 100, 100);
		IMAGEMANAGER->findImage("Micon_BlackHole2")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
		Count++;
	//	if (Count % 2 == 0)
		{
			index++;

			IMAGEMANAGER->findImage("BlackHole")->setFrameY(0);

			if (index > 14)
			{
				index = 0;
			}
			IMAGEMANAGER->findImage("BlackHole")->setFrameX(index);
			IMAGEMANAGER->findImage("BlackHole2")->setFrameX(index);
		}
	}
	Ccount++;
}

void userSkill2::render()
{
	//Rectangle(getMemDC(), icon_Meteor);

	if (now == 2) 		IMAGEMANAGER->findImage("Micon_BlackHole2")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
	//Rectangle(getMemDC(), drag_icon_Meteor);


	if (now == 3)
	{
		//	IMAGEMANAGER->findImage("Áø")->frameRender(getMemDC(), 0, 0);
		//	IMAGEMANAGER->frameRender("Áø2", getMemDC(), 100, -80,
			/*	IMAGEMANAGER->findImage("Meteor_Circle")->getFrameX(), IMAGEMANAGER->findImage("Meteor_Circle")->getFrameY(),
				Cscale);
				*/
				//if (Cscale > 1.48f)
			//Rectangle(getMemDC(), Damage);
		{
			//Rectangle(getMemDC(), Damage);		
			IMAGEMANAGER->findImage("Micon_BlackHole2")->render(getMemDC(), _ptMouse.x, _ptMouse.y);

			IMAGEMANAGER->findImage("BlackHole")->setFrameX(0);
			IMAGEMANAGER->frameRender("BlackHole", getMemDC(),
				Damage.left, Damage.top);
			//IMAGEMANAGER->findImage("Meteor_Circle")->getY() + IMAGEMANAGER->findImage("Meteor_Circle")->getHeight() / 2);
		}
	}
	if (now == 4)
	{
		
		//Rectangle(getMemDC(), Damage);
		//Rectangle(getMemDC(), exit);
		IMAGEMANAGER->frameRender("BlackHole", getMemDC(),
			Damage.left, Damage.top);
		//IMAGEMANAGER->findImage("BlackHole2")->setFrameX(0);
		IMAGEMANAGER->frameRender("BlackHole2", getMemDC(),
			exit.left, exit.top);
	}
}