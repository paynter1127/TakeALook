#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	//IMAGEMANAGER->addFrameImage("����", "numSprite.bmp", 360, 42, 10, 1);
	IMAGEMANAGER->addFrameImage("����22", "����2.bmp", 360, 42, 10, 1, true, RGB(255, 0, 255));
	i = 0;
	//�ε�
	SOUNDMANAGER->addSound("256113__nckn__done", "256113__nckn__done.wav", false, false);
	
	

	isDone = false;

	return S_OK;
}

void loadingScene::release()
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ�� ����
	if (_loading->loadingDone())
	{
		
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("��ư");
			loadPlayer();
			SCENEMANAGER->loadScene("logo");
		}
		//SCENEMANAGER->loadScene("stage");
	}
}

void loadingScene::render()
{
	//�ε�Ŭ���� ����
	_loading->render();
	imageNum("����22", getMemDC(), 744, 529, (_loading->getCurrentGauge() * 100) / _loading->getLoadItem().size(), 26); //�Ϸ�

	textOutFont(getMemDC(), 184, 102, "3���� ���ο� �Ʊ�", 20, RGB(255, 255, 0));
	textOutFont(getMemDC(), 184, 126, "������ ��ȯ�� ������", 20, RGB(255, 255, 0));

	textOutFont(getMemDC(), 420, 50, "������ ���� ��ȭ��", 20, RGB(255, 255, 0));
	textOutFont(getMemDC(), 420, 50 + 24, "���� �����ϰ�!", 20, RGB(255, 255, 0));

	textOutFont(getMemDC(), 18, 342, "�����Ҷ� ���� ���ŷ�", 20, RGB(255, 255, 0));
	textOutFont(getMemDC(), 18, 342 + 24, "��Ը� ���� ������!", 20, RGB(255, 255, 0));

	textOutFont(getMemDC(), 524, 343, "������ ������", 20, RGB(255, 255, 0));
	textOutFont(getMemDC(), 524, 343 + 24, "���� ���� �Զ�����!", 20, RGB(255, 255, 0));

	//textOutMouse(getMemDC());


	

	//���� �̸� ǥ��
	//if(IMAGEMANAGER->findImage(_loading->getLoadItem()[i]->getImageResource().keyName))
	if (IMAGEMANAGER->findImage(_loading->getLoadItem()[i]->getImageResource().keyName))
	{
		//TextOut(getMemDC(), 30, 544,
		//	IMAGEMANAGER->findImage(_loading->getLoadItem()[i]->getImageResource().keyName)->getFileName(),
		//	strlen(IMAGEMANAGER->findImage(_loading->getLoadItem()[i]->getImageResource().keyName)->getFileName()));
		textOutFont(getMemDC(), 30, 544, IMAGEMANAGER->findImage(_loading->getLoadItem()[i]->getImageResource().keyName)->getFileName(), 16);
		if ((_loading->getCurrentGauge() * 100) / _loading->getLoadItem().size() == 99) 
		{
			SOUNDMANAGER->play("256113__nckn__done");
			i++;
		}
		else if((_loading->getCurrentGauge() * 100) / _loading->getLoadItem().size() != 100) i++;
		else
		{
			//�ε�
			textOutFont(getMemDC(), _ptMouse.x + 10, _ptMouse.y, "Click to", 40, RGB(250, 200, 0));
			textOutFont(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 42, "Continue", 40, RGB(250, 200, 0));
			//SOUNDMANAGER->play("����_�Ʊ�");
			//"����_��",
				//"����_�Ʊ�"
		}
		//_loading->getCurrentGauge()
		//_currentGauge, _vLoadItem.size()
			//_loadingBar->setGauge(_currentGauge, _vLoadItem.size());
	}



}

/* < ���⿡ �� ���� ����� �̹��� �̸� �ε� �صδ� ���Դϴ�. >*/
void loadingScene::loadingImage()
{







	_loading->loadImage("��������", "��������.bmp", 3, 3);

//================================================================================================================

	//�������� �̹���
	_loading->loadImage("���1", "���1.800.600.bmp", 800, 595);
	_loading->loadImage("���1_2", "���1_2.1003.369.bmp", 1003, 369);
	_loading->loadImage("���2", "���2.800.600.bmp", 812, 417);
	_loading->loadImage("���3", "���3.800.600.bmp", 800, 600);
	_loading->loadImage("���5", "���5.800.600.bmp", 800, 420);
	_loading->loadImage("���6", "���6.800.600.bmp", 1100, 310);
	_loading->loadImage("����", "������.1415.600.bmp", 1415, 600);
	
	//_loading->loadImage("���5.�̴ϸ�", "���5.800.600.bmp", 800, 500);

	_loading->loadImage("�ΰ���UI", "�ΰ���UI.800.600.bmp", 800, 600);



	_loading->loadImage("�����", "hero.256.311.bmp", 256 / 2, 311 / 2);
	_loading->loadImage("�����_��", "hero_enemy.238.270.bmp", 238 / 2, 270 / 2);
	_loading->loadImage("������", "worrior.285.314.bmp", 285 / 4, 314 / 4);
	_loading->loadImage("������_��", "worrior_enemy.286.269.bmp", 286 / 4, 269 / 4);
	_loading->loadImage("��ó", "archer.251.258.bmp", 251 / 3.6, 258 / 3.6);
	_loading->loadImage("��ó_��", "archer_enemy.248.247.bmp", 248 / 3.6, 247 / 3.6);
	_loading->loadImage("������", "magician.256.259.bmp", 256 / 3.6, 259 / 3.6);
	_loading->loadImage("������_��", "magician_enemy.243.273.bmp", 243 / 3.6, 273 / 3.6);
	_loading->loadImage("�ɽ�", "castle.397.484.bmp", 397 / 1.4, 484 / 1.4);
	_loading->loadImage("�ɽ�_��", "castle_enemy.423.445.bmp", 423 / 1.3, 445 / 1.3);
	_loading->loadImage("Ÿ��", "tower.163.244.bmp", 163 / 1.6, 244 / 1.6);
	_loading->loadImage("Ÿ��_��", "tower_enemy.160.220.bmp", 160 / 1.6, 220 / 1.6);

	_loading->loadImage("�����_�ǰ�", "hero_beHit.256.311.bmp", 256 / 2, 311 / 2);
	_loading->loadImage("�����_��_�ǰ�", "hero_enemy_beHit.238.270.bmp", 238 / 2, 270 / 2);
	_loading->loadImage("������_�ǰ�", "worrior_beHit.285.314.bmp", 285 / 4, 314 / 4);
	_loading->loadImage("������_��_�ǰ�", "worrior_enemy_beHit.286.269.bmp", 286 / 4, 269 / 4);
	_loading->loadImage("��ó_�ǰ�", "archer_beHit.251.258.bmp", 251 / 3.6, 258 / 3.6);
	_loading->loadImage("��ó_��_�ǰ�", "archer_enemy_beHit.248.247.bmp", 248 / 3.6, 247 / 3.6);
	_loading->loadImage("������_�ǰ�", "magician_beHit.256.259.bmp", 256 / 3.6, 259 / 3.6);
	_loading->loadImage("������_��_�ǰ�", "magician_enemy_beHit.243.273.bmp", 243 / 3.6, 273 / 3.6);
	_loading->loadImage("�ɽ�_�ǰ�", "castle_beHit.397.484.bmp", 397 / 1.4, 484 / 1.4);
	_loading->loadImage("�ɽ�_��_�ǰ�", "castle_enemy_beHit.423.445.bmp", 423 / 1.3, 445 / 1.3);
	_loading->loadImage("Ÿ��_�ǰ�", "tower_beHit.163.244.bmp", 163 / 1.6, 244 / 1.6);
	_loading->loadImage("Ÿ��_��_�ǰ�", "tower_enemy_beHit.160.220.bmp", 160 / 1.6, 220 / 1.6);



	_loading->loadFrameImage("�����̹���1", "numSprite.bmp", 360, 42, 10, 1);

	//===========�̴ϸ�======================



	//=======================================



	//ü�¹�
	_loading->loadImage("ü�¹�", "PlayerprogressBarFront.bmp", 50, 6);
	_loading->loadImage("ü�¹�_��", "progressBarFront.bmp", 50, 6);
	_loading->loadImage("ü�¹�_���", "progressBarBack.bmp", 50, 6);
	
	//ȭ��
	_loading->loadImage("ȭ��", "Arrow.142.40.bmp", 52, 16);
	_loading->loadImage("ȭ��_��", "Arrow_enemy.76.34.bmp", 52, 16);
	_loading->loadImage("��Ʈ", "bolt.124.62.bmp", 62, 20);
	_loading->loadImage("��Ʈ_��", "bolt_enemy.139.71.bmp", 62, 20);
	_loading->loadImage("������", "SlashingEffect.156.158.bmp", 78, 79);
	_loading->loadImage("������_��", "SlashingEffect_enemy.156.158.bmp", 78, 79);

	//����
	_loading->loadImage("����Į", "Weapon_boss.1200.169.bmp", 300, 42);
	_loading->loadImage("����Į_��", "boss_weapon.1300.500.bmp", 325, 125);
	_loading->loadImage("Į", "Weapon #3426.bmp", 140, 16);
	_loading->loadImage("Į_��", "Sword_enemy.900.102.bmp", 140, 16);
	_loading->loadImage("Ȱ", "Bow.80.128.bmp", 20, 36);
	_loading->loadImage("Ȱ_��", "bow_enemy.300.58.bmp", 75, 15);
	_loading->loadImage("������", "������.300.52.bmp", 80, 13);
	_loading->loadImage("������_��", "������_enemy.200.52.bmp", 50, 13);

	//����
	_loading->loadImage("�����_����", "hero_die.256.311.bmp", 311 / 2, 256 / 2);
	_loading->loadImage("������_����", "worrior_die.314.285.bmp", 314 / 4, 285 / 4);
	_loading->loadImage("��ó_����", "archer_die.251.258.bmp", 258 / 3.6, 251 / 3.6);
	_loading->loadImage("������_����", "magician_die.256.259.bmp", 259 / 3.6, 256 / 3.6);
	_loading->loadImage("�����_��_����", "hero_enemy_die.238.270.bmp", 270 / 2, 238 / 2);
	_loading->loadImage("������_��_����", "worrior_enemy_die.286.269.bmp", 269 / 4, 286 / 4);
	_loading->loadImage("��ó_��_����", "archer_enemy_die.248.247.bmp", 247 / 3.6, 248 / 3.6);
	_loading->loadImage("������_��_����", "magician_enemy_die.243.273.bmp", 273 / 3.6, 243 / 3.6);

	//_loading->loadImage("�ɽ�", "castle.397.484.bmp", 397 / 1.4, 484 / 1.4);
	//_loading->loadImage("�ɽ�_��", "castle_enemy.423.445.bmp", 423 / 1.3, 445 / 1.3);
	//_loading->loadImage("Ÿ��", "tower.163.244.bmp", 163 / 1.6, 244 / 1.6);
	//_loading->loadImage("Ÿ��_��", "tower_enemy.160.220.bmp", 160 / 1.6, 220 / 1.6);

//================================================================================================================



	_loading->loadFrameImage("����2", "����2.bmp", 360, 42, 10, 1, true, RGB(255, 0, 255));


	{
		_loading->loadImage("f0", "cat/Frame0.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f1", "cat/Frame1.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f2", "cat/Frame2.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f3", "cat/Frame3.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f4", "cat/Frame4.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f5", "cat/Frame5.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f6", "cat/Frame6.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f7", "cat/Frame7.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f8", "cat/Frame8.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f9", "cat/Frame9.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f10", "cat/Frame10.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f11", "cat/Frame11.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f12", "cat/Frame12.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f13", "cat/Frame13.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f14", "cat/Frame14.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f15", "cat/Frame15.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f16", "cat/Frame16.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f17", "cat/Frame17.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f18", "cat/Frame18.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f19", "cat/Frame19.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f20", "cat/Frame20.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f21", "cat/Frame21.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f22", "cat/Frame22.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f23", "cat/Frame23.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f24", "cat/Frame24.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f25", "cat/Frame25.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f26", "cat/Frame26.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f27", "cat/Frame27.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f28", "cat/Frame28.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f29", "cat/Frame29.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f30", "cat/Frame30.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f31", "cat/Frame31.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f32", "cat/Frame32.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f33", "cat/Frame33.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f34", "cat/Frame34.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f35", "cat/Frame35.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f36", "cat/Frame36.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f37", "cat/Frame37.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f38", "cat/Frame38.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f39", "cat/Frame39.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f40", "cat/Frame40.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f41", "cat/Frame41.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f42", "cat/Frame42.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f43", "cat/Frame43.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f44", "cat/Frame44.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f45", "cat/Frame45.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f46", "cat/Frame46.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f47", "cat/Frame47.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f48", "cat/Frame48.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f49", "cat/Frame49.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f50", "cat/Frame50.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f51", "cat/Frame51.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f52", "cat/Frame52.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f53", "cat/Frame53.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f54", "cat/Frame54.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f55", "cat/Frame55.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f56", "cat/Frame56.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f57", "cat/Frame57.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f58", "cat/Frame58.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f59", "cat/Frame59.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f60", "cat/Frame60.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f61", "cat/Frame61.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f62", "cat/Frame62.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f63", "cat/Frame63.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f64", "cat/Frame64.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f65", "cat/Frame65.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f66", "cat/Frame66.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f67", "cat/Frame67.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f68", "cat/Frame68.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f69", "cat/Frame69.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f70", "cat/Frame70.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f71", "cat/Frame71.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f72", "cat/Frame72.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f73", "cat/Frame73.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f74", "cat/Frame74.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f75", "cat/Frame75.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f76", "cat/Frame76.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f77", "cat/Frame77.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f78", "cat/Frame78.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f79", "cat/Frame79.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f80", "cat/Frame80.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f81", "cat/Frame81.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f82", "cat/Frame82.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f83", "cat/Frame83.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f84", "cat/Frame84.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f85", "cat/Frame85.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f86", "cat/Frame86.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f87", "cat/Frame87.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f88", "cat/Frame88.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f89", "cat/Frame89.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f90", "cat/Frame90.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f91", "cat/Frame91.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f92", "cat/Frame92.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f93", "cat/Frame93.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f94", "cat/Frame94.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f95", "cat/Frame95.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f96", "cat/Frame96.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f97", "cat/Frame97.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f98", "cat/Frame98.bmp", 250 * 1.5, 318 * 1.5);
		_loading->loadImage("f99", "cat/Frame99.bmp", 250 * 1.5, 318 * 1.5);
	}

	//�ε� ������


	//================================================================================================================

	_loading->loadImage("Micon_Cassle", "Shop/Shop_Micon_Cassle.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_Tower", "Shop/Shop_Micon_Tower.bmp", 40, 40, true, RGB(255, 0, 255));

	//�κ� �̹���
	_loading->loadImage("bg", "lobby_bg.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("popup", "popup.bmp", 180, 100, true, RGB(255, 0, 255));
	_loading->loadFrameImage("hero_lobby", "hero_lobby.bmp", 6270 / 1.24, 630 / 1.24, 11, 1);
	_loading->loadImage("setting", "����.bmp", 36, 36, true, RGB(255, 0, 255));
	_loading->loadImage("exit", "����.bmp", 36, 36, true, RGB(255, 0, 255));
	_loading->loadImage("goldbar", "�ݹ�.bmp", 170, 36, true, RGB(255, 0, 255));
	_loading->loadImage("window", "������.bmp", 370, 290, true, RGB(255, 0, 255));
	_loading->loadImage("sound", "����.bmp", 72, 72, true, RGB(255, 0, 255));
	_loading->loadImage("ex", "����.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadFrameImage("onoff", "onoff.bmp", 176, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("shop", "shop.bmp", 160, 80, true, RGB(255, 0, 255));
	_loading->loadImage("upgrade", "upgrade.bmp", 160, 80, true, RGB(255, 0, 255));
	_loading->loadImage("box", "box.bmp", WINSIZEX, 50);
	_loading->loadImage("��", "��.bmp", 33, 200, true, RGB(255, 0, 255));
	_loading->loadImage("st", "stage.bmp", 160, 80, true, RGB(255, 0, 255));

	//����â �̹���
	_loading->loadImage("button", "��ư.bmp", 100, 80, true, RGB(255, 0, 255));
	_loading->loadFrameImage("speed", "speed.bmp", 140, 56, 3, true, RGB(255, 0, 255));
	_loading->loadImage("coin", "����.bmp", 150, 150, true, RGB(255, 0, 255));
	_loading->loadImage("end", "end.bmp", 370, 290, true, RGB(255, 0, 255));



	//������ų �̹���
	_loading->loadFrameImage("��", "��2.bmp", 2496, 108, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��", "��.bmp", 640, 176, 4, 1, true, RGB(255, 0, 255));

	//stageMap �̹���
	_loading->loadImage("table", "table.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("stage_bg", "stage_bg.bmp", ((WINSIZEX - 135)) * 7, (WINSIZEY - 180), 7, 1, true, RGB(255, 0, 255));
	_loading->loadImage("alpha", "alpha.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadImage("stage1", "��������.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadImage("stage2", "��������2.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadImage("stage3", "��������3.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadImage("stage4", "��������4.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadImage("stage5", "��������5.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadFrameImage("stage_num", "stage_num.bmp", 235, 48, 5, 1, true, RGB(255, 0, 255));
	_loading->loadImage("back", "back.bmp", 36, 36, true, RGB(255, 0, 255));
	_loading->loadImage("lock", "lock.bmp", 47, 48, true, RGB(255, 0, 255));

	//Ÿ��Ʋ �� �̹���
	_loading->loadImage("title_bg", "title_bg.bmp", WINSIZEX, WINSIZEY);
	//_loading->loadImage("monster", "monster.bmp", WINSIZEX + 500, -40, WINSIZEX*0.83, WINSIZEY*1.1, true, RGB(255, 0, 255));
	_loading->loadImage("monster", "monster.bmp", WINSIZEX + 500, 000, 954 / 1.09, 653 / 1.09, true, RGB(255, 0, 255));
	//_loading->loadImage("hero", "hero.bmp", -WINSIZEX, 50, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("hero", "hero.bmp", -WINSIZEX, 100, 908 / 1.2, 639 / 1.2, true, RGB(255, 0, 255));
	_loading->loadImage("start", "start.bmp", WINSIZEX, WINSIZEY, 204 / 1.2, 138 / 1.2, true, RGB(255, 0, 255));
	_loading->loadImage("title", "title.bmp", 243 * 1.4, 109 * 1.4, true, RGB(255, 0, 255));

	//================================================================================================================


	_loading->loadImage("���� ��ũ��", "Shop/Shop_ShopScroll.bmp", 2000, 200);							//��ũ�� ��׶��� �̹���
	_loading->loadImage("�׽�Ʈ", "Shop/Shop_ShopScroll.bmp", 800, 50);
	_loading->loadImage("ȭ��ǥ", "Shop/Shop_StatUp.bmp", 25, 21, true, RGB(255, 0, 255));				//���ݾ� �����ϴ� ȭ��ǥ �̹���
	_loading->loadImage("Yes", "Shop/Shop_Yes.bmp", 80, 40, true, RGB(255, 0, 255));					//���׷��̵�or���� Yes
	_loading->loadImage("No", "Shop/Shop_no.bmp", 80, 40, true, RGB(255, 0, 255));						//���׷��̵�or���� No
	_loading->loadImage("Pop_Up", "Shop/Shop_PopUp.bmp", 300, 200, true, RGB(255, 0, 255));				//�˾�â
	_loading->loadImage("Discription", "Shop/Shop_Discription.bmp", 800, 400, true, RGB(255, 0, 255));	//��ũ���� 
	_loading->loadImage("Sign", "Shop/Shop_Buy.bmp", 222 / 2, 222 / 2, true, RGB(255, 0, 255));			//����or���׷��̵� �� �̹���
	_loading->loadImage("Gold", "Shop/Shop_Gold_Icon.bmp", 238 / 12, 269 / 12, true, RGB(255, 0, 255)); //��� ������
	_loading->loadImage("Price", "Shop/Shop_Price.bmp", 163 * 7 / 8, 33 * 7 / 8);						//����ϰ� ���� â �������ִ� �̹���
	_loading->loadImage("Back", "Shop/Icon_Scene_Back.bmp", 36, 36);
	_loading->loadImage("Player_Gold", "Shop/Shop_Show_Player_Gold.bmp", 170, 36, true, RGB(255, 0, 255));


	_loading->loadImage("Unit_Info", "Shop/Shop_Unit_Info.bmp", 119, 48, true, RGB(255, 0, 255));		//���� ���׷��̵�â���� ��ȯ 
	_loading->loadImage("Object_Info", "Shop/Shop_Object_Info.bmp", 119, 48, true, RGB(255, 0, 255));	//������Ʈ ���׷��̵�â���� ��ȯ


	_loading->loadImage("Upgrade_BG", "Shop/Shop_ShopBG.bmp", 820, 450);								//���׷��̵� ��� �̹���
	_loading->loadImage("Shop_BG", "Shop/Shop_Shop_Bg.bmp", 820, 450);									//���� ��� �̹���


	_loading->loadImage("Upgrade_Load", "Shop/Shop_Go_Upgrade.bmp", 146, 80, true, RGB(255, 0, 255));	//����->���׷��̵� 
	_loading->loadImage("Shop_Load", "Shop/Shop_Go_Shop.bmp", 146, 80, true, RGB(255, 0, 255));			//���׷��̵�->���� 

	//ĳ���� �̹���
	_loading->loadImage("Icon_Warrior", "Shop/Shop_Icon_Warrior.bmp", 200, 200);						//������ ������ �̹���	
	_loading->loadImage("Icon_Archor", "Shop/Shop_Icon_Archor.bmp", 200, 200);							//���� ������ �̹���
	_loading->loadImage("Icon_Mage", "Shop/Shop_Icon_Mage.bmp", 200, 200);								//������ ������ �̹���
	_loading->loadImage("Icon_Hero", "Shop//Shop_Icon_Hero.bmp", 200, 200);								//���� ������ �̹���

	_loading->loadImage("Micon_Warrior", "Shop/Shop_MIcon_Worrior.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_Archor", "Shop/Shop_MIcon_Archor.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_Mage", "Shop/Shop_MIcon_Mage.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_Hero", "Shop/Shop_MIcon_Hero.bmp", 40, 40, true, RGB(255, 0, 255));

	//������Ʈ �̹���
	_loading->loadImage("Icon_Tower", "Shop/Shop_Icon_Tower.bmp", 200, 200);							//Ÿ�� ������ �̹���
	_loading->loadImage("Icon_Cassle", "Shop/Shop_Icon_Cassle.bmp", 200, 200);							//�� ������ �̹��� 



	//

	_loading->loadImage("Micon_Meteor2", "Shop/Shop_Icon_Meteor_Mini.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_BlackHole2", "Shop/Shop_Icon_BlackHole_Mini.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_Heal2", "Shop/Shop_Icon_Heal_Mini.bmp", 60, 60, true, RGB(255, 0, 255));


	//================================================================================================================



	_loading->loadFrameImage("BlackHole2", "Skill_BlackHole.bmp", 1360, 130, 15, 1);

	_loading->loadFrameImage("BlackHole", "Skill_BlackHole2.bmp", 1360, 130, 15, 1);


//================================================================================================================








}

/* < ���⿡ �� ���� ����� ���� �̸� �ε� �صδ� ���Դϴ�. >*/
void loadingScene::loadingSound()
{
	

	//���� ��¼Ҹ�
	SOUNDMANAGER->addSound("p1", "test.wav");
	SOUNDMANAGER->addSound("����", "unequip.mp3", false, false);
	SOUNDMANAGER->addSound("������", "������2.mp3", false, false);
	SOUNDMANAGER->addSound("Buy_Skill", "Shop_Sound_Buy_Skill.mp3");
	SOUNDMANAGER->addSound("Buy_Upgrade", "Shop_Sound_Buy_Upgrade.mp3");
	SOUNDMANAGER->addSound("����", "����.mp3", false, false);
	SOUNDMANAGER->addSound("��ư", "��ư.mp3", false, false);
	
	SOUNDMANAGER->addSound("���ݻ���_����", "Hero_Attack.mp3", false, false);
	//SOUNDMANAGER->addSound("���ݻ���_������", "Mage_Attack.mp3", false, false);
	SOUNDMANAGER->addSound("����_������", "������.wav", false, false);
	SOUNDMANAGER->addSound("���ݻ���_������", "Worrior_Attack.mp3", false, false);
	SOUNDMANAGER->addSound("���ݻ���_����", "Archor_Attack.mp3", false, false);
	SOUNDMANAGER->addSound("����_���׿�", "Meteor.mp3", false, false);
	SOUNDMANAGER->addSound("��_����", "heal.mp3", false, false);
	SOUNDMANAGER->addSound("��Ȧ_����", "��Ż2.wav", false, false);
	SOUNDMANAGER->addSound("��Ȧ_�ٶ�", "��Ż_�ٶ�.wav", false, false);

	//��������
	SOUNDMANAGER->addSound("����_��", "348270__metekavruk__oops2.ogg", false, false); //�� ����
	SOUNDMANAGER->addSound("����_�Ʊ�", "76958__michel88__deathd.wav", false, false); //�Ʊ� ����
	SOUNDMANAGER->addSound("�ǰ�", "beHit.wav", false, false); //�ǰ�
	
	//��� â
	SOUNDMANAGER->addSound("���_�¸�", "victory.mp3", true, true); //�¸� ���
	SOUNDMANAGER->addSound("���_�¸�2", "victory2.wav", true, true); //�¸� ���

	//���
	SOUNDMANAGER->addSound("���_Ÿ��Ʋ", "bgm_title.mp3", true, true); //�Ʊ� ����
	SOUNDMANAGER->addSound("���_�κ�", "bgm_lobby.mp3", true, true); //�Ʊ� ����
	SOUNDMANAGER->addSound("���_��������", "bgm_stage.wma", true, true); //�Ʊ� ����

	
	
}
