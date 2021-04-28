#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//�̰����� �ʱ�ȭ�� �Ѵ�

	//�� �߰�
	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("lobby", new lobby);

	SCENEMANAGER->addScene("upgrade", new upgrade);
	SCENEMANAGER->addScene("Shop", new shop);
	SCENEMANAGER->addScene("logo", new logo);

	SCENEMANAGER->addScene("stageMap", new stageMap);
	SCENEMANAGER->addScene("stage", new stage);
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);



	//���� �� ����
	SCENEMANAGER->loadScene("�ε�ȭ��");
	//SCENEMANAGER->loadScene("stage");
	//���

	//��Ʈ �߰�
	AddFontResource("Maplestory Bold.ttf");



	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//�̹��� Ŭ������ ���������� ����� �� ����
	//�����Ҵ� new�� ����ߴٸ� �̰����� SAFE_DELETE() ����Ѵ�
	RemoveFontResource("Maplestory Bold.ttf");
}


//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//�����ϰ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�
	SCENEMANAGER->update();
	SOUNDMANAGER->update();

	//���� �� �̵�
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->loadScene("stage");
	}
	//���� �� �̵�
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->loadScene("lobby");
	}
	//���� �� �̵�
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->loadScene("upgrade");
	}

	//���̺�
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		savePlayer();
	}
	//�ε�
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		loadPlayer();
	}

}

//=============================================================
//	## ���� ## render(HDC hdc)
//=============================================================
void mainGame::render()
{
	//��� �� ��Ʈ�� (�̰͵� ������ �׳� �α�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	SCENEMANAGER->render();
	//textOutMouse(getMemDC()); //�Ϸ�
	//textOutDbug(getMemDC(), playerInfo::getSingleton()->gold);


	//textOutFont(getMemDC(), 20, 20, "�۲��׽�Ʈ", 40, RGB(255, 255, 255) );
	//TextOut(getMemDC(), 20, 0, "���� �׽�Ʈ", strlen("���� �׽�Ʈ"));


	//TextOut(getMemDC(), 20, 20, "�κ�", strlen("�κ�"));
//=============================================================
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());
}
