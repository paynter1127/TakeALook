#include "stdafx.h"
#include "userSkill3.h"


HRESULT userSkill3::init()
{

	icon_Meteor = RectMakeCenter(750, 558, 70, 70);
	drag_icon_Meteor = RectMakeCenter(750, 558, 70, 70);


	drag_Meteor = false;
	Use_Meteor = false;


	Count = index = 0;
	//Ccount = Cindex = 0;
	Cscale = 0.3f;

	//Damage = RectMakeCenter(Meteor_Coordinates.x, IMAGEMANAGER->findImage("진2")->boudingBox().bottom, 60, 60);


	return S_OK;
}

void userSkill3::release()
{
}

void userSkill3::update()
{
	/*if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&icon_Meteor, _ptMouse))
		{
			//if (playerInfo::getSingleton()->num_skill2 > 0)
			drag_Meteor = true;
		}
	}*/

	if (drag_Meteor == true) drag_icon_Meteor = RectMakeCenter(_ptMouse.x, _ptMouse.y, 416, 108);


	if (Use_Meteor == true)
	{

		if (Count % 80 == 0)
		{
			SOUNDMANAGER->play("힐_사운드");
		}
		Count++;
		if (Count % 3 == 0)
		{
			index++;

			IMAGEMANAGER->findImage("진")->setFrameY(0);
			if (index > 5)
			{
				index = 0;
			}
			IMAGEMANAGER->findImage("진")->setFrameX(index);
		}
	}
	Ccount++;


	//if (Ccount % 3 == 0)
	//{
	//	Cindex++;

	//	IMAGEMANAGER->findImage("Meteor_Circle")->setFrameY(0);


	//	if (Cindex > 6)
	//	{
	//		Cindex = 0;
	//	}
	//	IMAGEMANAGER->findImage("Meteor_Circle")->setFrameX(Cindex);
	//}




}

void userSkill3::render()
{
	//Rectangle(getMemDC(), icon_Meteor);

	if (drag_Meteor == true) 		IMAGEMANAGER->findImage("Micon_Heal2")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
	//Rectangle(getMemDC(), drag_icon_Meteor);


	if (Use_Meteor == true)
	{
		//	IMAGEMANAGER->findImage("진")->frameRender(getMemDC(), 0, 0);
		//	IMAGEMANAGER->frameRender("진2", getMemDC(), 100, -80,
			/*	IMAGEMANAGER->findImage("Meteor_Circle")->getFrameX(), IMAGEMANAGER->findImage("Meteor_Circle")->getFrameY(),
				Cscale);
				*/
				//if (Cscale > 1.48f)
		//Rectangle(getMemDC(), Damage);
		{
			IMAGEMANAGER->frameRender("진", getMemDC(),
				Damage.left, Damage.top);
			//IMAGEMANAGER->findImage("Meteor_Circle")->getY() + IMAGEMANAGER->findImage("Meteor_Circle")->getHeight() / 2);
		}
	}

}

