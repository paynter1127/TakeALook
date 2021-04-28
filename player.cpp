#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init()
{
	//�÷��̾� �̹��� �ʱ�ȭ
	_rocket = IMAGEMANAGER->addImage("rocket", "rocket.bmp", WINSIZEX / 2, WINSIZEY - 100, 52, 64, true, RGB(255, 0, 255));
	//_rcPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 52, 64);
	
	//�̻��� Ŭ���� �ʱ�ȭ
	_missile = new missile;
	_missile->init(10, 800);

	//��ź Ŭ���� �ʱ�ȭ
	_bomb = new bomb;
	_bomb->init(5, 600);


	return S_OK;
}

void player::release()
{
	//�̻��� Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);

	//��ź Ŭ���� ����
	_bomb->release();
	SAFE_DELETE(_bomb);
}

void player::update()
{
	//�̹��� �ٿ���ڽ��� �浹ó��
	//RECT rc;
	//if(IntersectRect(&rc, &_rocket->boudingBox(), ))
	
	//�÷��̾� �����̱� & ȭ������� ����� ���ϰ�
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rocket->getX() > 0)
	{
		_rocket->setX(_rocket->getX() - 5.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rocket->getX() < WINSIZEX)
	{
		_rocket->setX(_rocket->getX() + 5.0f);
	}
	//�Ѿ˹߻�
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//�Ѿ�Ŭ������ �ϲ� �߻���Ѷ�~
		_missile->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}
	//��ź�߻�
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		//��źŬ������ �ϲ� �߻���Ѷ�~
		_bomb->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	//�̻��� Ŭ���� ������Ʈ
	_missile->update();

	//��ź Ŭ���� ������Ʈ
	_bomb->update();


	//�浹
	RECT tttemp;
	for (int i = 0; i < eeenemyManager->getVMinion().size(); i++)
	{
				//system("pause");
		for (int j = 0; j < _missile->getMissile().size(); j++)
		{
			
			if (IntersectRect(&tttemp, &_getMissile()[j].rc, &eeenemyManager->getVMinion()[i]->getRect()))
			{
				eeenemyManager->removeMinion(i);
				getRemoveMissile(j);
			}
			if (i == eeenemyManager->getVMinion().size()) break;
		}
	}
	

}

void player::render()
{
	//�÷��̾� ����
	_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());

	//�̻��� Ŭ���� ����
	_missile->render();

	//��ź Ŭ���� ����
	_bomb->render();

}
