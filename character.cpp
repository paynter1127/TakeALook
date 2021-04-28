#include "stdafx.h"
#include "character.h"


HRESULT character::init()
{

	//시간 조건
	count = 0;


	//히어로 초기화
	{
		//제로 초기화
		ZeroMemory(&hero[0], sizeof(tagCharacter));
		ZeroMemory(&hero[1], sizeof(tagCharacter));
		//여기 아래로 캐릭터 초기화 할 것
		//========================================================================우리편

		//이미지 초기화
		hero[0].img = IMAGEMANAGER->findImage("히어로");
		hero[0].isHit = false;
		hero[0].sort = BOSS;
		hero[0].frame_count = 0;
		hero[0].lv = 1;
		hero[0].hp = 14 + 2 * hero[0].lv;
		hero[0].maxhp = 14 + 2 * hero[0].lv;
		hero[0].att = 4 + hero[0].lv;
		hero[0].att_spd = 1.1f;
		hero[0].run_spd = 2;
		hero[0].price = 100 * hero[0].lv;
		hero[0].gravity = 0.0f;
		hero[0].x = 460;
		hero[0].y = 540;
		hero[0].rc = RectMakeCenter(hero[0].x, hero[0].y, 80, 80);
		hero[0].rc_attRange = RectMakeCenter(hero[0].x, hero[0].y, 80, 80);
		hero[0].fire = false;
		hero[0].fire_motion = false;
		hero[0].rc_att = RectMakeCenter(hero[0].x, hero[0].y, 52, 16);
		hero[0].img_att = IMAGEMANAGER->findImage("슬레쉬");
		hero[0].state = RUN;
		hero[0].img_weapon = IMAGEMANAGER->findImage("보스칼");
		hero[0].angle = 0; //회전 각
		hero[0].isDown = true; //회전 방향


		hero[0].Mx = hero[0].x;

		//========================================================================적군
		//적이미지 만들기
		hero[1].img = IMAGEMANAGER->findImage("히어로_적");
		hero[1].isHit = false;
		hero[1].sort = BOSS;
		hero[1].frame_count = 0;
		hero[1].lv = 1;
		hero[1].hp = 14 + 2 * hero[1].lv;
		hero[1].maxhp = 14 + 2 * hero[1].lv;
		hero[1].att = 4 + hero[1].lv;
		hero[1].att_spd = 1.1f;
		hero[1].run_spd = -2;
		hero[1].price = 100 * hero[1].lv;
		hero[1].gravity = 0.0f;
		hero[1].x = 450;
		hero[1].y = 550;
		hero[1].rc = RectMakeCenter(hero[1].x, hero[1].y, 80, 80);
		hero[1].rc_attRange = RectMakeCenter(hero[1].x, hero[1].y, 80, 80);
		hero[1].fire = false;
		hero[1].fire_motion = false;
		hero[1].rc_att = RectMakeCenter(hero[1].x, hero[1].y, 52, 16);
		hero[1].img_att = IMAGEMANAGER->findImage("슬레쉬_적");
		hero[1].state = RUN;
		hero[1].img_weapon = IMAGEMANAGER->findImage("보스칼_적");
		hero[1].angle = 0; //회전 각
		hero[1].isDown = true; //회전 방향

		hero[1].Mx = hero[1].x;
	}

	//워리어 초기화
	{
		//제로 초기화
		ZeroMemory(&worrior[0], sizeof(tagCharacter));
		ZeroMemory(&worrior[1], sizeof(tagCharacter));
		//여기 아래로 캐릭터 초기화 할 것
		//========================================================================우리편

		//이미지 초기화
		worrior[0].img = IMAGEMANAGER->findImage("워리어");
		worrior[0].isHit = false;
		worrior[0].sort = WORRIOR;
		worrior[0].frame_count = 0;
		worrior[0].lv = 1;
		worrior[0].hp = 14 + 2 * worrior[0].lv;
		worrior[0].maxhp = 14 + 2 * worrior[0].lv;
		worrior[0].att = 4 + worrior[0].lv;
		worrior[0].att_spd = 1.1f;
		worrior[0].run_spd = 4;
		worrior[0].price = 100 * worrior[0].lv;
		worrior[0].gravity = 0.0f;
		worrior[0].x = 460;
		worrior[0].y = 540;
		worrior[0].rc = RectMakeCenter(worrior[0].x, worrior[0].y, 80, 80);
		worrior[0].rc_attRange = RectMakeCenter(worrior[0].x, worrior[0].y, 80, 80);
		worrior[0].fire = false;
		worrior[0].fire_motion = false;
		worrior[0].rc_att = RectMakeCenter(worrior[0].x, worrior[0].y, 52, 16);
		worrior[0].img_att = IMAGEMANAGER->findImage("슬레쉬");
		worrior[0].state = RUN;
		worrior[0].img_weapon = IMAGEMANAGER->findImage("칼");
		worrior[0].angle = 0; //회전 각
		worrior[0].isDown = true; //회전 방향
		
		worrior[0].Mx = worrior[0].x;
		
		//========================================================================적군
		//적이미지 만들기
		worrior[1].img = IMAGEMANAGER->findImage("워리어_적");
		worrior[1].isHit = false;
		worrior[1].sort = WORRIOR;
		worrior[1].frame_count = 0;
		worrior[1].lv = 1;
		worrior[1].hp = 14 + 2 * worrior[1].lv;
		worrior[1].maxhp = 14 + 2 * worrior[1].lv;
		worrior[1].att = 4 + worrior[1].lv;
		worrior[1].att_spd = 1.1f;
		worrior[1].run_spd = -4;
		worrior[1].price = 100 * worrior[1].lv;
		worrior[1].gravity = 0.0f;
		worrior[1].x = 450;
		worrior[1].y = 550;
		worrior[1].rc = RectMakeCenter(worrior[1].x, worrior[1].y, 80, 80);
		worrior[1].rc_attRange = RectMakeCenter(worrior[1].x, worrior[1].y, 80, 80);
		worrior[1].fire = false;
		worrior[1].fire_motion = false;
		worrior[1].rc_att = RectMakeCenter(worrior[1].x, worrior[1].y, 52, 16);
		worrior[1].img_att = IMAGEMANAGER->findImage("슬레쉬_적");
		worrior[1].state = RUN;
		worrior[1].img_weapon = IMAGEMANAGER->findImage("칼_적");
		worrior[1].angle = 0; //회전 각
		worrior[1].isDown = true; //회전 방향

		
		worrior[1].Mx = worrior[1].x;
	}

	//아처 초기화
	{
		//제로 초기화
		ZeroMemory(&archer[0], sizeof(tagCharacter));
		ZeroMemory(&archer[1], sizeof(tagCharacter));
		//여기 아래로 캐릭터 초기화 할 것
		//========================================================================우리편

		//이미지 초기화
		archer[0].img = IMAGEMANAGER->findImage("아처");
		archer[0].isHit = false;
		archer[0].sort = ARCHER;
		archer[0].frame_count = 0;
		archer[0].lv = 1;
		archer[0].hp = 4 + 2 * archer[0].lv;
		archer[0].maxhp = 4 + 2 * archer[0].lv;
		archer[0].att = 6 + archer[0].lv;
		archer[0].att_spd = 0.8f;
		archer[0].run_spd = 3.0f;
		archer[0].price = 120 * archer[0].lv;
		archer[0].gravity = 0.0f;
		archer[0].x = 460;
		archer[0].y = 540;
		archer[0].rc = RectMakeCenter(archer[0].x, archer[0].y, 80, 80);
		archer[0].rc_attRange = RectMake(archer[0].x, archer[0].rc.top, 200, 80);
		archer[0].fire = false;
		archer[0].fire_motion = false;
		archer[0].rc_att = RectMakeCenter(archer[0].x, archer[0].y, 52, 16);
		archer[0].img_att = IMAGEMANAGER->findImage("화살");
		archer[0].state = RUN;
		archer[0].img_weapon = IMAGEMANAGER->findImage("활");
		archer[0].angle = 0; //회전 각
		archer[0].isDown = true; //회전 방향

		archer[0].Mx = archer[0].x;

		//========================================================================적군
		//적이미지 만들기
		archer[1].img = IMAGEMANAGER->findImage("아처_적");
		archer[1].isHit = false;
		archer[1].sort = ARCHER;
		archer[1].frame_count = 0;
		archer[1].lv = 1;
		archer[1].hp = 4 + 2 * archer[1].lv;
		archer[1].maxhp = 4 + 2 * archer[1].lv;
		archer[1].att = 6 + archer[1].lv;
		archer[1].att_spd = 0.8f;
		archer[1].run_spd = -3;
		archer[1].price = 120 * archer[1].lv;
		archer[1].gravity = 0.0f;
		archer[1].x = 450;
		archer[1].y = 550;
		archer[1].rc = RectMakeCenter(archer[1].x, archer[1].y, 80, 80);
		archer[1].rc_attRange = RectMake(archer[1].x - 200, archer[1].rc.top, 200, 80);
		archer[1].fire = false;
		archer[1].fire_motion = false;
		archer[1].rc_att = RectMakeCenter(archer[1].x, archer[1].y, 52, 16);
		archer[1].img_att = IMAGEMANAGER->findImage("화살_적");
		archer[1].state = RUN;
		archer[1].img_weapon = IMAGEMANAGER->findImage("활_적");
		archer[1].angle = 0; //회전 각
		archer[1].isDown = true; //회전 방향

		archer[1].Mx = archer[1].x;

	}

	//메지션 초기화
	{
		//제로 초기화
		ZeroMemory(&magician[0], sizeof(tagCharacter));
		ZeroMemory(&magician[1], sizeof(tagCharacter));
		//여기 아래로 캐릭터 초기화 할 것
		//========================================================================우리편

		//이미지 초기화
		magician[0].img = IMAGEMANAGER->findImage("메지션");
		magician[0].isHit = false;
		magician[0].sort = MAGICIAN;
		magician[0].frame_count = 0;
		magician[0].lv = 1;
		magician[0].hp = 4 + 2 * magician[0].lv;
		magician[0].maxhp = 4 + 2 * magician[0].lv;
		magician[0].att = 10 + magician[0].lv;
		magician[0].att_spd = 0.4f;
		magician[0].run_spd = 2;
		magician[0].price = 200 * magician[0].lv;
		magician[0].gravity = 0.0f;
		magician[0].x = 460;
		magician[0].y = 540;
		magician[0].rc = RectMakeCenter(magician[0].x, magician[0].y, 80, 80);
		magician[0].rc_attRange = RectMake(magician[0].x, magician[0].rc.top, 300, 80);
		magician[0].fire = false;
		magician[0].fire_motion = false;
		magician[0].rc_att = RectMakeCenter(magician[0].x, magician[0].y, 52, 16);
		magician[0].img_att = IMAGEMANAGER->findImage("볼트");
		magician[0].state = RUN;
		magician[0].img_weapon = IMAGEMANAGER->findImage("지팡이");
		magician[0].angle = 0; //회전 각
		magician[0].isDown = true; //회전 방향

		magician[0].Mx = magician[0].x;

		//========================================================================적군
		//적이미지 만들기
		magician[1].img = IMAGEMANAGER->findImage("메지션_적");
		magician[1].isHit = false;
		magician[1].sort = MAGICIAN;
		magician[1].frame_count = 0;
		magician[1].lv = 1;
		magician[1].hp = 14 + 2 * magician[1].lv;
		magician[1].maxhp = 14 + 2 * magician[1].lv;
		magician[1].att = 10 + magician[1].lv;
		magician[1].att_spd = 0.4f;
		magician[1].run_spd = -2;
		magician[1].price = 200 * magician[1].lv;
		magician[1].gravity = 0.0f;
		magician[1].x = 450;
		magician[1].y = 550;
		magician[1].rc = RectMakeCenter(magician[1].x, magician[1].y, 80, 80);
		magician[1].rc_attRange = RectMake(magician[1].x - 300, magician[1].rc.top, 300, 80);
		magician[1].fire = false;
		magician[1].fire_motion = false;
		magician[1].rc_att = RectMakeCenter(magician[1].x, magician[1].y, 52, 16);
		magician[1].img_att = IMAGEMANAGER->findImage("볼트_적");
		magician[1].state = RUN;
		magician[1].img_weapon = IMAGEMANAGER->findImage("지팡이_적");
		magician[1].angle = 0; //회전 각
		magician[1].isDown = true; //회전 방향
		magician[1].Mx = magician[1].x;

	}

	//케슬 초기화
	{
		//제로 초기화
		ZeroMemory(&castle[0], sizeof(tagCharacter));
		ZeroMemory(&castle[1], sizeof(tagCharacter));
		//여기 아래로 캐릭터 초기화 할 것
		//========================================================================우리편

		//이미지 초기화
		castle[0].img = IMAGEMANAGER->findImage("케슬");
		castle[0].isHit = false;
		castle[0].sort = CASTLE;
		castle[0].frame_count = 0;
		castle[0].lv = 1;
		castle[0].hp = 200 + 2 * castle[0].lv;
		castle[0].maxhp = 200 + 2 * castle[0].lv;
		castle[0].att = 4 + castle[0].lv;
		castle[0].att_spd = 1.1f;
		castle[0].run_spd = 0;
		castle[0].price = 100 * castle[0].lv;
		castle[0].gravity = 0.0f;
		castle[0].x = 90;
		castle[0].y = 280;
		castle[0].rc = RectMakeCenter(castle[0].x, castle[0].y, 397 / 1.4, 484 / 1.4);
		castle[0].rc_attRange = RectMakeCenter(castle[0].x, castle[0].y, 397 / 1.4, 484 / 1.4);
		castle[0].fire = false;
		castle[0].fire_motion = false;
		castle[0].rc_att = RectMakeCenter(castle[0].x, castle[0].y, 52, 16);
		castle[0].img_att = IMAGEMANAGER->findImage("화살");
		castle[0].state = RUN;
		castle[0].img_weapon = IMAGEMANAGER->findImage("빈페이지");
		castle[0].angle = 0; //회전 각
		castle[0].isDown = true; //회전 방향

		castle[0].Mx = castle[0].x;

		//========================================================================적군
		//적이미지 만들기
		castle[1].img = IMAGEMANAGER->findImage("케슬_적");
		castle[1].isHit = false;
		castle[1].sort = CASTLE;
		castle[1].frame_count = 0;
		castle[1].lv = 1;
		castle[1].hp = 14 + 2 * castle[1].lv;
		castle[1].maxhp = 14 + 2 * castle[1].lv;
		castle[1].att = 4 + castle[1].lv;
		castle[1].att_spd = 1.1f;
		castle[1].run_spd = -2;
		castle[1].price = 100 * castle[1].lv;
		castle[1].gravity = 0.0f;
		castle[1].x = 1090; //(-64, 100, 1200 - (423 / 1.3) + 64, 108);
		castle[1].y = 280;
		castle[1].rc = RectMakeCenter(castle[1].x, castle[1].y, 423 / 1.3, 445 / 1.3);
		castle[1].rc_attRange = RectMakeCenter(castle[1].x, castle[1].y, 423 / 1.3, 445 / 1.3);
		castle[1].fire = false;
		castle[1].fire_motion = false;
		castle[1].rc_att = RectMakeCenter(castle[1].x, castle[1].y, 52, 16);
		castle[1].img_att = IMAGEMANAGER->findImage("화살_적");
		castle[1].state = RUN;
		castle[1].img_weapon = IMAGEMANAGER->findImage("빈페이지");
		castle[1].angle = 0; //회전 각
		castle[1].isDown = true; //회전 방향

		castle[1].Mx = castle[1].x;

	}

	//타워 초기화
	{
		//제로 초기화
		ZeroMemory(&tower[0], sizeof(tagCharacter));
		ZeroMemory(&tower[1], sizeof(tagCharacter));
		//여기 아래로 캐릭터 초기화 할 것
		//========================================================================우리편

		//이미지 초기화
		tower[0].img = IMAGEMANAGER->findImage("타워");
		tower[0].isHit = false;
		tower[0].sort = TOWER;
		tower[0].frame_count = 0;
		tower[0].lv = 1;
		tower[0].hp = 200 + 2 * tower[0].lv;
		tower[0].maxhp = 200 + 2 * tower[0].lv;
		tower[0].att = 4 + tower[0].lv;
		tower[0].att_spd = 1.1f;
		tower[0].run_spd = 0;
		tower[0].price = 100 * tower[0].lv;
		tower[0].gravity = 0.0f;
		tower[0].x = 0;
		tower[0].y = 0;
		tower[0].rc = RectMakeCenter(tower[0].x, tower[0].y, 163 / 1.6, 244 / 1.6);
		tower[0].rc_attRange = RectMake(tower[0].x, tower[0].y, 340, 80);
		tower[0].fire = false;
		tower[0].fire_motion = false;
		tower[0].rc_att = RectMakeCenter(tower[0].x, tower[0].y, 52, 16);
		tower[0].img_att = IMAGEMANAGER->findImage("화살");
		tower[0].state = RUN;
		tower[0].img_weapon = IMAGEMANAGER->findImage("빈페이지");
		tower[0].angle = 0; //회전 각
		tower[0].isDown = true; //회전 방향

		tower[0].Mx = tower[0].x;

		//========================================================================적군
		//적이미지 만들기
		tower[1].img = IMAGEMANAGER->findImage("타워_적");
		tower[1].isHit = false;
		tower[1].sort = TOWER;
		tower[1].frame_count = 0;
		tower[1].lv = 1;
		tower[1].hp = 14 + 2 * tower[1].lv;
		tower[1].maxhp = 14 + 2 * tower[1].lv;
		tower[1].att = 4 + tower[1].lv;
		tower[1].att_spd = 1.1f;
		tower[1].run_spd = 0;
		tower[1].price = 100 * tower[1].lv;
		tower[1].gravity = 0.0f;
		//tower[1].x = WINSIZEX + 64 - (423 / 1.3);
		tower[1].x = 700;
		tower[1].y = 300;
		tower[1].rc = RectMakeCenter(tower[1].x, tower[1].y, 160 / 1.6, 220 / 1.6);
		tower[1].rc_attRange = RectMake(tower[1].x - 340, tower[1].y, 340, 80);
		tower[1].fire = false;
		tower[1].fire_motion = false;
		tower[1].rc_att = RectMakeCenter(tower[1].x, tower[1].y, 52, 16);
		tower[1].img_att = IMAGEMANAGER->findImage("화살_적");
		tower[1].state = RUN;
		tower[1].img_weapon = IMAGEMANAGER->findImage("빈페이지");
		tower[1].angle = 0; //회전 각
		tower[1].isDown = true; //회전 방향


		tower[1].Mx = tower[1].x;


	}


	return S_OK;
}

void character::release()
{
	
}


