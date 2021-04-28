#include "stdafx.h"
#include "stage.h"



HRESULT stage::init()
{
	//스테이지렉터
	stage1RECT = RectMake(0, 0, 1200, 500);

	//라인 만들기
	for (int i = 0; i < 3; i++) line[i] = RectMake(stage1RECT.left + 100, 330 + i * 46, 1000, 36);
	//썸네일 박스 초기화
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

	//카메라 생성
	camara_rc = RectMake(_ptMouse.x - 10, _ptMouse.y, 20, 10);

	//라인 사이즈 설정
	field_player.resize(3);
	field_enemy.resize(3);

	//hp바 사이즈 설정
	ZeroMemory(&init_hpBar, sizeof(tagProgressBar));
	init_hpBar.hpBar = new progressBar;
	init_hpBar.hpBar->init("PlayerprogressBarFront", "progressBarBack", 0, 0, 50, 6);
	field_player_hpBar.resize(3);
	field_enemy_hpBar.resize(3);


	//다이 이미지 최초 초기화
	{
		hero_die.img = IMAGEMANAGER->findImage("히어로_다이");
		hero_die.count = 200;
		hero_die.isDie = false;
		worrior_die.img = IMAGEMANAGER->findImage("워리어_다이");
		worrior_die.count = 200;
		worrior_die.isDie = false;
		archer_die.img = IMAGEMANAGER->findImage("아처_다이");
		archer_die.count = 200;
		archer_die.isDie = false;
		magician_die.img = IMAGEMANAGER->findImage("메지션_다이");
		magician_die.count = 200;
		magician_die.isDie = false;
		tower_die.img = IMAGEMANAGER->findImage("빈페이지");
		tower_die.count = 200;
		tower_die.isDie = false;
		castle_die.img = IMAGEMANAGER->findImage("빈페이지");
		castle_die.count = 200;
		castle_die.isDie = false;

		hero_enemy_die.img = IMAGEMANAGER->findImage("히어로_적_다이");
		hero_enemy_die.count = 200;
		hero_enemy_die.isDie = false;
		worrior_enemy_die.img = IMAGEMANAGER->findImage("워리어_적_다이");
		worrior_enemy_die.count = 200;
		worrior_enemy_die.isDie = false;
		archer_enemy_die.img = IMAGEMANAGER->findImage("아처_적_다이");
		archer_enemy_die.count = 200;
		archer_enemy_die.isDie = false;
		magician_enemy_die.img = IMAGEMANAGER->findImage("메지션_적_다이");
		magician_enemy_die.count = 200;
		magician_enemy_die.isDie = false;
		tower_enemy_die.img = IMAGEMANAGER->findImage("빈페이지");
		tower_enemy_die.count = 200;
		tower_enemy_die.isDie = false;
		castle_enemy_die.img = IMAGEMANAGER->findImage("빈페이지");
		castle_enemy_die.count = 200;
		castle_enemy_die.isDie = false;
	}

	//다이 벡트 컨테이너 사이즈 설정
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
	//SOUNDMANAGER->play("브금_스테이지", 0.1f);

	if (isplay == true)
	{
		
		_character->count++;

		//카메라
		this->camera();

		//식량
		this->food(_character->count);

		//다이함수
		for (int c = 0; c < 3; c++) this->removeplayer(c);
		for (int c = 0; c < 3; c++) this->removeEnemy(c);

		//소환함수
		this->summon_hero();
		this->summon_worrior();
		this->summon_archer();
		this->summon_magician();
		this->summon_AI();

		//적 이동 함수
		for (int i = 0; i < 3; i++) this->runPlayer(i);
		for (int i = 0; i < 3; i++) this->runEnemy(i);

		//각 라인 충돌 시 => 어택 상태로 변경
		for (int i = 1; i < 3; i++) this->bumpCastle(i);
		for (int i = 0; i < 3; i++) this->bump(i);

		//체력바 업데이트
		this->updateHpBar();

		//다이 업데이트
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
					SOUNDMANAGER->play("블랙홀_바람");
					break;
				}
			}
		}
		if (bcount == count)
		{
			SOUNDMANAGER->stop("블랙홀_바람");
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

					//렉트 위치조정하셈(DAMAGE, exit)
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
						SOUNDMANAGER->play("블랙홀_사운드");
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
			SOUNDMANAGER->stop("브금_스테이지");
			SOUNDMANAGER->play("브금_승리", 0.5f);
			SOUNDMANAGER->play("브금_승리2", 1);

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
			SOUNDMANAGER->stop("브금_승리");
			SOUNDMANAGER->stop("브금_승리2");
			SOUNDMANAGER->play("버튼");
			
			SOUNDMANAGER->play("브금_로비", 0.2f);
			SCENEMANAGER->loadScene("stageMap");


		}
	}



	//============================================



}


void stage::render()
{
	//배경이미지 랜더
	
	if ((playerInfo::getSingleton()->lv_stage) == 0)
	{
		IMAGEMANAGER->findImage("배경1_2")->render(getMemDC());
		_stageInfo->chapter1_stage1.img->render(getMemDC(), 0, -80);
	}
	if ((playerInfo::getSingleton()->lv_stage) == 1)	_stageInfo->chapter1_stage2.img->render(getMemDC());
	if ((playerInfo::getSingleton()->lv_stage) == 4)	_stageInfo->chapter1_stage5.img->render(getMemDC());
	if ((playerInfo::getSingleton()->lv_stage) == 5)	_stageInfo->chapter2_stage1.img->render(getMemDC());
		//IMAGEMANAGER->render("배경5", getMemDC(), 0, 0);
	IMAGEMANAGER->render("라인", getMemDC(), stage1RECT.left, stage1RECT.top);
	IMAGEMANAGER->render("인게임UI", getMemDC(), 0, 0);

	//SOUNDMANAGER->play("브금_스테이지", 0.1f);

	if (isplay == false)
	{
		
		IMAGEMANAGER->findImage("end")->render(getMemDC(), end.left, end.top);

		imagescaleNum("숫자2", getMemDC(), WINSIZEX/2+75,WINSIZEY/2-30, getgold, 14, 0.45);
	}




	if (isplay == true)
	{
		char skill[128];

		textOutFontNum(getMemDC(), sumNailSkill[0].left + 50, sumNailSkill[0].top - 20, playerInfo::getSingleton()->num_skill2, 20, RGB(250, 200, 0));	//추가
		textOutFontNum(getMemDC(), sumNailSkill[1].left + 50, sumNailSkill[1].top - 20, playerInfo::getSingleton()->num_skill1, 20, RGB(250, 200, 0));	//추가
		textOutFontNum(getMemDC(), sumNailSkill[2].left + 50, sumNailSkill[2].top - 20, playerInfo::getSingleton()->num_skill3, 20, RGB(250, 200, 0));	//추가
		textOutFont(getMemDC(), sumNailSkill[0].left + 8, sumNailSkill[0].top - 20, "보유 : ", 20, RGB(250, 200, 0));
		textOutFont(getMemDC(), sumNailSkill[1].left + 8, sumNailSkill[1].top - 20, "보유 : ", 20, RGB(250, 200, 0));
		textOutFont(getMemDC(), sumNailSkill[2].left + 8, sumNailSkill[2].top - 20, "보유 : ", 20, RGB(250, 200, 0));

		textOutFont(getMemDC(), sumNailSkill[0].left - 246, sumNailSkill[0].top - 20, "Cost: 3    Cost: 3    Cost: 3", 20, RGB(250, 200, 0));

		//라인 위 캐릭터 렌더
		{
			//적군 라인 렌더
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < field_enemy[j].size(); i++)
				{
					//이펙트 렌더
					if (field_enemy[j][i].fire)
					{
						//공격 이펙트 렌더
						field_enemy[j][i].img_att->render(getMemDC(), field_enemy[j][i].rc_att.left, field_enemy[j][i].rc_att.top);
					}

					//공격 모션 렌더
					if (field_enemy[j][i].fire_motion)
					{
						//무기 렌더
						if (_character->count % 1 == 0)
						{
							if (field_enemy[j][i].sort == BOSS) //보스 렌더
							{
								if (field_enemy[j][i].angle < 0)
								{
									field_enemy[j][i].isDown = true; //아래로 내려라 
									field_enemy[j][i].fire = false;
									field_enemy[j][i].angle = 0;
								}
								if (field_enemy[j][i].angle > ((PI * 5) / 8)) field_enemy[j][i].isDown = false; //위로 올려라
								if (field_enemy[j][i].isDown) field_enemy[j][i].angle += PI / 4; //아래로 회전 엥글
								if (!field_enemy[j][i].isDown) field_enemy[j][i].angle -= PI / 64; //위로 올리는 엥글
							}
							else
							{
								if (field_enemy[j][i].angle < 0)
								{
									field_enemy[j][i].isDown = true; //아래로 내려라 
									field_enemy[j][i].fire = false;
									field_enemy[j][i].angle = 0;
								}
								if (field_enemy[j][i].angle > ((PI * 5) / 8)) field_enemy[j][i].isDown = false; //위로 올려라
								if (field_enemy[j][i].isDown) field_enemy[j][i].angle += PI / 4; //아래로 회전 엥글
								if (!field_enemy[j][i].isDown) field_enemy[j][i].angle -= PI / 64; //위로 올리는 엥글
							}
						}
						if (field_enemy[j][i].sort == BOSS) //회전 렌더 적용
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
					else//무기 초기 각도
					{
						if (field_enemy[j][i].sort == BOSS) //보스 렌더
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
					//캐릭터 이미지 렌더
					field_enemy[j][i].img->render(getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
				}
			}

			//우리 라인 렌더
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < field_player[j].size(); i++)
				{
					//이펙트 렌더
					if (field_player[j][i].fire) //공격 충돌체 렌더
					{
						//공격 이펙트 렌더
						field_player[j][i].img_att->render(getMemDC(), field_player[j][i].rc_att.left, field_player[j][i].rc_att.top);
					}

					//공격 모션 렌더
					if (field_player[j][i].fire_motion) //공격 충돌체 렌더
					{
						//무기 렌더
						if (_character->count % 1 == 0)
						{
							if (field_player[j][i].sort == ARCHER) //활 렌더
							{
								if (field_player[j][i].angle < 0)
								{
									field_player[j][i].isDown = true; //아래로 내려라 
									field_player[j][i].fire_motion = false;
									field_player[j][i].angle = 0;
								}
								if (field_player[j][i].angle > +((PI * 4) / 8)) field_player[j][i].isDown = false; //위로 올려라
								if (field_player[j][i].isDown) field_player[j][i].angle += PI / 64; //아래로 회전 엥글
								if (!field_player[j][i].isDown) field_player[j][i].angle -= PI / 4; //위로 올리는 엥글
							}
							else if (field_player[j][i].sort == BOSS) //보스 렌더
							{
								if (field_player[j][i].angle > 0)
								{
									field_player[j][i].isDown = true; //아래로 내려라 
									field_player[j][i].fire = false;
									field_player[j][i].angle = 0;
								}
								if (field_player[j][i].angle < -((PI * 5) / 8)) field_player[j][i].isDown = false; //위로 올려라
								if (field_player[j][i].isDown) field_player[j][i].angle -= PI / 4; //아래로 회전 엥글
								if (!field_player[j][i].isDown) field_player[j][i].angle += PI / 64; //위로 올리는 엥글
							}
							else //기본 렌더
							{
								if (field_player[j][i].angle > 0)
								{
									field_player[j][i].isDown = true; //아래로 내려라 
									field_player[j][i].fire = false;
									field_player[j][i].angle = 0;
								}
								if (field_player[j][i].angle < -((PI * 5) / 8)) field_player[j][i].isDown = false; //위로 올려라
								if (field_player[j][i].isDown) field_player[j][i].angle -= PI / 4; //아래로 회전 엥글
								if (!field_player[j][i].isDown) field_player[j][i].angle += PI / 64; //위로 올리는 엥글
							}
						}
						if (field_player[j][i].sort == ARCHER) //회전 적용
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 48, field_player[j][i].rc.top + 56, -((PI * 3) / 8) + field_player[j][i].angle);
						}
						else if (field_player[j][i].sort == BOSS) //보스 렌더
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 86, field_player[j][i].rc.top + 116, ((PI * 5) / 8) + field_player[j][i].angle);
						}
						else
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 52, field_player[j][i].rc.top + 60, ((PI * 5) / 8) + field_player[j][i].angle);
						}
					}
					else//무기 초기 각도
					{
						if (field_player[j][i].sort == ARCHER)
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 48, field_player[j][i].rc.top + 56, -((PI * 3) / 8) + 0);
						}
						else if (field_player[j][i].sort == BOSS) //보스 렌더
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 86, field_player[j][i].rc.top + 116, ((PI * 3) / 8) + 0);
						}
						else
						{
							field_player[j][i].img_weapon->rotateRender(getMemDC(), field_player[j][i].rc.left + 52, field_player[j][i].rc.top + 60, ((PI * 3) / 8) + 0);
						}
					}
					//캐릭터 이미지 렌더(런)
					field_player[j][i].img->render(getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
				}
			}
		}


		//피격 이펙트 렌더
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < field_player[j].size(); i++)
			{
				//아군
				if (field_player[j][i].isHit)
				{
					switch (field_player[j][i].sort)
					{
					case BOSS:
						IMAGEMANAGER->render("히어로_피격", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					case WORRIOR:
						IMAGEMANAGER->render("워리어_피격", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					case ARCHER:
						IMAGEMANAGER->render("아처_피격", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					case MAGICIAN:
						IMAGEMANAGER->render("메지션_피격", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					case TOWER:
						IMAGEMANAGER->render("타워_피격", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					case CASTLE:
						IMAGEMANAGER->render("케슬_피격", getMemDC(), field_player[j][i].rc.left, field_player[j][i].rc.top);
						break;
					}
					field_player[j][i].isHit = false;
				}
			}
			//적군
			for (int i = 0; i < field_enemy[j].size(); i++)
			{
				if (field_enemy[j][i].isHit)
				{
					switch (field_enemy[j][i].sort)
					{
					case BOSS:
						IMAGEMANAGER->render("히어로_적_피격", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					case WORRIOR:
						IMAGEMANAGER->render("워리어_적_피격", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					case ARCHER:
						IMAGEMANAGER->render("아처_적_피격", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					case MAGICIAN:
						IMAGEMANAGER->render("메지션_적_피격", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					case TOWER:
						IMAGEMANAGER->render("타워_적_피격", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					case CASTLE:
						IMAGEMANAGER->render("케슬_적_피격", getMemDC(), field_enemy[j][i].rc.left, field_enemy[j][i].rc.top);
						break;
					}
					field_enemy[j][i].isHit = false;
				}
			}
		}


		//체력바 렌더
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



		//다이 모션 알파 처리
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


		//아군 푸드 렌더
		imageNum("숫자2", getMemDC(), 128, 524, playerfood, 32);

		// 소환 시, 캐릭터 이미지 마우스 포인터에 렌더
		{
			if (isDrag[0])
			{
				sumNail[0] = RectMakeCenter(_ptMouse.x, _ptMouse.y, 256 / 2, 311 / 2);
				IMAGEMANAGER->render("히어로", getMemDC(), sumNail[0].left, sumNail[0].top);
				for (int i = 0; i < 3; i++)
				{
					if (PtInRect(&line[i], _ptMouse))
					{
						FrameRect(getMemDC(), line[i], RGB(255, 255, 0));
						if ((_character->count / 10) % 2 == 0) IMAGEMANAGER->alphaRender("히어로", getMemDC(), line[i].left - 70, line[i].top - 140, 200);
					}
				}
			}
			if (isDrag[1])
			{
				sumNail[1] = RectMakeCenter(_ptMouse.x, _ptMouse.y, 80, 80);
				IMAGEMANAGER->render("워리어", getMemDC(), sumNail[1].left, sumNail[1].top);
				for (int i = 0; i < 3; i++)
				{
					if (PtInRect(&line[i], _ptMouse))
					{
						FrameRect(getMemDC(), line[i], RGB(255, 255, 0));
						if ((_character->count / 10) % 2 == 0) IMAGEMANAGER->alphaRender("워리어", getMemDC(), line[i].left - 40, line[i].top - 50, 200);
					}
				}
			}
			if (isDrag[2])
			{
				sumNail[2] = RectMakeCenter(_ptMouse.x, _ptMouse.y, 80, 80);
				IMAGEMANAGER->render("아처", getMemDC(), sumNail[2].left, sumNail[2].top);
				for (int i = 0; i < 3; i++)
				{
					if (PtInRect(&line[i], _ptMouse))
					{
						FrameRect(getMemDC(), line[i], RGB(255, 255, 0));
						if ((_character->count / 10) % 2 == 0) IMAGEMANAGER->alphaRender("아처", getMemDC(), line[i].left - 40, line[i].top - 50, 200);
					}
				}
			}
			if (isDrag[3])
			{
				sumNail[3] = RectMakeCenter(_ptMouse.x, _ptMouse.y, 80, 80);
				IMAGEMANAGER->render("메지션", getMemDC(), sumNail[3].left, sumNail[3].top);
				for (int i = 0; i < 3; i++)
				{
					if (PtInRect(&line[i], _ptMouse))
					{
						FrameRect(getMemDC(), line[i], RGB(255, 255, 0));
						if ((_character->count / 10) % 2 == 0) IMAGEMANAGER->alphaRender("메지션", getMemDC(), line[i].left - 40, line[i].top - 50, 200);
					}
				}
			}
		}







		//캐릭터 렉터 
		//for (int i = 0; i < field_player[0].size(); i++) FrameRect(getMemDC(), field_player[0][i].rc, RGB(0, 255, 255));
		//for (int i = 0; i < field_player[1].size(); i++) FrameRect(getMemDC(), field_player[1][i].rc, RGB(0, 255, 255));
		//for (int i = 0; i < field_player[2].size(); i++) FrameRect(getMemDC(), field_player[2][i].rc, RGB(0, 255, 255));
		//for (int i = 0; i < field_enemy[0].size(); i++) FrameRect(getMemDC(), field_enemy[0][i].rc, RGB(0, 255, 255));
		//for (int i = 0; i < field_enemy[1].size(); i++) FrameRect(getMemDC(), field_enemy[1][i].rc, RGB(0, 255, 255));
		//for (int i = 0; i < field_enemy[2].size(); i++) FrameRect(getMemDC(), field_enemy[2][i].rc, RGB(0, 255, 255));

		//공격범위 렉터
		//for (int i = 0; i < field_player[0].size(); i++) FrameRect(getMemDC(), field_player[0][i].rc_attRange, RGB(255, 0, 0));
		//for (int i = 0; i < field_player[1].size(); i++) FrameRect(getMemDC(), field_player[1][i].rc_attRange, RGB(255, 0, 0));
		//for (int i = 0; i < field_player[2].size(); i++) FrameRect(getMemDC(), field_player[2][i].rc_attRange, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[0].size(); i++) FrameRect(getMemDC(), field_enemy[0][i].rc_attRange, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[1].size(); i++) FrameRect(getMemDC(), field_enemy[1][i].rc_attRange, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[2].size(); i++) FrameRect(getMemDC(), field_enemy[2][i].rc_attRange, RGB(255, 0, 0));

		//공격 충돌체 렉터
		//for (int i = 0; i < field_player[0].size(); i++) FrameRect(getMemDC(), field_player[0][i].rc_att, RGB(255, 0, 0));
		//for (int i = 0; i < field_player[1].size(); i++) FrameRect(getMemDC(), field_player[1][i].rc_att, RGB(255, 0, 0));
		//for (int i = 0; i < field_player[2].size(); i++) FrameRect(getMemDC(), field_player[2][i].rc_att, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[0].size(); i++) FrameRect(getMemDC(), field_enemy[0][i].rc_att, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[1].size(); i++) FrameRect(getMemDC(), field_enemy[1][i].rc_att, RGB(255, 0, 0));
		//for (int i = 0; i < field_enemy[2].size(); i++) FrameRect(getMemDC(), field_enemy[2][i].rc_att, RGB(255, 0, 0));

		//라인
		//for (int i = 0; i < 3; i++) FrameRect(getMemDC(), line[i], RGB(255, 255, 0));
		//for (int i = 0; i < 4; i++) FrameRect(getMemDC(), sumNail[i], RGB(0, 255, 255));
		//for (int i = 0; i < 3; i++) FrameRect(getMemDC(), sumNailSkill[i], RGB(0, 255, 255));

		//카메라 렉트
		//FrameRect(getMemDC(), camara_rc, RGB(0, 255, 255));



			//==================================================

		_userSkill->render();

		Rectangle(getMemDC(), miniMap);

		IMAGEMANAGER->scaleRender("라인", getMemDC(), miniMap.left, miniMap.top, 0.2f);
		//IMAGEMANAGER->scaleRender("배경.미니맵5", getMemDC(), miniMap.left, miniMap.top, 0.3f);




		//==================================미니맵================================================================
		//추가한거



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


			MiniMeteorCircleX = _userSkill->_Meteor->Meteor.x;																					//추가한거ㅓ
			MiniMeteorX = _userSkill->_Meteor->Meteor_Coordinates.x;																			//추가한거ㅓ
																																				//추가한거ㅓ
			IMAGEMANAGER->scaleFrameRender("Meteor_Circle", getMemDC(),																			//추가한거ㅓ
				getPosition(1415, MiniMeteorCircleX, 283) + 280,																				//추가한거ㅓ
				getPosition(600, IMAGEMANAGER->findImage("Meteor_Circle")->boudingBox().top, 100) - 10,											//추가한거ㅓ
				IMAGEMANAGER->findImage("Meteor_Circle")->getFrameX(), IMAGEMANAGER->findImage("Meteor_Circle")->getFrameY(), 0.2f);			//추가한거ㅓ
																																				//추가한거ㅓ
																																				//추가한거ㅓ
			IMAGEMANAGER->scaleFrameRender("Meteor", getMemDC(),																				//추가한거ㅓ
				getPosition(1415, MiniMeteorX, 283) + 280,																						//추가한거ㅓ
				getPosition(600, IMAGEMANAGER->findImage("Meteor")->boudingBox().top, 100) + -15,													//추가한거ㅓ
				IMAGEMANAGER->findImage("Meteor")->getFrameX(), IMAGEMANAGER->findImage("Meteor")->getFrameY(), 0.2f);							//추가한거ㅓ
																																				//추가한거ㅓ
		}


		//==================================미니맵================================================================

	}

}




// < 함수 부 > =============================================================


//카메라
void stage::camera()
{
	//카메라 상자 만들기
	camara_rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, 80, 10);

	//맵 오른쪽으로 이동
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


		//라인이동
		for (int i = 0; i < 3; i++)
		{

			line[i].left -= 5;
			line[i].right -= 5;
			
			//다이 이미지 처리
			for (int j = 0; j < field_player_die[i].size(); j++)
			{
				field_player_die[i][j].x -= 5;
			}
			//다이 이미지 처리
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

	//맵 왼쪽으로 이동
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

			//다이 이미지 처리
			for (int j = 0; j < field_player_die[i].size(); j++)
			{
				field_player_die[i][j].x += 5;
			}
			//다이 이미지 처리
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

//소환함수(히어로)
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
				//3.필드 위 소환 범위 체크
				if (PtInRect(&line[i], _ptMouse) && playerfood >= 3)
				{
					//놓았을떄 라인위에 냅두기
					_character->hero[0].x = line[i].left;
					_character->hero[0].y = line[i].top - 50;
					_character->hero[0].rc = RectMakeCenter(_character->hero[0].x, _character->hero[0].y, 256 / 2, 311 / 2);

					//식량값 3임
					playerfood -= 3;
					_character->hero[0].gravity = 0;

					//4.소환 범위에서 마우스 떼면 소환 + field_player 벡터에 넣어주기
					//라인에 놓았으면 넣고 다시 썸네일은 원래위치로 돌려보내기
					field_player[i].push_back(_character->hero[0]);
					hpBar(i, true, BOSS);
					field_player_die[i].push_back(hero_die); //다이 이미지 준비 해주기

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
//소환함수(워리어)
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
				//3.필드 위 소환 범위 체크
				if (PtInRect(&line[i], _ptMouse) && playerfood >= 3)
				{
					//놓았을떄 라인위에 냅두기
					_character->worrior[0].x = line[i].left + RND->range(-4, 4);
					_character->worrior[0].y = line[i].top;
					_character->worrior[0].rc = RectMakeCenter(_character->worrior[0].x, _character->worrior[0].y, 80, 80);

					//식량값 3임
					playerfood -= 3;
					_character->worrior[0].gravity = 0;

					//4.소환 범위에서 마우스 떼면 소환 + field_player 벡터에 넣어주기
					//라인에 놓았으면 넣고 다시 썸네일은 원래위치로 돌려보내기
					field_player[i].push_back(_character->worrior[0]);
					hpBar(i, true, WORRIOR);
					field_player_die[i].push_back(worrior_die); //다이 이미지 준비 해주기

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
//소환함수(아쳐)
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
				//3.필드 위 소환 범위 체크
				if (PtInRect(&line[i], _ptMouse) && playerfood >= 3)
				{
					//놓았을떄 라인위에 냅두기
					_character->archer[0].x = line[i].left;
					_character->archer[0].y = line[i].top;
					_character->archer[0].rc = RectMakeCenter(_character->archer[0].x, _character->archer[0].y, 80, 80);

					//식량값 3임
					playerfood -= 3;
					_character->archer[0].gravity = 0;

					//4.소환 범위에서 마우스 떼면 소환 + field_player 벡터에 넣어주기
					//라인에 놓았으면 넣고 다시 썸네일은 원래위치로 돌려보내기
					field_player[i].push_back(_character->archer[0]);
					hpBar(i, true, ARCHER);
					field_player_die[i].push_back(archer_die); //다이 이미지 준비 해주기

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
//소환함수(메지션)
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
				//3.필드 위 소환 범위 체크
				if (PtInRect(&line[i], _ptMouse) && playerfood >= 3)
				{
					//놓았을떄 라인위에 냅두기
					_character->magician[0].x = line[i].left;
					_character->magician[0].y = line[i].top;
					_character->magician[0].rc = RectMakeCenter(_character->magician[0].x, _character->magician[0].y, 80, 80);

					//식량값 3임
					playerfood -= 3;
					_character->magician[0].gravity = 0;

					//4.소환 범위에서 마우스 떼면 소환 + field_player 벡터에 넣어주기
					//라인에 놓았으면 넣고 다시 썸네일은 원래위치로 돌려보내기
					field_player[i].push_back(_character->magician[0]);
					hpBar(i, true, MAGICIAN);
					field_player_die[i].push_back(magician_die); //다이 이미지 준비 해주기

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
//소환함수(적)
void stage::summon_AI()
{


	if (_character->count > 1)
	{
		for (int i = 0; i < 3; i++)
		{
			if (field_enemy[i].size() < 20)
			{
				int a;
				// 워리어 소환
				if (KEYMANAGER->isOnceKeyDown('A'))
				{
					int a;
					a = RND->range(3);

					//필드 적 1번라인 넣을떄
					if (a == 0)
					{

						_character->worrior[1].x = line[0].right;
						_character->worrior[1].y = line[0].top;
						_character->worrior[1].rc = RectMake(_character->worrior[1].x, _character->worrior[1].y, 80, 80);


						field_enemy[0].push_back(_character->worrior[1]);
						hpBar(0, false, WORRIOR);
						field_enemy_die[0].push_back(worrior_enemy_die); //다이 이미지 준비 해주기
					}
					//필드 적 2번라인 넣을떄
					if (a == 1)
					{
						_character->worrior[1].x = line[1].right;
						_character->worrior[1].y = line[1].top;
						_character->worrior[1].rc = RectMake(_character->worrior[1].x, _character->worrior[1].y, 80, 80);


						field_enemy[1].push_back(_character->worrior[1]);
						hpBar(1, false, WORRIOR);
						field_enemy_die[1].push_back(worrior_enemy_die); //다이 이미지 준비 해주기
					}
					//필드 적 3번라인 넣을떄
					if (a == 2)
					{
						_character->worrior[1].x = line[2].right;
						_character->worrior[1].y = line[2].top;
						_character->worrior[1].rc = RectMake(_character->worrior[1].x, _character->worrior[1].y, 80, 80);


						field_enemy[2].push_back(_character->worrior[1]);
						hpBar(2, false, WORRIOR);
						field_enemy_die[2].push_back(worrior_enemy_die); //다이 이미지 준비 해주기
					}
				}
				if (KEYMANAGER->isOnceKeyDown('S'))
				{
					int b;
					b = RND->range(3);

					//필드 적 1번라인 넣을떄
					if (b == 0)
					{
						_character->archer[1].x = line[0].right;
						_character->archer[1].y = line[0].top;
						_character->archer[1].rc = RectMake(_character->archer[1].x, _character->archer[1].y, 80, 80);


						field_enemy[0].push_back(_character->archer[1]);
						hpBar(0, false, ARCHER);
						field_enemy_die[0].push_back(archer_enemy_die); //다이 이미지 준비 해주기
					}
					//필드 적 2번라인 넣을떄
					if (b == 1)
					{
						_character->archer[1].x = line[1].right;
						_character->archer[1].y = line[1].top;
						_character->archer[1].rc = RectMake(_character->archer[1].x, _character->archer[1].y, 80, 80);


						field_enemy[1].push_back(_character->archer[1]);
						hpBar(1, false, ARCHER);
						field_enemy_die[1].push_back(archer_enemy_die); //다이 이미지 준비 해주기
					}
					//필드 적 3번라인 넣을떄
					if (b == 2)
					{
						_character->archer[1].x = line[2].right;
						_character->archer[1].y = line[2].top;
						_character->archer[1].rc = RectMake(_character->archer[1].x, _character->archer[1].y, 80, 80);


						field_enemy[2].push_back(_character->archer[1]);
						hpBar(2, false, ARCHER);
						field_enemy_die[2].push_back(archer_enemy_die); //다이 이미지 준비 해주기
					}

				}

				//적매시션 소환함수
				if (KEYMANAGER->isOnceKeyDown('D'))
				{
					int c;
					c = RND->range(3);

					//필드 적 1번라인 넣을떄
					if (c == 0)
					{
						_character->magician[1].x = line[0].right;
						_character->magician[1].y = line[0].top;
						_character->magician[1].rc = RectMake(_character->magician[1].x, _character->magician[1].y, 80, 80);


						field_enemy[0].push_back(_character->magician[1]);
						hpBar(0, false, MAGICIAN);
						field_enemy_die[0].push_back(magician_enemy_die); //다이 이미지 준비 해주기
					}
					//필드 적 2번라인 넣을떄
					if (c == 1)
					{
						_character->magician[1].x = line[1].right;
						_character->magician[1].y = line[1].top;
						_character->magician[1].rc = RectMake(_character->magician[1].x, _character->magician[1].y, 80, 80);


						field_enemy[1].push_back(_character->magician[1]);
						hpBar(1, false, MAGICIAN);
						field_enemy_die[1].push_back(magician_enemy_die); //다이 이미지 준비 해주기
					}
					//필드 적 3번라인 넣을떄
					if (c == 2)
					{
						_character->magician[1].x = line[2].right;
						_character->magician[1].y = line[2].top;
						_character->magician[1].rc = RectMake(_character->magician[1].x, _character->magician[1].y, 80, 80);


						field_enemy[2].push_back(_character->magician[1]);
						hpBar(2, false, MAGICIAN);
						field_enemy_die[2].push_back(magician_enemy_die); //다이 이미지 준비 해주기
					}

				}

				//적보스 소환
				if (KEYMANAGER->isOnceKeyDown('Q'))
				{
					int c;
					c = RND->range(3);

					//필드 적 1번라인 넣을떄
					if (c == 0)
					{
						//_character->hero[0].x = line[i].left;
						//_character->hero[0].y = line[i].top - 50;
						_character->hero[1].x = line[0].right;
						_character->hero[1].y = line[0].top - 50;
						_character->hero[1].rc = RectMake(_character->hero[1].x, _character->hero[1].y, 80, 80);


						field_enemy[0].push_back(_character->hero[1]);
						hpBar(0, false, BOSS);
						field_enemy_die[0].push_back(hero_enemy_die); //다이 이미지 준비 해주기
					}
					//필드 적 2번라인 넣을떄
					if (c == 1)
					{
						_character->hero[1].x = line[1].right;
						_character->hero[1].y = line[1].top - 50;
						_character->hero[1].rc = RectMake(_character->hero[1].x, _character->hero[1].y, 80, 80);


						field_enemy[1].push_back(_character->hero[1]);
						hpBar(1, false, BOSS);
						field_enemy_die[1].push_back(hero_enemy_die); //다이 이미지 준비 해주기
					}
					//필드 적 3번라인 넣을떄
					if (c == 2)
					{
						_character->hero[1].x = line[2].right;
						_character->hero[1].y = line[2].top - 50;
						_character->hero[1].rc = RectMake(_character->hero[1].x, _character->hero[1].y, 80, 80);


						field_enemy[2].push_back(_character->hero[1]);
						hpBar(2, false, BOSS);
						field_enemy_die[2].push_back(hero_enemy_die); //다이 이미지 준비 해주기
					}


				}
			}
		}
	}
}

//적 타워 소환
void stage::summon_tower_AI(int lineNum, int x, int y)
{
	//놓았을떄 라인위에 냅두기
	_character->tower[1].x = x;
	_character->tower[1].y = y;
	_character->tower[1].rc = RectMakeCenter(_character->tower[1].x, _character->tower[1].y, 160 / 1.6, 220 / 1.6);
	//_character->tower[1].hpBar->init("progressBarFront", "progressBarBack", _character->tower[1].rc.left, _character->tower[1].rc.top - 8, 100, 8);
	_character->tower[1].gravity = 0;

	//4.소환 범위에서 마우스 떼면 소환 + field_player 벡터에 넣어주기
	//라인에 놓았으면 넣고 다시 썸네일은 원래위치로 돌려보내기
	field_enemy[lineNum].push_back(_character->tower[1]);
	field_enemy_die[0].push_back(tower_enemy_die); //다이 이미지 준비 해주기
}

//케슬 소환
void stage::summon_castle()
{
	//아군
	{
		_character->castle[0].rc = RectMakeCenter(_character->castle[0].x, _character->castle[0].y, 397 / 1.4, 484 / 1.4);
		_character->castle[0].gravity = 0;
		field_player[0].push_back(_character->castle[0]);
		hpBar(0, true, _character->castle[0].sort);
		field_player_die[0].push_back(castle_die);
	}
	//적군
	{
		_character->castle[1].rc = RectMakeCenter(_character->castle[1].x, _character->castle[1].y, 423 / 1.3, 445 / 1.3);
		_character->castle[1].gravity = 0;
		field_enemy[0].push_back(_character->castle[1]);
		hpBar(0, false, _character->castle[1].sort);
		field_enemy_die[0].push_back(castle_enemy_die);
	}
}


//다이 모션 업데이트
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

//음식
void stage::food(int count)
{
	if (playerfood < 20)
	{
		if (count % 50 == 0)
		{
			playerfood++;
		}
	}
	//적군 식량 최대치 조절
	if (enemyfood < 20)
	{
		if (count % 50 == 0)
		{
			enemyfood++;
		}
	}
}

//플레이어 이동 함수 line[i] = RectMake(stage1RECT.left + 100, 330 + i * 46, 1000, 36);
void stage::runPlayer(int lineNum)
{
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		if (field_player[lineNum][i].state == RUN && field_player[lineNum][i].sort != TOWER && field_player[lineNum][i].sort != CASTLE)
		{
			field_player[lineNum][i].Mx += field_player[lineNum][i].run_spd / 4; //추가한거 



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
		//렉트 업데이트 summon_castle(-64, 100, 1200 - (423 / 1.3) + 64, 108);
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
//적 이동 함수
void stage::runEnemy(int lineNum)
{
	for (int i = 0; i < field_enemy[lineNum].size(); i++)
	{
		if (field_enemy[lineNum][i].state == RUN && field_enemy[lineNum][i].sort != TOWER && field_enemy[lineNum][i].sort != CASTLE)
		{

			field_enemy[lineNum][i].Mx += field_enemy[lineNum][i].run_spd / 4; //추가한거 



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


//체력바 업데이드(출력 위치도)
void stage::updateHpBar()
{
	for (int j = 0; j < 3; j++)
	{
		//아군
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
		//적군
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

//체력바 생성
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

//각 라인 충돌 시 => 어택 상태로 변경
void stage::bump(int lineNum)
{
	RECT temp;
	//플레이어 체크
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		for (int j = 0; j < field_enemy[lineNum].size(); j++)
		{
			if (IntersectRect(&temp, &field_player[lineNum][i].rc_attRange, &field_enemy[lineNum][j].rc))
			{
				field_player[lineNum][i].state = ATTACK;

				if (field_player[lineNum][i].state == ATTACK)
				{
					if (_character->count % 100 == 0)//공속
					{
						field_player[lineNum][i].fire = true;
						field_player[lineNum][i].fire_motion = true;
						field_player[lineNum][i].rc_att = RectMakeCenter(field_player[lineNum][i].x, field_player[lineNum][i].y, 52, 16);
						//SOUNDMANAGER->play("공격사운드_워리어");
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
	
	

	//에너미 체크
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


	//아군이 공격
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		for (int j = 0; j < field_enemy[lineNum].size(); j++)
		{
			if (field_player[lineNum][i].fire)
			{
				//발사체 렉트 업데이트
				field_player[lineNum][i].rc_att.left += 3;
				field_player[lineNum][i].rc_att.right += 3;
				if (IntersectRect(&temp, &field_player[lineNum][i].rc_att, &field_enemy[lineNum][j].rc)) //충돌 체크
				{
					field_enemy[lineNum][j].hp = field_enemy[lineNum][j].hp - field_player[lineNum][i].att;
					field_player[lineNum][i].fire = false;
					//피격 이펙트 on
					field_enemy[lineNum][j].isHit = true;
				}
			}
			if (!IntersectRect(&temp, &field_player[lineNum][i].rc_att, &field_player[lineNum][i].rc_attRange)) //범위 넘어가면 초기화
			{
				field_player[lineNum][i].fire = false;
				field_player[lineNum][i].fire_motion = false;
			}
		}
	}
	//적군이 공격 
	for (int i = 0; i < field_enemy[lineNum].size(); i++)
	{
		for (int j = 0; j < field_player[lineNum].size(); j++)
		{
			if (field_enemy[lineNum][i].fire)
			{
				//발사체 렉트 업데이트
				field_enemy[lineNum][i].rc_att.left -= 3;
				field_enemy[lineNum][i].rc_att.right -= 3;
				if (IntersectRect(&temp, &field_enemy[lineNum][i].rc_att, &field_player[lineNum][j].rc)) //충돌 체크
				{
					field_player[lineNum][j].hp = field_player[lineNum][j].hp - field_enemy[lineNum][i].att;//공격
					field_enemy[lineNum][i].fire = false;
					//피격 이펙트 on
					field_player[lineNum][j].isHit = true;
				}
			}
			if (!IntersectRect(&temp, &field_enemy[lineNum][i].rc_att, &field_enemy[lineNum][i].rc_attRange)) //범위 넘어가면 초기화
			{
				field_enemy[lineNum][i].fire = false;
				field_enemy[lineNum][i].fire_motion = false;
			}
		}
	}
}

//각 라인 충돌 시 => 어택 상태로 변경
void stage::bumpCastle(int lineNum)
{
	RECT temp;
	//플레이어 체크
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		for (int j = 0; j < field_enemy[0].size(); j++)
		{
			if (IntersectRect(&temp, &field_player[lineNum][i].rc_attRange, &field_enemy[0][0].rc))
			{
				field_player[lineNum][i].state = ATTACK;

				if (field_player[lineNum][i].state == ATTACK)
				{
					if (_character->count % 100 == 0)//공속
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



	//에너미 체크
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


	//아군이 공격
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		for (int j = 0; j < field_enemy[0].size(); j++)
		{
			if (field_player[lineNum][i].fire)
			{
				//발사체 렉트 업데이트
				field_player[lineNum][i].rc_att.left += 3;
				field_player[lineNum][i].rc_att.right += 3;
				if (IntersectRect(&temp, &field_player[lineNum][i].rc_att, &field_enemy[0][0].rc)) //충돌 체크
				{
					field_enemy[0][0].hp = field_enemy[0][0].hp - field_player[lineNum][i].att;
					field_player[lineNum][i].fire = false;
					//피격 이펙트 on
					field_enemy[0][0].isHit = true;
				}
			}
			if (!IntersectRect(&temp, &field_player[lineNum][i].rc_att, &field_player[lineNum][i].rc_attRange)) //범위 넘어가면 초기화
			{
				field_player[lineNum][i].fire = false;
				field_player[lineNum][i].fire_motion = false;
			}
		}
	}
	//적군이 공격 
	for (int i = 0; i < field_enemy[lineNum].size(); i++)
	{
		for (int j = 0; j < field_player[0].size(); j++)
		{
			if (field_enemy[lineNum][i].fire)
			{
				//발사체 렉트 업데이트
				field_enemy[lineNum][i].rc_att.left -= 3;
				field_enemy[lineNum][i].rc_att.right -= 3;
				if (IntersectRect(&temp, &field_enemy[lineNum][i].rc_att, &field_player[0][0].rc)) //충돌 체크
				{
					field_player[0][0].hp = field_player[0][0].hp - field_enemy[lineNum][i].att;//공격
					field_enemy[lineNum][i].fire = false;
					//피격 이펙트 on
					field_player[0][0].isHit = true;
				}
			}
			if (!IntersectRect(&temp, &field_enemy[lineNum][i].rc_att, &field_enemy[lineNum][i].rc_attRange)) //범위 넘어가면 초기화
			{
				field_enemy[lineNum][i].fire = false;
				field_enemy[lineNum][i].fire_motion = false;
			}
		}
	}
}

//플레이어 삭제
void stage::removeplayer(int lineNum)
{
	for (int i = 0; i < field_player[lineNum].size(); i++)
	{
		if (field_player[lineNum].size() != 0)
		{
			if (field_player[lineNum][i].hp <= 0)
			{

				field_player_die[lineNum][i].isDie = true; //다이 이미지 재생 시점
				field_player_die[lineNum][i].x = field_player[lineNum][i].rc.left - 40;// field_player[i][j].y
				field_player_die[lineNum][i].y = field_player[lineNum][i].y - 20;

				field_player[lineNum][i].state = DIE;
				SOUNDMANAGER->play("다이_아군");
				field_player[lineNum].erase(field_player[lineNum].begin() + i);
				field_player_hpBar[lineNum].erase(field_player_hpBar[lineNum].begin() + i);
				i--;
			}
		}
	}
}
//에너미 삭제
void stage::removeEnemy(int lineNum)
{
	for (int i = 0; i < field_enemy[lineNum].size(); i++)
	{
		if (field_enemy[lineNum][i].hp <= 0)
		{
			field_enemy_die[lineNum][i].isDie = true; //다이 이미지 재생 시점
			field_enemy_die[lineNum][i].x = field_enemy[lineNum][i].rc.left + 60;// field_player[i][j].y
			field_enemy_die[lineNum][i].y = field_enemy[lineNum][i].y -20;

			field_enemy[lineNum][i].state = DIE;
			SOUNDMANAGER->play("다이_적");
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
		SOUNDMANAGER->play("공격사운드_영웅");
		break;
	case WORRIOR:
		SOUNDMANAGER->play("공격사운드_워리어");
		break;
	case ARCHER:
		SOUNDMANAGER->play("공격사운드_아쳐");
		break;
	case MAGICIAN:
		SOUNDMANAGER->play("공격_메이지", 0.6f);
		break;
	case TOWER:
		SOUNDMANAGER->play("공격사운드_아쳐");
		break;
	case CASTLE:
		SOUNDMANAGER->play("공격사운드_아쳐");
		break;
	}
}

void stage::sortSound_enemy(int lineNum, int i)
{
	switch (field_enemy[lineNum][i].sort)
	{
	case BOSS:
		SOUNDMANAGER->play("공격사운드_영웅");
		break;
	case WORRIOR:
		SOUNDMANAGER->play("공격사운드_워리어");
		break;
	case ARCHER:
		SOUNDMANAGER->play("공격사운드_아쳐");
		break;
	case MAGICIAN:
		SOUNDMANAGER->play("공격_메이지", 0.6f);
		break;
	case TOWER:
		SOUNDMANAGER->play("공격사운드_아쳐");
		break;
	case CASTLE:
		SOUNDMANAGER->play("공격사운드_아쳐");
		break;
	}
}



