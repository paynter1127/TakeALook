#include "stdafx.h"
#include "stage.h"



HRESULT stage::init()
{
	//������������
	stage1RECT = RectMake(0, 0, 1200, 500);

	//���� �����
	for (int i = 0; i < 3; i++) line[i] = RectMake(stage1RECT.left + 100, 330 + i * 46, 1000, 36);
	//����� �ڽ� �ʱ�ȭ
	for (int i = 0; i < 4; i++) isDrag[i] = false;
	sumNail[0] = RectMakeCenter(250, 544, 90, 90); //255, 544
	sumNail[1] = RectMakeCenter(344, 558, 60, 60); //255, 544
	sumNail[2] = RectMakeCenter(426, 558, 60, 60); //255, 544
	sumNail[3] = RectMakeCenter(506, 558, 60, 60); //255, 544
	sumNailSkill[0] = RectMakeCenter(594, 558, 70, 70); //255, 544
	sumNailSkill[1] = RectMakeCenter(678, 558, 70, 70); //255, 544
	sumNailSkill[2] = RectMakeCenter(756, 558, 70, 70); //255, 544

	end = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 370, 290);

	_character = new character;
	_character->init();

	_stageInfo = new stageInfo;
	_stageInfo->init();

	//ī�޶� ����
	camara_rc = RectMake(_ptMouse.x - 10, _ptMouse.y, 20, 10);

	//���� ������ ����
	field_player.resize(3);
	field_enemy.resize(3);

	//hp�� ������ ����
	ZeroMemory(&init_hpBar, sizeof(tagProgressBar));
	init_hpBar.hpBar = new progressBar;
	init_hpBar.hpBar->init("PlayerprogressBarFront", "progressBarBack", 0, 0, 50, 6);
	field_player_hpBar.resize(3);
	field_enemy_hpBar.resize(3);


	//���� �̹��� ���� �ʱ�ȭ
	{
		hero_die.img = IMAGEMANAGER->findImage("�����_����");
		hero_die.count = 200;
		hero_die.isDie = false;
		worrior_die.img = IMAGEMANAGER->findImage("������_����");
		worrior_die.count = 200;
		worrior_die.isDie = false;
		archer_die.img = IMAGEMANAGER->findImage("��ó_����");
		archer_die.count = 200;
		archer_die.isDie = false;
		magician_die.img = IMAGEMANAGER->findImage("������_����");
		magician_die.count = 200;
		magician_die.isDie = false;
		tower_die.img = IMAGEMANAGER->findImage("��������");
		tower_die.count = 200;
		tower_die.isDie = false;
		castle_die.img = IMAGEMANAGER->findImage("��������");
		castle_die.count = 200;
		castle_die.isDie = false;

		hero_enemy_die.img = IMAGEMANAGER->findImage("�����_��_����");
		hero_enemy_die.count = 200;
		hero_enemy_die.isDie = false;
		worrior_enemy_die.img = IMAGEMANAGER->findImage("������_��_����");
		worrior_enemy_die.count = 200;
		worrior_enemy_die.isDie = false;
		archer_enemy_die.img = IMAGEMANAGER->findImage("��ó_��_����");
		archer_enemy_die.count = 200;
		archer_enemy_die.isDie = false;
		magician_enemy_die.img = IMAGEMANAGER->findImage("������_��_����");
		magician_enemy_die.count = 200;
		magician_enemy_die.isDie = false;
		tower_enemy_die.img = IMAGEMANAGER->findImage("��������");
		tower_enemy_die.count = 200;
		tower_enemy_die.isDie = false;
		castle_enemy_die.img = IMAGEMANAGER->findImage("��������");
		castle_enemy_die.count = 200;
		castle_enemy_die.isDie = false;
	}

	//���� ��Ʈ �����̳� ������ ����
	field_player_die.resize(3);
	field_enemy_die.resize(3);


	summon_castle();

	playerfood = 8;
	enemyfood = 8;

	bcount = 0;

	_userSkill = new userSKillCombine;
	_userSkill->init();

	//SOUNDMANAGER->play("p1");

	miniMap = RectMakeCenter(WINSIZEX / 2, 30, 283, 100);
	isplay = true;
	getgold = RND->range(-500, 500) + 5000;


	

	return S_OK;
}

void stage::release()
{
	_character->release();
	SAFE_DELETE(_character);

	_stageInfo->release();
	SAFE_DELETE(_stageInfo);

	init_hpBar.hpBar->release();
	SAFE_DELETE(init_hpBar.hpBar);
}

void stage::update()
{
	//SOUNDMANAGER->play("���_��������", 0.1f);

	if (isplay == true)
	{
		
		_character->count++;

		//ī�޶�
		this->camera();

		//�ķ�
		this->food(_character->count);

		//�����Լ�
		for (int c = 0; c < 3; c++) this->removeplayer(c);
		for (int c = 0; c < 3; c++) this->removeEnemy(c);

		//��ȯ�Լ�
		this->summon_hero();
		this->summon_worrior();
		this->summon_archer();
		this->summon_magician();
		this->summon_AI();

		//�� �̵� �Լ�
		for (int i = 0; i < 3; i++) this->runPlayer(i);
		for (int i = 0; i < 3; i++) this->runEnemy(i);

		//�� ���� �浹 �� => ���� ���·� ����
		for (int i = 1; i < 3; i++) this->bumpCastle(i);
		for (int i = 0; i < 3; i++) this->bump(i);

		//ü�¹� ������Ʈ
		this->updateHpBar();

		//���� ������Ʈ
		this->die();


		//===========================================






		count++;


		_userSkill->update();

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_userSkill->_Meteor->icon_Meteor, _ptMouse))
			{
				//if (playerInfo::getSingleton()->num_skill2 > 0) 
				_userSkill->_Meteor->drag_Meteor = true;
			}

			if (PtInRect(&_userSkill->_Heal->icon_Meteor, _ptMouse))
			{
				//if (playerInfo::getSingleton()->num_skill2 > 0) 
				_userSkill->_Heal->drag_Meteor = true;
			}
			if (PtInRect(&_userSkill->_BlackHole->icon_Meteor, _ptMouse))
			{
				//if (playerInfo::getSingleton()->num_skill2 > 0) 
				_userSkill->_BlackHole->now = PICK;
			}
			for (int i = 0; i < 3; i++)
			{
				if (PtInRect(&line[i], _ptMouse) && _userSkill->_BlackHole->now == EAT)
				{
					exline = i;
					bcount = count + 500;
					//_userSkill->_BlackHole->now = EAT;
					//playerInfo::getSingleton()->num_skill2 -= 1;

					_userSkill->_BlackHole->now = EXIT;
					_userSkill->_BlackHole->exit = RectMakeCenter(_ptMouse.x, line[i].bottom-48, 100, 100);
					SOUNDMANAGER->play("��Ȧ_�ٶ�");
					break;
				}
			}
		}
		if (bcount == count)
		{
			SOUNDMANAGER->stop("��Ȧ_�ٶ�");
			_userSkill->_BlackHole->now = NOT;
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			RECT NON;
			RECT HEAL;
			for (int i = 0; i < 3; i++)
			{
				if (PtInRect(&line[i], _ptMouse) && _userSkill->_Meteor->drag_Meteor == true)
				{
					//playerInfo::getSingleton()->num_skill2 -= 1;

					savePlayer();

					_userSkill->_Meteor->Use_Meteor = true;
					_userSkill->_Meteor->drag_Meteor = false;

				}

				if (PtInRect(&line[i], _ptMouse) && _userSkill->_Heal->drag_Meteor == true)
				{
					//playerInfo::getSingleton()->num_skill2 -= 1;

					savePlayer();

					_userSkill->_Heal->Use_Meteor = true;
					_userSkill->_Heal->drag_Meteor = false;
					_userSkill->_Heal->Damage = RectMakeCenter(_ptMouse.x, _ptMouse.y, 416, 162);
					hcount = count + 400;
				}
				if (PtInRect(&line[i], _ptMouse) && _userSkill->_BlackHole->now == PICK)
				{
					//playerInfo::getSingleton()->num_skill2 -= 1;

					savePlayer();

					//��Ʈ ��ġ�����ϼ�(DAMAGE, exit)
					_userSkill->_BlackHole->Damage = RectMakeCenter(_ptMouse.x, line[i].bottom-50, 100, 100);
					_userSkill->_BlackHole->now = EAT;

				}

			}
		}
		if (_userSkill->_BlackHole->now == EXIT)
		{
			for (int i = 0; i < field_enemy.size(); i++)
			{
				for (int j = 0; j < field_enemy[i].size(); j++)
				{
					RECT rc;
					tagCharacter a;
					if (IntersectRect(&rc, &_userSkill->_BlackHole->Damage, &field_enemy[i][j].rc))
					{
						SOUNDMANAGER->play("��Ȧ_����");
						a = field_enemy[i][j];
						a.x = _userSkill->_BlackHole->exit.left;
						a.y = line[exline].top;
						a.rc = RectMakeCenter(a.x, a.y, 80, 80);
						field_enemy[i].erase(field_enemy[i].begin() + j);
						field_enemy_hpBar[i].erase(field_enemy_hpBar[i].begin() + j);
						field_enemy_die[i].erase(field_enemy_die[i].begin() + j);
						j--;


						field_enemy[exline].push_back(a);
						hpBar(exline, false, a.sort);
						if (a.sort == WORRIOR)
							field_player_die[exline].push_back(worrior_die);
						else if (a.sort == MAGICIAN)
							field_player_die[exline].push_back(magician_die);
						else if (a.sort == ARCHER)
							field_player_die[exline].push_back(archer_die);
						else if (a.sort == BOSS)
							field_player_die[exline].push_back(hero_enemy_die);
						else if (a.sort == CASTLE)
							field_player_die[exline].push_back(castle_die);
						else if (a.sort == TOWER)
							field_player_die[exline].push_back(tower_die);


						//field_enemy[i][j].rc.left = (_userSkill->_BlackHole->Damage.left+ _userSkill->_BlackHole->Damage.right)/2;
						//field_enemy[i][j].state = ATTACK;
					}
				}
			}
		}

		RECT NON;
		RECT HEAL;
		for (int i = 0; i < field_enemy.size(); i++)
		{
			for (int j = 0; j < field_enemy[i].size(); j++)
			{
				if (IntersectRect(&NON, &_userSkill->_Meteor->Damage, &field_enemy[i][j].rc))
				{
					field_enemy[i][j].hp -= 0.005f;

				}
			}
		}
		if (hcount == count)
		{
			_userSkill->_Heal->Use_Meteor = false;
		}

		if (_userSkill->_Heal->Use_Meteor == true)
		{
			if (count % 7 == 0)
			{
				for (int i = 0; i < field_player.size(); i++)
				{
					for (int j = 0; j < field_player[i].size(); j++)
					{
						if (IntersectRect(&HEAL, &_userSkill->_Heal->Damage, &field_player[i][j].rc))
						{
							field_player[i][j].hp += 1.0f;
							if (field_player[i][j].hp > field_player[i][j].maxhp)
								field_player[i][j].hp = field_player[i][j].maxhp;
						}
					}
				}
			}
		}

		if (field_enemy[0][0].hp <= 0)
		{
			SOUNDMANAGER->stop("���_��������");
			SOUNDMANAGER->play("���_�¸�", 0.5f);
			SOUNDMANAGER->play("���_�¸�2", 1);

			isplay = false;
		}



	}
	if (isplay == false)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			playerInfo::getSingleton()->gold += getgold;

			if (playerInfo::getSingleton()->lv_stage == 0)
				playerInfo::getSingleton()->lv_stage = 1;
			else if (playerInfo::getSingleton()->lv_stage == 1)
				playerInfo::getSingleton()->lv_stage = 4;
			else if (playerInfo::getSingleton()->lv_stage == 4)
				playerInfo::getSingleton()->lv_stage = 5;


			//SOUNDMANAGER->stop("p1");
			savePlayer();
			SOUNDMANAGER->stop("���_�¸�");
			SOUNDMANAGER->stop("���_�¸�2");
			SOUNDMANAGER->play("��ư");
			
			SOUNDMANAGER->play("���_�κ�", 0.2f);
			SCENEMANAGER->loadScene("stageMap");


		}
	}



	//============================================



}


void stage::render()
{
	//����̹��� ����
	
	if ((playerInfo::getSingleton()->lv_stage) == 0)
	{
		IMAGEMANAGER->findImage("���1_2")->render(getMemDC());
		_stageInfo->chapter1_stage1.img->render(getMemDC(), 0, -80);
	}
	if ((playerInfo::getSingleton()->lv_stage) == 1)	_stageInfo->chapter1_stage2.img->render(getMemDC());
	if ((playerInfo::getSingleton()->lv_stage) == 4)	_stageInfo->chapter1_stage5.img->render(getMemDC());
	if ((playerInfo::getSingleton()->lv_stage) == 5)	_stageInfo->chapter2_stage1.img->render(getMemDC());
		//IMAGEMANAGER->render("���5", getMemDC(), 0, 0);
	IMAGEMANAGER->render("����", getMemDC(), stage1RECT.left, stage1RECT.top);
	IMAGEMANAGER->render("�ΰ���UI", getMemDC(), 0, 0);

	//SOUNDMANAGER->play("���_��������", 0.1f);

	if (isplay == false)
	{
		
		IMAGEMANAGER->findImage("end")->render(getMemDC(), end.left, end.top);

		imagescaleNum("����2", getMemDC(), WINSIZEX/2+75,WINSIZEY/2-30, getgold, 14, 0.45);
	}




	if (isplay == true)
	{
		char skill[128];

		textOutFontNum(getMemDC(), sumNailSkill[0].left + 50, sumNailSkill[0].top - 20, playerInfo::getSingleton()->num_skill2, 20, RGB(250, 200, 0));	//�߰�
		textOutFontNum(getMemDC(), sumNailSkill[1].left + 50, sumNailSkill[1].top - 20, playerInfo::getSingleton()->num_skill1, 20, RGB(250, 200, 0));	//�߰�
		textOutFontNum(getMemDC(), sumNailSkill[2].left + 50, sumNailSkill[2].top - 20, playerInfo::getSingleton()->num_skill3, 20, RGB(250, 200, 0));	//�߰�
		textOutFont(getMemDC(), sumNailSkill[0].left + 8, sumNailSkill[0].top - 20, "���� : ", 20, RGB(250, 200, 0));
		textOutFont(getMemDC(), sumNailSkill[1].left + 8, sumNailSkill[1].top - 20, "���� : ", 20, RGB(250, 200, 0));
		textOutFont(getMemDC(), sumNailSkill[2].left + 8, sumNailSkill[2].top - 20, "���� : ", 20, RGB(250, 200, 0));

		textOutFont(getMemDC(), sumNailSkill[0].left - 246, sumNailSkill[0].top - 20, "Cost: 3    Cost: 3    Cost: 3", 20, RGB(250, 200, 0));

		//���� �� ĳ���� ����
		{
			//���� ���� ����
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < field_enemy[j].size(); i++)
				{
					//����Ʈ ����
					if (field_enemy[j][i].fire)
					{
						//���� ����Ʈ ����
						field_enemy[j][i].img_att->render(getMemDC(), field_enemy[j][i].rc_att.left, field_enemy[j][i].rc_att.top);
					}

					//���� ��� ����
					if (field_enemy[j][i].fire_motion)
					{
						//���� ����
						if (_character->count % 1 == 0)
						{
							if (field_enemy[j][i].sort == BOSS) //���� ����
							{
								if (field_enemy[j][i].angle < 0)
								{
									field_enemy[j][i].isDown = true; //�Ʒ��� ������ 
									field_enemy[j][i].fire = false;
									field_enemy[j][i].angle = 0;
								}
								if (field_enemy[j][i].angle > ((PI * 5) / 8)) field_enemy[j][i].isDown = false; //���� �÷���
								if (field_enemy[j][i].isDown) field_enemy[j][i].angle += PI / 4; //�Ʒ��� ȸ�� ����
								if (!field_enemy[j][i].isDown) field_enemy[j][i].angle -= PI / 64; //���� �ø��� ����
							}
							else
							{
								if (field_enemy[j][i].angle < 0)
								{
									field_enemy[j][i].isDown = true; //�Ʒ��� ������ 
									field_enemy[j][i].fire = false;
									field_enemy[j][i].angle = 0;
								}
								if (field_enemy[j][i].angle > ((PI * 5) / 8)) field_enemy[j][i].isDown = false; //���� �÷���
								if (field_enemy[j][i].isDown) field_enemy[j][i].angle += PI / 4; //�Ʒ��� ȸ�� ����
								if (!field_enemy[j][i].isDown) field_enemy[j][i].angle -= PI / 64; //���� �ø��� ����
							}
						}
						if (field_enemy[j][i].sort == BOSS) //ȸ�� ���� ����
						{
							field_enemy[j][i].img_weapon->rotateRender(getMemDC(), field_enemy[j][i].rc.left + 48, field_enemy[j][i].rc.top + 106, -((PI * 3) / 8) + field_enemy[j][i].angle);
						}
						else if (field_enemy[j][i].sort == ARCHER)
						{
							field_enemy[j][i].img_weapon->rotateRender(getMemDC(), field_enemy[j][i].rc.left + 24, field_enemy[j][i].rc.top + 50, -((PI * 3) / 8) + field_enemy[j][i].angle);
						}
						else if (field_enemy[j][i].sort == MAGICIAN)
						{
							field_enemy[j][i].img_weapon->rotateRender(getMemDC(), field_enemy[j][i].rc.left + 18, field_enemy[j][i].rc.top + 60, -((PI * 3) / 8) + field_enemy[j][i].angle);
						}
						else
						{
							field_enemy[j][i].img_weapon->rotateRender(getMemDC(), field_enemy[j][i].rc.left + 20, field_enemy[j][i].rc.top + 50, -((PI * 5) / 8) + field_enemy[j][i].angle);
						}
					}
					else//���� �ʱ� ����
					{
						if (field_enemy[j][i].sort == BOSS) //���� ����
						{
							field_enemy[j][i].img_weapon->rotateRender(getMemDC(), field_enemy[j][i].rc.left + 48, field_enemy[j][i].rc.top + 106, -((PI * 3) / 8) + 0);
						}
						else if (field_enemy[j][i].sort == ARCHER)
						{
							field_enemy[j][i].img_weapon->rotateRender(getMemDC(), field_enemy[j][i].rc.left + 24, field_enemy[j][i].rc.top + 50, -((PI * 3) / 8) + 0);
						}
						else if (field_enemy[j][i].sort == MAGICIAN)
						{
							field_enemy[j][i].img_weapon->rotateRender(getMemDC(), field_enemy[j][i].rc.left + 18, field_enemy[j][i].rc.top + 60, -((PI * 3) / 8) + 0);
						}
						else
						{
							field_enemy[j][i].img_weapon->rotateRender(getMemDC(), field_enemy[j][i].rc.left + 20, field_enemy[j][i].rc.top + 50, -((PI * 3) / 8) + 0);
						}
					}
					//ĳ���� �̹��� ����
					field_enemy[j][i].img->render(getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
				}
			}

			//�츮 ���� ����
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < field_player[j].size(); i++)
				{
					//����Ʈ ����
					if (field_player[j][i].fire) //���� �浹ü ����
					{
						//���� ����Ʈ ����
						field_player[j][i].img_att->render(getMemDC(), field_player[j][i].rc_att.left, field_player[j][i].rc_att.top);
					}

					//���� ��� ����
					if (field_player[j][i].fire_motion) //���� �浹ü ����
					{
						//���� ����
						if (_character->count % 1 == 0)
						{
							if (field_player[j][i].sort == ARCHER) //Ȱ ����
							{
								if (field_player[j][i].angle < 0)
								{
									field_player[j][i].isDown = true; //�Ʒ��� ������ 
									field_player[j][i].fire_motion = false;
									field_player[j][i].angle = 0;
								}
								if (field_player[j][i].angle > +((PI * 4) / 8)) field_player[j][i].isDown = false; //���� �÷���
								if (field_player[j][i].isDown) field_player[j][i].angle += PI / 64; //�Ʒ��� ȸ�� ����
								if (!field_player[j][i].isDown) field_player[j][i].angle -= PI / 4; //���� �ø��� ����
							}
							else if (field_player[j][i].sort == BOSS) //���� ����
							{
								if (field_player[j][i].angle > 0)
								{
									field_player[j][i].isDown = true; //�Ʒ��� ������ 
									field_player[j][i].fire = false;
									field_player[j][i].angle = 0;
								}
								if (field_player[j][i].angle < -((PI * 5) / 8)) field_player[j][i].isDown = false; //���� �÷���
								if (field_player[j][i].isDown) field_player[j][i].angle -= PI / 4; //�Ʒ��� ȸ�� ����
								if (!field_player[j][i].isDown) field_player[j][i].angle += PI / 64; //���� �ø��� ����
							}
							else //�⺻ ����
							{
								if (field_player[j][i].angle > 0)
								{
									field_player[j][i].isDown = true; //�Ʒ��� ������ 
									field_player[j][i].fire = false;
									field_player[j][i].angle = 0;
								}
								if (field_player[j][i].angle < -((PI * 5) / 8)) field_player[j][i].isDown = false; //���� �÷���
								if (field_player[j][i].isDown) field_player[j][i].angle -= PI / 4; //�Ʒ��� ȸ�� ����
								if (!field_player[j][i].isDown) field_player[j][i].angle += PI / 64; //���� �ø��� ����
							}
						}
						if (field_player[j][i].sort == ARCHER) //ȸ�� ����
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 48, field_player[j][i].rc.top + 56, -((PI * 3) / 8) + field_player[j][i].angle);
						}
						else if (field_player[j][i].sort == BOSS) //���� ����
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 86, field_player[j][i].rc.top + 116, ((PI * 5) / 8) + field_player[j][i].angle);
						}
						else
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 52, field_player[j][i].rc.top + 60, ((PI * 5) / 8) + field_player[j][i].angle);
						}
					}
					else//���� �ʱ� ����
					{
						if (field_player[j][i].sort == ARCHER)
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 48, field_player[j][i].rc.top + 56, -((PI * 3) / 8) + 0);
						}
						else if (field_player[j][i].sort == BOSS) //���� ����
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 86, field_player[j][i].rc.top + 116, ((PI * 3) / 8) + 0);
						}
						else
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 52, field_player[j][i].rc.top + 60, ((PI * 3) / 8) + 0);
						}
					}
					//ĳ���� �̹��� ����(��)
					field_player[j][i].img->render(getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
				}
			}
		}


		//�ǰ� ����Ʈ ����
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < field_player[j].size(); i++)
			{
				//�Ʊ�
				if (field_player[j][i].isHit)
				{
					switch (field_player[j][i].sort)
					{
					case BOSS:
						IMAGEMANAGER->render("�����_�ǰ�", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					case WORRIOR:
						IMAGEMANAGER->render("������_�ǰ�", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					case ARCHER:
						IMAGEMANAGER->render("��ó_�ǰ�", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					case MAGICIAN:
						IMAGEMANAGER->render("������_�ǰ�", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					case TOWER:
						IMAGEMANAGER->render("Ÿ��_�ǰ�", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					case CASTLE:
						IMAGEMANAGER->render("�ɽ�_�ǰ�", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					}
					field_player[j][i].isHit = false;
				}
			}
			//����
			for (int i = 0; i < field_enemy[j].size(); i++)
			{
				if (field_enemy[j][i].isHit)
				{
					switch (field_enemy[j][i].sort)
					{
					case BOSS:
						IMAGEMANAGER->render("�����_��_�ǰ�", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					case WORRIOR:
						IMAGEMANAGER->render("������_��_�ǰ�", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					case ARCHER:
						IMAGEMANAGER->render("��ó_��_�ǰ�", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					case MAGICIAN:
						IMAGEMANAGER->render("������_��_�ǰ�", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					case TOWER:
						IMAGEMANAGER->render("Ÿ��_��_�ǰ�", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					case CASTLE:
						IMAGEMANAGER->render("�ɽ�_��_�ǰ�", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					}
					field_enemy[j][i].isHit = false;
				}
			}
		}


		//ü�¹� ����
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < field_enemy_hpBar[j].size(); i++)
			{
				field_enemy_hpBar[j][i].hpBar->render();
			}
			for (int i = 0; i < field_player_hpBar[j].size(); i++)
			{
				field_player_hpBar[j][i].hpBar->render();
			}
		}



		//���� ��� ���� ó��
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < field_player_die[i].size(); j++)
			{
				if (field_player_die[i][j].isDie) field_player_die[i][j].img->alphaRender(getMemDC(), field_player_die[i][j].x, field_player_die[i][j].y, field_player_die[i][j].count);
			}
			for (int j = 0; j < field_enemy_die[i].size(); j++)
			{
				if (field_enemy_die[i][j].isDie) field_enemy_die[i][j].img->alphaRender(getMemDC(), field_enemy_die[i][j].x, field_enemy_die[i][j].y, field_enemy_die[i][j].count);
			}
		}


		//�Ʊ� Ǫ�� ����
		imageNum("����2", getMemDC(), 128, 524, playerfood, 32);

		// ��ȯ ��, ĳ���� �̹��� ���콺 �����Ϳ� ����
		{
			if (isDrag[0])
			{
				sumNail[0] = RectMakeCenter(_ptMouse.x, _ptMouse.y, 256 / 2, 311 / 2);
				IMAGEMANAGER->render("�����", getMemDC(), sumNail[0].left, sumNail[0].top);
				for (int i = 0; i < 3; i++)
				{
					if (PtInRect(&line[i], _ptMouse))
					{
						FrameRect(getMemDC(), line[i], RGB(255, 255, 0));
						if ((_character->count / 10) % 2 == 0) IMAGEMANAGER->alphaRender("�����", getMemDC(), line[i].left - 70, line[i].top - 140, 200);
					}
				}
			}
			if (isDrag[1])
			{
				sumNail[1] = RectMakeCenter(_ptMouse.x, _ptMouse.y, 80, 80);
				IMAGEMANAGER->render("������", getMemDC(), sumNail[1].left, sumNail[1].top);
				for (int i = 0; i < 3; i++)
				{
					if (PtInRect(&line[i], _ptMouse))
					{
						FrameRect(getMemDC(), line[i], RGB(255, 255, 0));
						if ((_character->count / 10) % 2 == 0) IMAGEMANAGER->alphaRender("������", getMemDC(), line[i].left - 40, line[i].top - 50, 200);
					}
				}
			}
			if (isDrag[2])
			{
				sumNail[2] = RectMakeCenter(_ptMouse.x, _ptMouse.y, 80, 80);
				IMAGEMANAGER->render("��ó", getMemDC(), sumNail[2].left, sumNail[2].top);
				for (int i = 0; i < 3; i++)
				{
					if (PtInRect(&line[i], _ptMouse))
					{
						FrameRect(getMemDC(), line[i], RGB(255, 255, 0));
						if ((_character->count / 10) % 2 == 0) IMAGEMANAGER->alphaRender("��ó", getMemDC(), line[i].left - 40, line[i].top - 50, 200);
					}
				}
			}
			if (isDrag[3])
			{
				sumNail[3] = RectMakeCenter(_ptMouse.x, _ptMouse.y, 80, 80);
				IMAGEMANAGER->render("������", getMemDC(), sumNail[3].left, sumNail[3].top);
				for (int i = 0; i < 3; i++)
				{
					if (PtInRect(&line[i], _ptMouse))
					{
						FrameRect(getMemDC(), line[i], RGB(255, 255, 0));
						if ((_character->count / 10) % 2 == 0) IMAGEMANAGER->alphaRender("������", getMemDC(), line[i].left - 40, line[i].top - 50, 200);
					}
				}
			}
		}







		//ĳ���� ���� 
		//for (int i = 0; i < field_player[0].size(); i++) FrameRect(getMemDC(), field_player[0][i].rc, RGB(0, 255, 255));
		//for (int i = 0; i < field_player[1].size(); i++) FrameRect(getMemDC(), field_player[1][i].rc, RGB(0, 255, 255));
		//for (int i = 0; i < field_player[2].size(); i++) FrameRect(getMemDC(), field_player[2][i].rc, RGB(0, 255, 255));
		//for (int i = 0; i < field_enemy[0].size(); i++) FrameRect(getMemDC(), field_enemy[0][i].rc, RGB(0, 255, 255));
		//for (int i = 0; i < field_enemy[1].size(); i++) FrameRect(getMemDC(), field_enemy[1][i].rc, RGB(0, 255, 255));
		//for (int i = 0; i < field_enemy[2].size(); i++) FrameRect(getMemDC(), field_enemy[2][i].rc, RGB(0, 255, 255));

		//���ݹ��� ����
		//for (int i = 0; i < field_player[0].size(); i++) FrameRect(getMemDC(), field_player[0][i].rc_attRange, RGB(255, 0, 0));
		//for (int i = 0; i < field_player[1].size(); i++) FrameRect(getMemDC(), field_player[1][i].rc_attRange, RGB(255, 0, 0));
		//for (int i = 0; i < field_player[2].size(); i++) FrameRect(getMemDC(), field_player[2][i].rc_attRange, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[0].size(); i++) FrameRect(getMemDC(), field_enemy[0][i].rc_attRange, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[1].size(); i++) FrameRect(getMemDC(), field_enemy[1][i].rc_attRange, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[2].size(); i++) FrameRect(getMemDC(), field_enemy[2][i].rc_attRange, RGB(255, 0, 0));

		//���� �浹ü ����
		//for (int i = 0; i < field_player[0].size(); i++) FrameRect(getMemDC(), field_player[0][i].rc_att, RGB(255, 0, 0));
		//for (int i = 0; i < field_player[1].size(); i++) FrameRect(getMemDC(), field_player[1][i].rc_att, RGB(255, 0, 0));
		//for (int i = 0; i < field_player[2].size(); i++) FrameRect(getMemDC(), field_player[2][i].rc_att, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[0].size(); i++) FrameRect(getMemDC(), field_enemy[0][i].rc_att, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[1].size(); i++) FrameRect(getMemDC(), field_enemy[1][i].rc_att, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[2].size(); i++) FrameRect(getMemDC(), field_enemy[2][i].rc_att, RGB(255, 0, 0));

		//����
		//for (int i = 0; i < 3; i++) FrameRect(getMemDC(), line[i], RGB(255, 255, 0));
		//for (int i = 0; i < 4; i++) FrameRect(getMemDC(), sumNail[i], RGB(0, 255, 255));
		//for (int i = 0; i < 3; i++) FrameRect(getMemDC(), sumNailSkill[i], RGB(0, 255, 255));

		//ī�޶� ��Ʈ
		//FrameRect(getMemDC(), camara_rc, RGB(0, 255, 255));



			//==================================================

		_userSkill->render();

		Rectangle(getMemDC(), miniMap);

		IMAGEMANAGER->scaleRender("����", getMemDC(), miniMap.left, miniMap.top, 0.2f);
		//IMAGEMANAGER->scaleRender("���.�̴ϸ�5", getMemDC(), miniMap.left, miniMap.top, 0.3f);




		//==================================�̴ϸ�================================================================
		//�߰��Ѱ�



		for (int i = 0; i < field_enemy.size(); i++)
		{
			for (int j = 0; j < field_enemy[i].size(); j++)
			{
				if (field_enemy[i][j].hp > 0)
				{
					if (i == 0 && j == 0)  field_enemy[i][j].img->scaleRender(getMemDC(), getPosition(1415, field_enemy[i][j].Mx, 283) + 250, getPosition(600, field_enemy[i][j].rc.top, 100) - 15, 0.2f);
					else  field_enemy[i][j].img->scaleRender(getMemDC(), getPosition(1415, field_enemy[i][j].Mx, 283) + 400, getPosition(600, field_enemy[i][j].rc.top, 100) - 15, 0.2f);
				}
			}
		}

		for (int i = 0; i < field_player.size(); i++)
		{
			for (int j = 0; j < field_player[i].size(); j++)
			{

				if (field_player[i][j].hp > 0)
				{
					if (i == 0 && j == 0)  field_player[i][j].img->scaleRender(getMemDC(), getPosition(1415, field_player[i][j].Mx, 283) + 260, getPosition(600, field_player[i][j].rc.top, 100) - 15, 0.2f);
					else  field_player[i][j].img->scaleRender(getMemDC(), getPosition(1415, field_player[i][j].Mx, 283) + 200, getPosition(600, field_player[i][j].rc.top, 100) - 15, 0.2f);
				}

			}
		}



		if (_userSkill->_Meteor->Use_Meteor == true)
		{

			int MiniMeteorX;
			int MiniMeteorCircleX;


			MiniMeteorCircleX = _userSkill->_Meteor->Meteor.x;																					//�߰��ѰŤ�
			MiniMeteorX = _userSkill->_Meteor->Meteor_Coordinates.x;																			//�߰��ѰŤ�
																																				//�߰��ѰŤ�
			IMAGEMANAGER->scaleFrameRender("Meteor_Circle", getMemDC(),																			//�߰��ѰŤ�
				getPosition(1415, MiniMeteorCircleX, 283) + 280,																				//�߰��ѰŤ�
				getPosition(600, IMAGEMANAGER->findImage("Meteor_Circle")->boudingBox().top, 100) - 10,											//�߰��ѰŤ�
				IMAGEMANAGER->findImage("Meteor_Circle")->getFrameX(), IMAGEMANAGER->findImage("Meteor_Circle")->getFrameY(), 0.2f);			//�߰��ѰŤ�
																																				//�߰��ѰŤ�
																																				//�߰��ѰŤ�
			IMAGEMANAGER->scaleFrameRender("Meteor", getMemDC(),																				//�߰��ѰŤ�
				getPosition(1415, MiniMeteorX, 283) + 280,																						//�߰��ѰŤ�
				getPosition(600, IMAGEMANAGER->findImage("Meteor")->boudingBox().top, 100) + -15,													//�߰��ѰŤ�
				IMAGEMANAGER->findImage("Meteor")->getFrameX(), IMAGEMANAGER->findImage("Meteor")->getFrameY(), 0.2f);							//�߰��ѰŤ�
																																				//�߰��ѰŤ�
		}


		//==================================�̴ϸ�================================================================

	}

}




// < �Լ� �� > =============================================================


//ī�޶�
void stage::camera()
{
	//ī�޶� ���� �����
	camara_rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, 80, 10);

	//�� ���������� �̵�
	if (camara_rc.right <stage1RECT.right && camara_rc.right >WINSIZEX)
	{
		stage1RECT.left -= 5;
		stage1RECT.right -= 5;


		_userSkill->_Meteor->Meteor.x -= 5;
		_userSkill->_Meteor->Meteor_Coordinates.x -= 5;

		_userSkill->_BlackHole->Damage.left -= 5;
		_userSkill->_BlackHole->Damage.right -= 5;

		_userSkill->_BlackHole->exit.left -= 5;
		_userSkill->_BlackHole->exit.right -= 5;


		_userSkill->_Heal->Damage.left -= 5;
		_userSkill->_Heal->Damage.right -= 5;


		//�����̵�
		for (int i = 0; i < 3; i++)
		{

			line[i].left -= 5;
			line[i].right -= 5;
			
			//���� �̹��� ó��
			for (int j = 0; j < field_player_die[i].size(); j++)
			{
				field_player_die[i][j].x -= 5;
			}
			//���� �̹��� ó��
			for (int j = 0; j < field_enemy_die[i].size(); j++)
			{
				field_enemy_die[i][j].x -= 5;
			}
			
			for (int j = 0; j < field_enemy[i].size(); j++)
			{
				field_enemy[i][j].x -= 5;
				if (field_enemy[i][j].sort == CASTLE)
				{
					field_enemy_hpBar[i][j].hpBar->setX(field_enemy[i][j].rc.left + 60);
					field_enemy_hpBar[i][j].hpBar->setY(field_enemy[i][j].rc.top - 30);
				}
			}
			for (int j = 0; j < field_player[i].size(); j++)
			{
				field_player[i][j].x -= 5;
				if (field_player[i][j].sort == CASTLE)
				{
					field_player_hpBar[i][j].hpBar->setX(field_player[i][j].rc.left + 64);
					field_player_hpBar[i][j].hpBar->setY(field_player[i][j].rc.top - 30);
				}
			}
		}
	}

	//�� �������� �̵�
	if (camara_rc.left < 0 && camara_rc.left >stage1RECT.left)
	{
		stage1RECT.left += 5.0f;
		stage1RECT.right += 5.0f;

		_userSkill->_Meteor->Meteor.x += 5;
		_userSkill->_Meteor->Meteor_Coordinates.x += 5;


		_userSkill->_BlackHole->Damage.left += 5;
		_userSkill->_BlackHole->Damage.right += 5;

		_userSkill->_BlackHole->exit.left += 5;
		_userSkill->_BlackHole->exit.right += 5;


		_userSkill->_Heal->Damage.left += 5;
		_userSkill->_Heal->Damage.right += 5;

		for (int i = 0; i < 3; i++)
		{
			line[i].left += 5;
			line[i].right += 5;

			//���� �̹��� ó��
			for (int j = 0; j < field_player_die[i].size(); j++)
			{
				field_player_die[i][j].x += 5;
			}
			//���� �̹��� ó��
			for (int j = 0; j < field_enemy_die[i].size(); j++)
			{
				field_enemy_die[i][j].x += 5;
			}

			for (int j = 0; j < field_enemy[i].size(); j++)
			{
				field_enemy[i][j].x += 5;
				if (field_enemy[i][j].sort == CASTLE)
				{
					field_enemy_hpBar[i][j].hpBar->setX(field_enemy[i][j].rc.left + 60);
					field_enemy_hpBar[i][j].hpBar->setY(field_enemy[i][j].rc.top - 30);
				}
			}
			for (int j = 0; j < field_player[i].size(); j++)
			{
				field_player[i][j].x += 5;
				if (field_player[i][j].sort == CASTLE)
				{
					field_player_hpBar[i][j].hpBar->setX(field_player[i][j].rc.left + 64);
					field_player_hpBar[i][j].hpBar->setY(field_player[i][j].rc.top - 30);
				}
			}
		}

	}
}

//��ȯ�Լ�(�����)
void stage::summon_hero()
{
	RECT temp;
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (PtInRect(&sumNail[0], _ptMouse))) isDrag[0] = true;
	if (isDrag[0])
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			isDrag[0] = false;
			for (int i = 0; i < 3; i++)
			{
				//3.�ʵ� �� ��ȯ ���� üũ
				if (PtInRect(&line[i], _ptMouse) && playerfood >= 3)
				{
					//�������� �������� ���α�
					_character->hero[0].x = line[i].left;
					_character->hero[0].y = line[i].top - 50;
					_character->hero[0].rc = RectMakeCenter(_character->hero[0].x, _character->hero[0].y, 256 / 2, 311 / 2);

					//�ķ��� 3��
					playerfood -= 3;
					_character->hero[0].gravity = 0;

					//4.��ȯ �������� ���콺 ���� ��ȯ + field_player ���Ϳ� �־��ֱ�
					//���ο� �������� �ְ� �ٽ� ������� ������ġ�� ����������
					field_player[i].push_back(_character->hero[0]);
					hpBar(i, true, BOSS);
					field_player_die[i].push_back(hero_die); //���� �̹��� �غ� ���ֱ�

					sumNail[0] = RectMakeCenter(250, 544, 90, 90); //255, 544
				}
				else
				{
					sumNail[0] = RectMakeCenter(250, 544, 90, 90); //255, 544
				}
			}
		}
	}
}
//��ȯ�Լ�(������)
void stage::summon_worrior()
{
	RECT temp;
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (PtInRect(&sumNail[1], _ptMouse))) isDrag[1] = true;
	if (isDrag[1])
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			isDrag[1] = false;
			for (int i = 0; i < 3; i++)
			{
				//3.�ʵ� �� ��ȯ ���� üũ
				if (PtInRect(&line[i], _ptMouse) && playerfood >= 3)
				{
					//�������� �������� ���α�
					_character->worrior[0].x = line[i].left + RND->range(-4, 4);
					_character->worrior[0].y = line[i].top;
					_character->worrior[0].rc = RectMakeCenter(_character->worrior[0].x, _character->worrior[0].y, 80, 80);

					//�ķ��� 3��
					playerfood -= 3;
					_character->worrior[0].gravity = 0;

					//4.��ȯ �������� ���콺 ���� ��ȯ + field_player ���Ϳ� �־��ֱ�
					//���ο� �������� �ְ� �ٽ� ������� ������ġ�� ����������
					field_player[i].push_back(_character->worrior[0]);
					hpBar(i, true, WORRIOR);
					field_player_die[i].push_back(worrior_die); //���� �̹��� �غ� ���ֱ�

					sumNail[1] = RectMakeCenter(344, 558, 60, 60); //255, 544
				}
				else
				{
					sumNail[1] = RectMakeCenter(344, 558, 60, 60); //255, 544
				}
			}
		}
	}
}
//��ȯ�Լ�(����)
void stage::summon_archer()
{
	RECT temp;
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (PtInRect(&sumNail[2], _ptMouse))) isDrag[2] = true;
	if (isDrag[2])
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			isDrag[2] = false;
			for (int i = 0; i < 3; i++)
			{
				//3.�ʵ� �� ��ȯ ���� üũ
				if (PtInRect(&line[i], _ptMouse) && playerfood >= 3)
				{
					//�������� �������� ���α�
					_character->archer[0].x = line[i].left;
					_character->archer[0].y = line[i].top;
					_character->archer[0].rc = RectMakeCenter(_character->archer[0].x, _character->archer[0].y, 80, 80);

					//�ķ��� 3��
					playerfood -= 3;
					_character->archer[0].gravity = 0;

					//4.��ȯ �������� ���콺 ���� ��ȯ + field_player ���Ϳ� �־��ֱ�
					//���ο� �������� �ְ� �ٽ� ������� ������ġ�� ����������
					field_player[i].push_back(_character->archer[0]);
					hpBar(i, true, ARCHER);
					field_player_die[i].push_back(archer_die); //���� �̹��� �غ� ���ֱ�

					sumNail[2] = RectMakeCenter(426, 558, 60, 60); //255, 544
				}
				else
				{
					sumNail[2] = RectMakeCenter(426, 558, 60, 60); //255, 544
				}
			}
		}
	}
}
//��ȯ�Լ�(������)
void stage::summon_magician()
{
	RECT temp;
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (PtInRect(&sumNail[3], _ptMouse))) isDrag[3] = true;
	if (isDrag[3])
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			isDrag[3] = false;
			for (int i = 0; i < 3; i++)
			{
				//3.�ʵ� �� ��ȯ ���� üũ
				if (PtInRect(&line[i], _ptMouse) && playerfood >= 3)
				{
					//�������� �������� ���α�
					_character->magician[0].x = line[i].left;
					_character->magician[0].y = line[i].top;
					_character->magician[0].rc = RectMakeCenter(_character->magician[0].x, _character->magician[0].y, 80, 80);

					//�ķ��� 3��
					playerfood -= 3;
					_character->magician[0].gravity = 0;

					//4.��ȯ �������� ���콺 ���� ��ȯ + field_player ���Ϳ� �־��ֱ�
					//���ο� �������� �ְ� �ٽ� ������� ������ġ�� ����������
					field_player[i].push_back(_character->magician[0]);
					hpBar(i, true, MAGICIAN);
					field_player_die[i].push_back(magician_die); //���� �̹��� �غ� ���ֱ�

					sumNail[3] = RectMakeCenter(506, 558, 60, 60); //255, 544
				}
				else
				{
					sumNail[3] = RectMakeCenter(506, 558, 60, 60); //255, 544
				}
			}
		}
	}
}
//��ȯ�Լ�(��)
void stage::summon_AI()
{


	if (_character->count > 1)
	{
		for (int i = 0; i < 3; i++)
		{
			if (field_enemy[i].size() < 20)
			{
				int a;
				// ������ ��ȯ
				if (KEYMANAGER->isOnceKeyDown('A'))
				{
					int a;
					a = RND->range(3);

					//�ʵ� �� 1������ ������
					if (a == 0)
					{

						_character->worrior[1].x = line[0].right;
						_character->worrior[1].y = line[0].top;
						_character->worrior[1].rc = RectMake(_character->worrior[1].x, _character->worrior[1].y, 80, 80);


						field_enemy[0].push_back(_character->worrior[1]);
						hpBar(0, false, WORRIOR);
						field_enemy_die[0].push_back(worrior_enemy_die); //���� �̹��� �غ� ���ֱ�
					}
					//�ʵ� �� 2������ ������
					if (a == 1)
					{
						_character->worrior[1].x = line[1].right;
						_character->worrior[1].y = line[1].top;
						_character->worrior[1].rc = RectMake(_character->worrior[1].x, _character->worrior[1].y, 80, 80);


						field_enemy[1].push_back(_character->worrior[1]);
						hpBar(1, false, WORRIOR);
						field_enemy_die[1].push_back(worrior_enemy_die); //���� �̹��� �غ� ���ֱ�
					}
					//�ʵ� �� 3������ ������
					if (a == 2)
					{
						_character->worrior[1].x = line[2].right;
						_character->worrior[1].y = line[2].top;
						_character->worrior[1].rc = RectMake(_character->worrior[1].x, _character->worrior[1].y, 80, 80);


						field_enemy[2].push_back(_character->worrior[1]);
						hpBar(2, false, WORRIOR);
						field_enemy_die[2].push_back(worrior_enemy_die); //���� �̹��� �غ� ���ֱ�
					}
				}
				if (KEYMANAGER->isOnceKeyDown('S'))
				{
					int b;
					b = RND->range(3);

					//�ʵ� �� 1������ ������
					if (b == 0)
					{
						_character->archer[1].x = line[0].right;
						_character->archer[1].y = line[0].top;
						_character->archer[1].rc = RectMake(_character->archer[1].x, _character->archer[1].y, 80, 80);


						field_enemy[0].push_back(_character->archer[1]);
						hpBar(0, false, ARCHER);
						field_enemy_die[0].push_back(archer_enemy_die); //���� �̹��� �غ� ���ֱ�
					}
					//�ʵ� �� 2������ ������
					if (b == 1)
					{
						_character->archer[1].x = line[1].right;
						_character->archer[1].y = line[1].top;
						_character->archer[1].rc = RectMake(_character->archer[1].x, _character->archer[1].y, 80, 80);


						field_enemy[1].push_back(_character->archer[1]);
						hpBar(1, false, ARCHER);
						field_enemy_die[1].push_back(archer_enemy_die); //���� �̹��� �غ� ���ֱ�
					}
					//�ʵ� �� 3������ ������
					if (b == 2)
					{
						_character->archer[1].x = line[2].right;
						_character->archer[1].y = line[2].top;
						_character->archer[1].rc = RectMake(_character->archer[1].x, _character->archer[1].y, 80, 80);


						field_enemy[2].push_back(_character->archer[1]);
						hpBar(2, false, ARCHER);
						field_enemy_die[2].push_back(archer_enemy_die); //���� �̹��� �غ� ���ֱ�
					}

				}

				//���Žü� ��ȯ�Լ�
				if (KEYMANAGER->isOnceKeyDown('D'))
				{
					int c;
					c = RND->range(3);

					//�ʵ� �� 1������ ������
					if (c == 0)
					{
						_character->magician[1].x = line[0].right;
						_character->magician[1].y = line[0].top;
						_character->magician[1].rc = RectMake(_character->magician[1].x, _character->magician[1].y, 80, 80);


						field_enemy[0].push_back(_character->magician[1]);
						hpBar(0, false, MAGICIAN);
						field_enemy_die[0].push_back(magician_enemy_die); //���� �̹��� �غ� ���ֱ�
					}
					//�ʵ� �� 2������ ������
					if (c == 1)
					{
						_character->magician[1].x = line[1].right;
						_character->magician[1].y = line[1].top;
						_character->magician[1].rc = RectMake(_character->magician[1].x, _character->magician[1].y, 80, 80);


						field_enemy[1].push_back(_character->magician[1]);
						hpBar(1, false, MAGICIAN);
						field_enemy_die[1].push_back(magician_enemy_die); //���� �̹��� �غ� ���ֱ�
					}
					//�ʵ� �� 3������ ������
					if (c == 2)
					{
						_character->magician[1].x = line[2].right;
						_character->magician[1].y = line[2].top;
						_character->magician[1].rc = RectMake(_character->magician[1].x, _character->magician[1].y, 80, 80);


						field_enemy[2].push_back(_character->magician[1]);
						hpBar(2, false, MAGICIAN);
						field_enemy_die[2].push_back(magician_enemy_die); //���� �̹��� �غ� ���ֱ�
					}

				}

				//������ ��ȯ
				if (KEYMANAGER->isOnceKeyDown('Q'))
				{
					int c;
					c = RND->range(3);

					//�ʵ� �� 1������ ������
					if (c == 0)
					{
						//_character->hero[0].x = line[i].left;
						//_character->hero[0].y = line[i].top - 50;
						_character->hero[1].x = line[0].right;
						_character->hero[1].y = line[0].top - 50;
						_character->hero[1].rc = RectMake(_character->hero[1].x, _character->hero[1].y, 80, 80);


						field_enemy[0].push_back(_character->hero[1]);
						hpBar(0, false, BOSS);
						field_enemy_die[0].push_back(hero_enemy_die); //���� �̹��� �غ� ���ֱ�
					}
					//�ʵ� �� 2������ ������
					if (c == 1)
					{
						_character->hero[1].x = line[1].right;
						_character->hero[1].y = line[1].top - 50;
						_character->hero[1].rc = RectMake(_character->hero[1].x, _character->hero[1].y, 80, 80);


						field_enemy[1].push_back(_character->hero[1]);
						hpBar(1, false, BOSS);
						field_enemy_die[1].push_back(hero_enemy_die); //���� �̹��� �غ� ���ֱ�
					}
					//�ʵ� �� 3������ ������
					if (c == 2)
					{
						_character->hero[1].x = line[2].right;
						_character->hero[1].y = line[2].top - 50;
						_character->hero[1].rc = RectMake(_character->hero[1].x, _character->hero[1].y, 80, 80);


						field_enemy[2].push_back(_character->hero[1]);
						hpBar(2, false, BOSS);
						field_enemy_die[2].push_back(hero_enemy_die); //���� �̹��� �غ� ���ֱ�
					}


				}
			}
		}
	}
}

//�� Ÿ�� ��ȯ
void stage::summon_tower_AI(int lineNum, int x, int y)
{
	//�������� �������� ���α�
	_character->tower[1].x = x;
	_character->tower[1].y = y;
	_character->tower[1].rc = RectMakeCenter(_character->tower[1].x, _character->tower[1].y, 160 / 1.6, 220 / 1.6);
	//_character->tower[1].hpBar->init("progressBarFront", "progressBarBack", _character->tower[1].rc.left, _character->tower[1].rc.top - 8, 100, 8);
	_character->tower[1].gravity = 0;

	//4.��ȯ �������� ���콺 ���� ��ȯ + field_player ���Ϳ� �־��ֱ�
	//���ο� �������� �ְ� �ٽ� ������� ������ġ�� ����������
	field_enemy[lineNum].push_back(_character->tower[1]);
	field_enemy_die[0].push_back(tower_enemy_die); //���� �̹��� �غ� ���ֱ�
}

//�ɽ� ��ȯ
void stage::summon_castle()
{
	//�Ʊ�
	{
		_character->castle[0].rc = RectMakeCenter(_character->castle[0].x, _character->castle[0].y, 397 / 1.4, 484 / 1.4);
		_character->castle[0].gravity = 0;
		field_player[0].push_back(_character->castle[0]);
		hpBar(0, true, _character->castle[0].sort);
		field_player_die[0].push_back(castle_die);
	}
	//����
	{
		_character->castle[1].rc = RectMakeCenter(_character->castle[1].x, _character->castle[1].y, 423 / 1.3, 445 / 1.3);
		_character->castle[1].gravity = 0;
		field_enemy[0].push_back(_character->castle[1]);
		hpBar(0, false, _character->castle[1].sort);
		field_enemy_die[0].push_back(castle_enemy_die);
	}
}


//���� ��� ������Ʈ
void stage::die()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < field_player_die[i].size(); j++)
		{
			if (field_player_die[i][j].isDie)
			{
				field_player_die[i][j].count--;
				if (field_player_die[i][j].count <= 0)
				{
					field_player_die[i].erase(field_player_die[i].begin() + j);
					j--;
				}
			}
		}
		for (int j = 0; j < field_enemy_die[i].size(); j++)
		{
			if (field_enemy_die[i][j].isDie)
			{
				field_enemy_die[i][j].count--;
				if (field_enemy_die[i][j].count <= 0)
				{
					field_enemy_die[i].erase(field_enemy_die[i].begin() + j);
					j--;
				}
			}
		}
	}
}

//����
void stage::food(int count)
{
	if (playerfood < 20)
	{
		if (count % 50 == 0)
		{
			playerfood++;
		}
	}
	//���� �ķ� �ִ�ġ ����
	if (enemyfood < 20)
	{
		if (count % 50 == 0)
		{
			enemyfood++;
		}
	}
}

//�÷��̾� �̵� �Լ� line[i] = RectMake(stage1RECT.left + 100, 330 + i * 46, 1000, 36);
void stage::runPlayer(int lineNum)
{
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		if (field_player[lineNum][i].state == RUN && field_player[lineNum][i].sort != TOWER && field_player[lineNum][i].sort != CASTLE)
		{
			field_player[lineNum][i].Mx += field_player[lineNum][i].run_spd / 4; //�߰��Ѱ� 



			field_player[lineNum][i].x += field_player[lineNum][i].run_spd / 4;
			field_player[lineNum][i].y = field_player[lineNum][i].y - 1.6 + field_player[lineNum][i].gravity;
			if (field_player[lineNum][i].gravity > 3.1f)
			{
				field_player[lineNum][i].gravity = 0;
			}
			else
			{
				field_player[lineNum][i].gravity += 0.1f;
			}
		}
		//��Ʈ ������Ʈ summon_castle(-64, 100, 1200 - (423 / 1.3) + 64, 108);
		if (field_player[lineNum][i].sort == CASTLE)
		{
			field_player[lineNum][i].rc = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 397 / 1.4, 484 / 1.4);
			field_player[lineNum][i].rc_attRange = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 397 / 1.4, 484 / 1.4);
		}
		else if (field_player[lineNum][i].sort == TOWER)
		{
			field_player[lineNum][i].rc = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 160 / 1.6, 220 / 1.6);
			field_player[lineNum][i].rc_attRange = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 320, 80);
		}
		else if (field_player[lineNum][i].sort == BOSS)
		{
			field_player[lineNum][i].rc = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 256 / 2, 311 / 2);
			field_player[lineNum][i].rc_attRange = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 256 / 2 + 100, 311 / 2);
		}
		else if (field_player[lineNum][i].sort == WORRIOR)
		{
			field_player[lineNum][i].rc = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 80, 80);
			field_player[lineNum][i].rc_attRange = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 80, 80);
		}
		else if (field_player[lineNum][i].sort == ARCHER)
		{
			field_player[lineNum][i].rc = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 80, 80);
			field_player[lineNum][i].rc_attRange = RectMake(field_player[lineNum][i].x, field_player[lineNum][i].rc.top, 200, 80);
		}
		else if (field_player[lineNum][i].sort == MAGICIAN)
		{
			field_player[lineNum][i].rc = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 80, 80);
			field_player[lineNum][i].rc_attRange = RectMake(field_player[lineNum][i].x, field_player[lineNum][i].rc.top, 300, 80);
		}
	}
}
//�� �̵� �Լ�
void stage::runEnemy(int lineNum)
{
	for (int i = 0; i < field_enemy[lineNum].size(); i++)
	{
		if (field_enemy[lineNum][i].state == RUN && field_enemy[lineNum][i].sort != TOWER && field_enemy[lineNum][i].sort != CASTLE)
		{

			field_enemy[lineNum][i].Mx += field_enemy[lineNum][i].run_spd / 4; //�߰��Ѱ� 



			field_enemy[lineNum][i].x += field_enemy[lineNum][i].run_spd / 4;
			field_enemy[lineNum][i].y = field_enemy[lineNum][i].y - 1.6 + field_enemy[lineNum][i].gravity;
			if (field_enemy[lineNum][i].gravity > 3.1f)
			{
				field_enemy[lineNum][i].gravity = 0;
			}
			else
			{
				field_enemy[lineNum][i].gravity += 0.1f;
			}
		}
		if (field_enemy[lineNum][i].sort == CASTLE)
		{
			field_enemy[lineNum][i].rc = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 423 / 1.3, 445 / 1.3);
			field_enemy[lineNum][i].rc_attRange = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 423 / 1.3, 445 / 1.3);
		}
		else if (field_enemy[lineNum][i].sort == TOWER)
		{
			field_enemy[lineNum][i].rc = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 160 / 1.6, 220 / 1.6);
			field_enemy[lineNum][i].rc_attRange = RectMakeCenter(field_enemy[lineNum][i].x - 320, field_enemy[lineNum][i].y, 320, 80);
		}
		else if (field_enemy[lineNum][i].sort == BOSS)
		{
			field_enemy[lineNum][i].rc = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 238 / 2, 270 / 2);
			field_enemy[lineNum][i].rc_attRange = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 238 / 2 + 100, 270 / 2);
		}
		else if (field_enemy[lineNum][i].sort == WORRIOR)
		{
			field_enemy[lineNum][i].rc = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 80, 80);
			field_enemy[lineNum][i].rc_attRange = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 80, 80);
		}
		else if (field_enemy[lineNum][i].sort == ARCHER)
		{
			field_enemy[lineNum][i].rc = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 80, 80);
			field_enemy[lineNum][i].rc_attRange = RectMake(field_enemy[lineNum][i].x - 200, field_enemy[lineNum][i].rc.top, 200, 80);
		}
		else if (field_enemy[lineNum][i].sort == MAGICIAN)
		{
			field_enemy[lineNum][i].rc = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 80, 80);
			field_enemy[lineNum][i].rc_attRange = RectMake(field_enemy[lineNum][i].x - 300, field_enemy[lineNum][i].rc.top, 300, 80);
		}
	}
}


//ü�¹� �����̵�(��� ��ġ��)
void stage::updateHpBar()
{
	for (int j = 0; j < 3; j++)
	{
		//�Ʊ�
		for (int i = 0; i < field_player_hpBar[j].size(); i++)
		{
			if (field_player[j][i].sort == CASTLE)
			{
				field_player_hpBar[j][i].hpBar->setX(field_player[j][i].rc.left + 60);
				field_player_hpBar[j][i].hpBar->setY(field_player[j][i].rc.top - 30);
			}
			else
			{
				field_player_hpBar[j][i].hpBar->setX(field_player[j][i].rc.left + 15);
				field_player_hpBar[j][i].hpBar->setY(field_player[j][i].rc.top);
			}
			field_player_hpBar[j][i].hpBar->setGauge(field_player[j][i].hp, field_player[j][i].maxhp);
			field_player_hpBar[j][i].hpBar->update();
		}
		//����
		for (int i = 0; i < field_enemy_hpBar[j].size(); i++)
		{
			if (field_enemy[j][i].sort == CASTLE)
			{
				field_enemy_hpBar[j][i].hpBar->setX(field_enemy[j][i].rc.left + 60);
				field_enemy_hpBar[j][i].hpBar->setY(field_enemy[j][i].rc.top - 30);
			}
			else
			{
				field_enemy_hpBar[j][i].hpBar->setX(field_enemy[j][i].rc.left + 15);
				field_enemy_hpBar[j][i].hpBar->setY(field_enemy[j][i].rc.top);
			}
			field_enemy_hpBar[j][i].hpBar->setGauge(field_enemy[j][i].hp, field_enemy[j][i].maxhp);
			field_enemy_hpBar[j][i].hpBar->update();
		}
	}
}

//ü�¹� ����
void stage::hpBar(int lineNum, bool isPlayer, int sort)
{
	tagProgressBar _hp;
	ZeroMemory(&_hp, sizeof(tagProgressBar));
	_hp.hpBar = new progressBar;
	if (sort == WORRIOR || sort == ARCHER || sort == MAGICIAN)
	{
		if (isPlayer)
		{
			_hp.hpBar->init("PlayerprogressBarFront", "progressBarBack", 0, 0, 50, 6);
			_hp.hpBar->setGauge(10, 10);
			field_player_hpBar[lineNum].push_back(_hp);
		}
		if (!isPlayer)
		{
			_hp.hpBar->init("progressBarFront", "progressBarBack", 0, 0, 50, 6);
			_hp.hpBar->setGauge(10, 10);
			field_enemy_hpBar[lineNum].push_back(_hp);
		}
	}
	if (sort == CASTLE)
	{
		if (isPlayer)
		{
			_hp.hpBar->init("castle_hpBar_0.1496.128", "castle_hpBar_back.1496.128", 6, 78, 200, 32);
			_hp.hpBar->setGauge(10, 10);
			field_player_hpBar[lineNum].push_back(_hp);
		}
		if (!isPlayer)
		{
			//_hp.hpBar->init("castle_hpBar_1.1496.128", "castle_hpBar_back.1496.128", 1200 - 200 - 4, 80, 200, 32);
			_hp.hpBar->init("castle_hpBar_1.1496.128", "castle_hpBar_back.1496.128", 100, 100, 200, 32);
			_hp.hpBar->setGauge(10, 10);
			field_enemy_hpBar[lineNum].push_back(_hp);
		}
	}
	if (sort == BOSS)
	{
		if (isPlayer)
		{
			_hp.hpBar->init("boss_hpBar_0.1496.128", "boss_hpBar_back.1496.128", 6, 78, 100, 12);
			_hp.hpBar->setGauge(10, 10);
			field_player_hpBar[lineNum].push_back(_hp);
		}
		if (!isPlayer)
		{
			//_hp.hpBar->init("castle_hpBar_1.1496.128", "castle_hpBar_back.1496.128", 1200 - 200 - 4, 80, 200, 32);
			_hp.hpBar->init("boss_hpBar_1.1496.128", "boss_hpBar_back.1496.128", 100, 100, 100, 12);
			_hp.hpBar->setGauge(10, 10);
			field_enemy_hpBar[lineNum].push_back(_hp);
		}
	}
}

//�� ���� �浹 �� => ���� ���·� ����
void stage::bump(int lineNum)
{
	RECT temp;
	//�÷��̾� üũ
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		for (int j = 0; j < field_enemy[lineNum].size(); j++)
		{
			if (IntersectRect(&temp, &field_player[lineNum][i].rc_attRange, &field_enemy[lineNum][j].rc))
			{
				field_player[lineNum][i].state = ATTACK;

				if (field_player[lineNum][i].state == ATTACK)
				{
					if (_character->count % 100 == 0)//����
					{
						field_player[lineNum][i].fire = true;
						field_player[lineNum][i].fire_motion = true;
						field_player[lineNum][i].rc_att = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 52, 16);
						//SOUNDMANAGER->play("���ݻ���_������");
						this->sortSound_player(lineNum, i);

						if (field_enemy[lineNum][j].hp <= 0)
						{
							field_player[lineNum][i].state = RUN;
							field_player[lineNum][i].fire = false;
							field_player[lineNum][i].fire_motion = false;
						}
					}
					else if (_character->count % 100 >= 50)
					{
						field_player[lineNum][i].fire_motion = false;
					}
					break;
				}
			}
			else
			{
				field_player[lineNum][i].state = RUN;
			}
		}
	}
	
	

	//���ʹ� üũ
	for (int i = 0; i < field_enemy[lineNum].size(); i++)
	{
		for (int j = 0; j < field_player[lineNum].size(); j++)
		{
			
			if (IntersectRect(&temp, &field_enemy[lineNum][i].rc_attRange, &field_player[lineNum][j].rc))
			{
				field_enemy[lineNum][i].state = ATTACK;

				if (field_enemy[lineNum][i].state == ATTACK)
				{
					if (_character->count % 120 == 0)
					{
						field_enemy[lineNum][i].fire = true;
						field_enemy[lineNum][i].fire_motion = true;
						field_enemy[lineNum][i].rc_att = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 52, 16);
						this->sortSound_enemy(lineNum, i);

						if (field_player[lineNum][j].hp <= 0)
						{
							field_enemy[lineNum][i].state = RUN;
							field_enemy[lineNum][i].fire = false;
							field_enemy[lineNum][i].fire_motion = false;
						}
					}
					else if (_character->count % 120 >= 50)
					{
						field_enemy[lineNum][i].fire_motion = false;
					}
					break;
				}
			}
			else
			{
				field_enemy[lineNum][i].state = RUN;
			}
		}
	}


	//�Ʊ��� ����
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		for (int j = 0; j < field_enemy[lineNum].size(); j++)
		{
			if (field_player[lineNum][i].fire)
			{
				//�߻�ü ��Ʈ ������Ʈ
				field_player[lineNum][i].rc_att.left += 3;
				field_player[lineNum][i].rc_att.right += 3;
				if (IntersectRect(&temp, &field_player[lineNum][i].rc_att, &field_enemy[lineNum][j].rc)) //�浹 üũ
				{
					field_enemy[lineNum][j].hp = field_enemy[lineNum][j].hp - field_player[lineNum][i].att;
					field_player[lineNum][i].fire = false;
					//�ǰ� ����Ʈ on
					field_enemy[lineNum][j].isHit = true;
				}
			}
			if (!IntersectRect(&temp, &field_player[lineNum][i].rc_att, &field_player[lineNum][i].rc_attRange)) //���� �Ѿ�� �ʱ�ȭ
			{
				field_player[lineNum][i].fire = false;
				field_player[lineNum][i].fire_motion = false;
			}
		}
	}
	//������ ���� 
	for (int i = 0; i < field_enemy[lineNum].size(); i++)
	{
		for (int j = 0; j < field_player[lineNum].size(); j++)
		{
			if (field_enemy[lineNum][i].fire)
			{
				//�߻�ü ��Ʈ ������Ʈ
				field_enemy[lineNum][i].rc_att.left -= 3;
				field_enemy[lineNum][i].rc_att.right -= 3;
				if (IntersectRect(&temp, &field_enemy[lineNum][i].rc_att, &field_player[lineNum][j].rc)) //�浹 üũ
				{
					field_player[lineNum][j].hp = field_player[lineNum][j].hp - field_enemy[lineNum][i].att;//����
					field_enemy[lineNum][i].fire = false;
					//�ǰ� ����Ʈ on
					field_player[lineNum][j].isHit = true;
				}
			}
			if (!IntersectRect(&temp, &field_enemy[lineNum][i].rc_att, &field_enemy[lineNum][i].rc_attRange)) //���� �Ѿ�� �ʱ�ȭ
			{
				field_enemy[lineNum][i].fire = false;
				field_enemy[lineNum][i].fire_motion = false;
			}
		}
	}
}

//�� ���� �浹 �� => ���� ���·� ����
void stage::bumpCastle(int lineNum)
{
	RECT temp;
	//�÷��̾� üũ
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		for (int j = 0; j < field_enemy[0].size(); j++)
		{
			if (IntersectRect(&temp, &field_player[lineNum][i].rc_attRange, &field_enemy[0][0].rc))
			{
				field_player[lineNum][i].state = ATTACK;

				if (field_player[lineNum][i].state == ATTACK)
				{
					if (_character->count % 100 == 0)//����
					{
						field_player[lineNum][i].fire = true;
						field_player[lineNum][i].fire_motion = true;
						field_player[lineNum][i].rc_att = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 52, 16);

						if (field_enemy[0][0].hp <= 0)
						{
							field_player[lineNum][i].state = RUN;
							field_player[lineNum][i].fire = false;
							field_player[lineNum][i].fire_motion = false;
						}
					}
					else if (_character->count % 100 >= 50)
					{
						field_player[lineNum][i].fire_motion = false;
					}
					break;
				}
			}
			else
			{
				field_player[lineNum][i].state = RUN;
			}
		}
	}



	//���ʹ� üũ
	for (int i = 0; i < field_enemy[lineNum].size(); i++)
	{
		for (int j = 0; j < field_player[0].size(); j++)
		{
			if (IntersectRect(&temp, &field_enemy[lineNum][i].rc_attRange, &field_player[0][0].rc))
			{
				field_enemy[lineNum][i].state = ATTACK;

				if (field_enemy[lineNum][i].state == ATTACK)
				{
					if (_character->count % 100 == 0)
					{
						field_enemy[lineNum][i].fire = true;
						field_enemy[lineNum][i].fire_motion = true;
						field_enemy[lineNum][i].rc_att = RectMakeCenter(field_enemy[lineNum][i].x, field_enemy[lineNum][i].y, 52, 16);

						if (field_player[0][0].hp <= 0)
						{
							field_enemy[lineNum][i].state = RUN;
							field_enemy[lineNum][i].fire = false;
							field_enemy[lineNum][i].fire_motion = false;
						}
					}
					else if (_character->count % 100 >= 50)
					{
						field_enemy[lineNum][i].fire_motion = false;
					}
					break;
				}
			}
			else
			{
				field_enemy[lineNum][i].state = RUN;
			}
		}
	}


	//�Ʊ��� ����
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		for (int j = 0; j < field_enemy[0].size(); j++)
		{
			if (field_player[lineNum][i].fire)
			{
				//�߻�ü ��Ʈ ������Ʈ
				field_player[lineNum][i].rc_att.left += 3;
				field_player[lineNum][i].rc_att.right += 3;
				if (IntersectRect(&temp, &field_player[lineNum][i].rc_att, &field_enemy[0][0].rc)) //�浹 üũ
				{
					field_enemy[0][0].hp = field_enemy[0][0].hp - field_player[lineNum][i].att;
					field_player[lineNum][i].fire = false;
					//�ǰ� ����Ʈ on
					field_enemy[0][0].isHit = true;
				}
			}
			if (!IntersectRect(&temp, &field_player[lineNum][i].rc_att, &field_player[lineNum][i].rc_attRange)) //���� �Ѿ�� �ʱ�ȭ
			{
				field_player[lineNum][i].fire = false;
				field_player[lineNum][i].fire_motion = false;
			}
		}
	}
	//������ ���� 
	for (int i = 0; i < field_enemy[lineNum].size(); i++)
	{
		for (int j = 0; j < field_player[0].size(); j++)
		{
			if (field_enemy[lineNum][i].fire)
			{
				//�߻�ü ��Ʈ ������Ʈ
				field_enemy[lineNum][i].rc_att.left -= 3;
				field_enemy[lineNum][i].rc_att.right -= 3;
				if (IntersectRect(&temp, &field_enemy[lineNum][i].rc_att, &field_player[0][0].rc)) //�浹 üũ
				{
					field_player[0][0].hp = field_player[0][0].hp - field_enemy[lineNum][i].att;//����
					field_enemy[lineNum][i].fire = false;
					//�ǰ� ����Ʈ on
					field_player[0][0].isHit = true;
				}
			}
			if (!IntersectRect(&temp, &field_enemy[lineNum][i].rc_att, &field_enemy[lineNum][i].rc_attRange)) //���� �Ѿ�� �ʱ�ȭ
			{
				field_enemy[lineNum][i].fire = false;
				field_enemy[lineNum][i].fire_motion = false;
			}
		}
	}
}

//�÷��̾� ����
void stage::removeplayer(int lineNum)
{
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		if (field_player[lineNum].size() != 0)
		{
			if (field_player[lineNum][i].hp <= 0)
			{

				field_player_die[lineNum][i].isDie = true; //���� �̹��� ��� ����
				field_player_die[lineNum][i].x = field_player[lineNum][i].rc.left - 40;// field_player[i][j].y
				field_player_die[lineNum][i].y = field_player[lineNum][i].y - 20;

				field_player[lineNum][i].state = DIE;
				SOUNDMANAGER->play("����_�Ʊ�");
				field_player[lineNum].erase(field_player[lineNum].begin() + i);
				field_player_hpBar[lineNum].erase(field_player_hpBar[lineNum].begin() + i);
				i--;
			}
		}
	}
}
//���ʹ� ����
void stage::removeEnemy(int lineNum)
{
	for (int i = 0; i < field_enemy[lineNum].size(); i++)
	{
		if (field_enemy[lineNum][i].hp <= 0)
		{
			field_enemy_die[lineNum][i].isDie = true; //���� �̹��� ��� ����
			field_enemy_die[lineNum][i].x = field_enemy[lineNum][i].rc.left + 60;// field_player[i][j].y
			field_enemy_die[lineNum][i].y = field_enemy[lineNum][i].y -20;

			field_enemy[lineNum][i].state = DIE;
			SOUNDMANAGER->play("����_��");
			field_enemy[lineNum].erase(field_enemy[lineNum].begin() + i);
			field_enemy_hpBar[lineNum].erase(field_enemy_hpBar[lineNum].begin() + i);
			i--;
		}
	}
}


void stage::sortSound_player(int lineNum, int i)
{
	switch (field_player[lineNum][i].sort)
	{
	case BOSS:
		SOUNDMANAGER->play("���ݻ���_����");
		break;
	case WORRIOR:
		SOUNDMANAGER->play("���ݻ���_������");
		break;
	case ARCHER:
		SOUNDMANAGER->play("���ݻ���_����");
		break;
	case MAGICIAN:
		SOUNDMANAGER->play("����_������", 0.6f);
		break;
	case TOWER:
		SOUNDMANAGER->play("���ݻ���_����");
		break;
	case CASTLE:
		SOUNDMANAGER->play("���ݻ���_����");
		break;
	}
}

void stage::sortSound_enemy(int lineNum, int i)
{
	switch (field_enemy[lineNum][i].sort)
	{
	case BOSS:
		SOUNDMANAGER->play("���ݻ���_����");
		break;
	case WORRIOR:
		SOUNDMANAGER->play("���ݻ���_������");
		break;
	case ARCHER:
		SOUNDMANAGER->play("���ݻ���_����");
		break;
	case MAGICIAN:
		SOUNDMANAGER->play("����_������", 0.6f);
		break;
	case TOWER:
		SOUNDMANAGER->play("���ݻ���_����");
		break;
	case CASTLE:
		SOUNDMANAGER->play("���ݻ���_����");
		break;
	}
}



