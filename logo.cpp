#include "stdafx.h"
#include "logo.h"

HRESULT logo::init()
{
	count = 0;
	num = 0;

	wsprintf(a, "f%d", num);
	//num++;
	//count++;
	take = false;
	return S_OK;
}

void logo::release()
{
}

void logo::update()
{

	if (count % 3 == 0)
	{
		wsprintf(a, "f%d", num);
		num++;

		if (num == 65)
		{
			take = true;
			SOUNDMANAGER->play("¶¼²¬·è");
		}


		if (num == 101)
		{
			SCENEMANAGER->loadScene("title");
		}
	}
	count++;

}

void logo::render()
{
	IMAGEMANAGER->findImage(a)->render(getMemDC(), 400 - 187, 61);
	if (take==true)
		textOutFont(getMemDC(), 410, 450, "Take a Look",66,RGB(0,255,255));

		//TextOut(getMemDC(), WINSIZEX / 2 - 50, 500, "Take a Look", strlen("Take a Look"));

}
