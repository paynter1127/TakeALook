#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	//IMAGEMANAGER->addFrameImage("숫자", "numSprite.bmp", 360, 42, 10, 1);
	IMAGEMANAGER->addFrameImage("숫자22", "숫자2.bmp", 360, 42, 10, 1, true, RGB(255, 0, 255));
	i = 0;
	//로딩
	SOUNDMANAGER->addSound("256113__nckn__done", "256113__nckn__done.wav", false, false);
	
	

	isDone = false;

	return S_OK;
}

void loadingScene::release()
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("버튼");
			loadPlayer();
			SCENEMANAGER->loadScene("logo");
		}
		//SCENEMANAGER->loadScene("stage");
	}
}

void loadingScene::render()
{
	//로딩클래스 렌더
	_loading->render();
	imageNum("숫자22", getMemDC(), 744, 529, (_loading->getCurrentGauge() * 100) / _loading->getLoadItem().size(), 26); //완료

	textOutFont(getMemDC(), 184, 102, "3개의 라인에 아군", 20, RGB(255, 255, 0));
	textOutFont(getMemDC(), 184, 126, "병력을 소환해 보세요", 20, RGB(255, 255, 0));

	textOutFont(getMemDC(), 420, 50, "영웅과 병력 강화로", 20, RGB(255, 255, 0));
	textOutFont(getMemDC(), 420, 50 + 24, "더욱 강력하게!", 20, RGB(255, 255, 0));

	textOutFont(getMemDC(), 18, 342, "위급할땐 마법 구매로", 20, RGB(255, 255, 0));
	textOutFont(getMemDC(), 18, 342 + 24, "대규모 전장 마법을!", 20, RGB(255, 255, 0));

	textOutFont(getMemDC(), 524, 343, "나만의 동료들과", 20, RGB(255, 255, 0));
	textOutFont(getMemDC(), 524, 343 + 24, "적의 성을 함락하자!", 20, RGB(255, 255, 0));

	//textOutMouse(getMemDC());


	

	//파일 이름 표시
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
			//로딩
			textOutFont(getMemDC(), _ptMouse.x + 10, _ptMouse.y, "Click to", 40, RGB(250, 200, 0));
			textOutFont(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 42, "Continue", 40, RGB(250, 200, 0));
			//SOUNDMANAGER->play("다이_아군");
			//"다이_적",
				//"다이_아군"
		}
		//_loading->getCurrentGauge()
		//_currentGauge, _vLoadItem.size()
			//_loadingBar->setGauge(_currentGauge, _vLoadItem.size());
	}



}

/* < 여기에 각 씬에 출력할 이미지 미리 로드 해두는 곳입니다. >*/
void loadingScene::loadingImage()
{







	_loading->loadImage("빈페이지", "빈페이지.bmp", 3, 3);

//================================================================================================================

	//스테이지 이미지
	_loading->loadImage("배경1", "배경1.800.600.bmp", 800, 595);
	_loading->loadImage("배경1_2", "배경1_2.1003.369.bmp", 1003, 369);
	_loading->loadImage("배경2", "배경2.800.600.bmp", 812, 417);
	_loading->loadImage("배경3", "배경3.800.600.bmp", 800, 600);
	_loading->loadImage("배경5", "배경5.800.600.bmp", 800, 420);
	_loading->loadImage("배경6", "배경6.800.600.bmp", 1100, 310);
	_loading->loadImage("라인", "배경라인.1415.600.bmp", 1415, 600);
	
	//_loading->loadImage("배경5.미니맵", "배경5.800.600.bmp", 800, 500);

	_loading->loadImage("인게임UI", "인게임UI.800.600.bmp", 800, 600);



	_loading->loadImage("히어로", "hero.256.311.bmp", 256 / 2, 311 / 2);
	_loading->loadImage("히어로_적", "hero_enemy.238.270.bmp", 238 / 2, 270 / 2);
	_loading->loadImage("워리어", "worrior.285.314.bmp", 285 / 4, 314 / 4);
	_loading->loadImage("워리어_적", "worrior_enemy.286.269.bmp", 286 / 4, 269 / 4);
	_loading->loadImage("아처", "archer.251.258.bmp", 251 / 3.6, 258 / 3.6);
	_loading->loadImage("아처_적", "archer_enemy.248.247.bmp", 248 / 3.6, 247 / 3.6);
	_loading->loadImage("메지션", "magician.256.259.bmp", 256 / 3.6, 259 / 3.6);
	_loading->loadImage("메지션_적", "magician_enemy.243.273.bmp", 243 / 3.6, 273 / 3.6);
	_loading->loadImage("케슬", "castle.397.484.bmp", 397 / 1.4, 484 / 1.4);
	_loading->loadImage("케슬_적", "castle_enemy.423.445.bmp", 423 / 1.3, 445 / 1.3);
	_loading->loadImage("타워", "tower.163.244.bmp", 163 / 1.6, 244 / 1.6);
	_loading->loadImage("타워_적", "tower_enemy.160.220.bmp", 160 / 1.6, 220 / 1.6);

	_loading->loadImage("히어로_피격", "hero_beHit.256.311.bmp", 256 / 2, 311 / 2);
	_loading->loadImage("히어로_적_피격", "hero_enemy_beHit.238.270.bmp", 238 / 2, 270 / 2);
	_loading->loadImage("워리어_피격", "worrior_beHit.285.314.bmp", 285 / 4, 314 / 4);
	_loading->loadImage("워리어_적_피격", "worrior_enemy_beHit.286.269.bmp", 286 / 4, 269 / 4);
	_loading->loadImage("아처_피격", "archer_beHit.251.258.bmp", 251 / 3.6, 258 / 3.6);
	_loading->loadImage("아처_적_피격", "archer_enemy_beHit.248.247.bmp", 248 / 3.6, 247 / 3.6);
	_loading->loadImage("메지션_피격", "magician_beHit.256.259.bmp", 256 / 3.6, 259 / 3.6);
	_loading->loadImage("메지션_적_피격", "magician_enemy_beHit.243.273.bmp", 243 / 3.6, 273 / 3.6);
	_loading->loadImage("케슬_피격", "castle_beHit.397.484.bmp", 397 / 1.4, 484 / 1.4);
	_loading->loadImage("케슬_적_피격", "castle_enemy_beHit.423.445.bmp", 423 / 1.3, 445 / 1.3);
	_loading->loadImage("타워_피격", "tower_beHit.163.244.bmp", 163 / 1.6, 244 / 1.6);
	_loading->loadImage("타워_적_피격", "tower_enemy_beHit.160.220.bmp", 160 / 1.6, 220 / 1.6);



	_loading->loadFrameImage("숫자이미지1", "numSprite.bmp", 360, 42, 10, 1);

	//===========미니멈======================



	//=======================================



	//체력바
	_loading->loadImage("체력바", "PlayerprogressBarFront.bmp", 50, 6);
	_loading->loadImage("체력바_적", "progressBarFront.bmp", 50, 6);
	_loading->loadImage("체력바_배경", "progressBarBack.bmp", 50, 6);
	
	//화살
	_loading->loadImage("화살", "Arrow.142.40.bmp", 52, 16);
	_loading->loadImage("화살_적", "Arrow_enemy.76.34.bmp", 52, 16);
	_loading->loadImage("볼트", "bolt.124.62.bmp", 62, 20);
	_loading->loadImage("볼트_적", "bolt_enemy.139.71.bmp", 62, 20);
	_loading->loadImage("슬레쉬", "SlashingEffect.156.158.bmp", 78, 79);
	_loading->loadImage("슬레쉬_적", "SlashingEffect_enemy.156.158.bmp", 78, 79);

	//무기
	_loading->loadImage("보스칼", "Weapon_boss.1200.169.bmp", 300, 42);
	_loading->loadImage("보스칼_적", "boss_weapon.1300.500.bmp", 325, 125);
	_loading->loadImage("칼", "Weapon #3426.bmp", 140, 16);
	_loading->loadImage("칼_적", "Sword_enemy.900.102.bmp", 140, 16);
	_loading->loadImage("활", "Bow.80.128.bmp", 20, 36);
	_loading->loadImage("활_적", "bow_enemy.300.58.bmp", 75, 15);
	_loading->loadImage("지팡이", "지팡이.300.52.bmp", 80, 13);
	_loading->loadImage("지팡이_적", "지팡이_enemy.200.52.bmp", 50, 13);

	//다이
	_loading->loadImage("히어로_다이", "hero_die.256.311.bmp", 311 / 2, 256 / 2);
	_loading->loadImage("워리어_다이", "worrior_die.314.285.bmp", 314 / 4, 285 / 4);
	_loading->loadImage("아처_다이", "archer_die.251.258.bmp", 258 / 3.6, 251 / 3.6);
	_loading->loadImage("메지션_다이", "magician_die.256.259.bmp", 259 / 3.6, 256 / 3.6);
	_loading->loadImage("히어로_적_다이", "hero_enemy_die.238.270.bmp", 270 / 2, 238 / 2);
	_loading->loadImage("워리어_적_다이", "worrior_enemy_die.286.269.bmp", 269 / 4, 286 / 4);
	_loading->loadImage("아처_적_다이", "archer_enemy_die.248.247.bmp", 247 / 3.6, 248 / 3.6);
	_loading->loadImage("메지션_적_다이", "magician_enemy_die.243.273.bmp", 273 / 3.6, 243 / 3.6);

	//_loading->loadImage("케슬", "castle.397.484.bmp", 397 / 1.4, 484 / 1.4);
	//_loading->loadImage("케슬_적", "castle_enemy.423.445.bmp", 423 / 1.3, 445 / 1.3);
	//_loading->loadImage("타워", "tower.163.244.bmp", 163 / 1.6, 244 / 1.6);
	//_loading->loadImage("타워_적", "tower_enemy.160.220.bmp", 160 / 1.6, 220 / 1.6);

//================================================================================================================



	_loading->loadFrameImage("숫자2", "숫자2.bmp", 360, 42, 10, 1, true, RGB(255, 0, 255));


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

	//로딩 떼껄룩


	//================================================================================================================

	_loading->loadImage("Micon_Cassle", "Shop/Shop_Micon_Cassle.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_Tower", "Shop/Shop_Micon_Tower.bmp", 40, 40, true, RGB(255, 0, 255));

	//로비 이미지
	_loading->loadImage("bg", "lobby_bg.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("popup", "popup.bmp", 180, 100, true, RGB(255, 0, 255));
	_loading->loadFrameImage("hero_lobby", "hero_lobby.bmp", 6270 / 1.24, 630 / 1.24, 11, 1);
	_loading->loadImage("setting", "설정.bmp", 36, 36, true, RGB(255, 0, 255));
	_loading->loadImage("exit", "종료.bmp", 36, 36, true, RGB(255, 0, 255));
	_loading->loadImage("goldbar", "금바.bmp", 170, 36, true, RGB(255, 0, 255));
	_loading->loadImage("window", "윈도우.bmp", 370, 290, true, RGB(255, 0, 255));
	_loading->loadImage("sound", "음악.bmp", 72, 72, true, RGB(255, 0, 255));
	_loading->loadImage("ex", "엑스.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadFrameImage("onoff", "onoff.bmp", 176, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("shop", "shop.bmp", 160, 80, true, RGB(255, 0, 255));
	_loading->loadImage("upgrade", "upgrade.bmp", 160, 80, true, RGB(255, 0, 255));
	_loading->loadImage("box", "box.bmp", WINSIZEX, 50);
	_loading->loadImage("줄", "줄.bmp", 33, 200, true, RGB(255, 0, 255));
	_loading->loadImage("st", "stage.bmp", 160, 80, true, RGB(255, 0, 255));

	//세팅창 이미지
	_loading->loadImage("button", "버튼.bmp", 100, 80, true, RGB(255, 0, 255));
	_loading->loadFrameImage("speed", "speed.bmp", 140, 56, 3, true, RGB(255, 0, 255));
	_loading->loadImage("coin", "코인.bmp", 150, 150, true, RGB(255, 0, 255));
	_loading->loadImage("end", "end.bmp", 370, 290, true, RGB(255, 0, 255));



	//유저스킬 이미지
	_loading->loadFrameImage("진", "진2.bmp", 2496, 108, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("별", "별.bmp", 640, 176, 4, 1, true, RGB(255, 0, 255));

	//stageMap 이미지
	_loading->loadImage("table", "table.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("stage_bg", "stage_bg.bmp", ((WINSIZEX - 135)) * 7, (WINSIZEY - 180), 7, 1, true, RGB(255, 0, 255));
	_loading->loadImage("alpha", "alpha.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadImage("stage1", "알파지역.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadImage("stage2", "알파지역2.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadImage("stage3", "알파지역3.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadImage("stage4", "알파지역4.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadImage("stage5", "알파지역5.bmp", WINSIZEX - 135, WINSIZEY - 180, true, RGB(255, 0, 255));
	_loading->loadFrameImage("stage_num", "stage_num.bmp", 235, 48, 5, 1, true, RGB(255, 0, 255));
	_loading->loadImage("back", "back.bmp", 36, 36, true, RGB(255, 0, 255));
	_loading->loadImage("lock", "lock.bmp", 47, 48, true, RGB(255, 0, 255));

	//타이틀 씬 이미지
	_loading->loadImage("title_bg", "title_bg.bmp", WINSIZEX, WINSIZEY);
	//_loading->loadImage("monster", "monster.bmp", WINSIZEX + 500, -40, WINSIZEX*0.83, WINSIZEY*1.1, true, RGB(255, 0, 255));
	_loading->loadImage("monster", "monster.bmp", WINSIZEX + 500, 000, 954 / 1.09, 653 / 1.09, true, RGB(255, 0, 255));
	//_loading->loadImage("hero", "hero.bmp", -WINSIZEX, 50, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("hero", "hero.bmp", -WINSIZEX, 100, 908 / 1.2, 639 / 1.2, true, RGB(255, 0, 255));
	_loading->loadImage("start", "start.bmp", WINSIZEX, WINSIZEY, 204 / 1.2, 138 / 1.2, true, RGB(255, 0, 255));
	_loading->loadImage("title", "title.bmp", 243 * 1.4, 109 * 1.4, true, RGB(255, 0, 255));

	//================================================================================================================


	_loading->loadImage("상점 스크롤", "Shop/Shop_ShopScroll.bmp", 2000, 200);							//스크롤 백그라운드 이미지
	_loading->loadImage("테스트", "Shop/Shop_ShopScroll.bmp", 800, 50);
	_loading->loadImage("화살표", "Shop/Shop_StatUp.bmp", 25, 21, true, RGB(255, 0, 255));				//스텟업 강조하는 화살표 이미지
	_loading->loadImage("Yes", "Shop/Shop_Yes.bmp", 80, 40, true, RGB(255, 0, 255));					//업그레이드or구매 Yes
	_loading->loadImage("No", "Shop/Shop_no.bmp", 80, 40, true, RGB(255, 0, 255));						//업그레이드or구매 No
	_loading->loadImage("Pop_Up", "Shop/Shop_PopUp.bmp", 300, 200, true, RGB(255, 0, 255));				//팝업창
	_loading->loadImage("Discription", "Shop/Shop_Discription.bmp", 800, 400, true, RGB(255, 0, 255));	//디스크립션 
	_loading->loadImage("Sign", "Shop/Shop_Buy.bmp", 222 / 2, 222 / 2, true, RGB(255, 0, 255));			//구매or업그레이드 픽 이미지
	_loading->loadImage("Gold", "Shop/Shop_Gold_Icon.bmp", 238 / 12, 269 / 12, true, RGB(255, 0, 255)); //골드 아이콘
	_loading->loadImage("Price", "Shop/Shop_Price.bmp", 163 * 7 / 8, 33 * 7 / 8);						//골드하고 가격 창 강조해주는 이미지
	_loading->loadImage("Back", "Shop/Icon_Scene_Back.bmp", 36, 36);
	_loading->loadImage("Player_Gold", "Shop/Shop_Show_Player_Gold.bmp", 170, 36, true, RGB(255, 0, 255));


	_loading->loadImage("Unit_Info", "Shop/Shop_Unit_Info.bmp", 119, 48, true, RGB(255, 0, 255));		//유닛 업그레이드창으로 전환 
	_loading->loadImage("Object_Info", "Shop/Shop_Object_Info.bmp", 119, 48, true, RGB(255, 0, 255));	//오브젝트 업그레이드창으로 전환


	_loading->loadImage("Upgrade_BG", "Shop/Shop_ShopBG.bmp", 820, 450);								//업그레이드 배경 이미지
	_loading->loadImage("Shop_BG", "Shop/Shop_Shop_Bg.bmp", 820, 450);									//상점 배경 이미지


	_loading->loadImage("Upgrade_Load", "Shop/Shop_Go_Upgrade.bmp", 146, 80, true, RGB(255, 0, 255));	//상점->업그레이드 
	_loading->loadImage("Shop_Load", "Shop/Shop_Go_Shop.bmp", 146, 80, true, RGB(255, 0, 255));			//업그레이드->상점 

	//캐릭터 이미지
	_loading->loadImage("Icon_Warrior", "Shop/Shop_Icon_Warrior.bmp", 200, 200);						//워리어 아이콘 이미지	
	_loading->loadImage("Icon_Archor", "Shop/Shop_Icon_Archor.bmp", 200, 200);							//아쳐 아이콘 이미지
	_loading->loadImage("Icon_Mage", "Shop/Shop_Icon_Mage.bmp", 200, 200);								//마법사 아이콘 이미지
	_loading->loadImage("Icon_Hero", "Shop//Shop_Icon_Hero.bmp", 200, 200);								//영웅 아이콘 이미지

	_loading->loadImage("Micon_Warrior", "Shop/Shop_MIcon_Worrior.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_Archor", "Shop/Shop_MIcon_Archor.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_Mage", "Shop/Shop_MIcon_Mage.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_Hero", "Shop/Shop_MIcon_Hero.bmp", 40, 40, true, RGB(255, 0, 255));

	//오브젝트 이미지
	_loading->loadImage("Icon_Tower", "Shop/Shop_Icon_Tower.bmp", 200, 200);							//타워 아이콘 이미지
	_loading->loadImage("Icon_Cassle", "Shop/Shop_Icon_Cassle.bmp", 200, 200);							//성 아이콘 이미지 



	//

	_loading->loadImage("Micon_Meteor2", "Shop/Shop_Icon_Meteor_Mini.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_BlackHole2", "Shop/Shop_Icon_BlackHole_Mini.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->loadImage("Micon_Heal2", "Shop/Shop_Icon_Heal_Mini.bmp", 60, 60, true, RGB(255, 0, 255));


	//================================================================================================================



	_loading->loadFrameImage("BlackHole2", "Skill_BlackHole.bmp", 1360, 130, 15, 1);

	_loading->loadFrameImage("BlackHole", "Skill_BlackHole2.bmp", 1360, 130, 15, 1);


//================================================================================================================








}

/* < 여기에 각 씬에 출력할 사운드 미리 로드 해두는 곳입니다. >*/
void loadingScene::loadingSound()
{
	

	//지도 펴는소리
	SOUNDMANAGER->addSound("p1", "test.wav");
	SOUNDMANAGER->addSound("지도", "unequip.mp3", false, false);
	SOUNDMANAGER->addSound("떼껄룩", "떼껄룩2.mp3", false, false);
	SOUNDMANAGER->addSound("Buy_Skill", "Shop_Sound_Buy_Skill.mp3");
	SOUNDMANAGER->addSound("Buy_Upgrade", "Shop_Sound_Buy_Upgrade.mp3");
	SOUNDMANAGER->addSound("종이", "종이.mp3", false, false);
	SOUNDMANAGER->addSound("버튼", "버튼.mp3", false, false);
	
	SOUNDMANAGER->addSound("공격사운드_영웅", "Hero_Attack.mp3", false, false);
	//SOUNDMANAGER->addSound("공격사운드_메이지", "Mage_Attack.mp3", false, false);
	SOUNDMANAGER->addSound("공격_메이지", "메이지.wav", false, false);
	SOUNDMANAGER->addSound("공격사운드_워리어", "Worrior_Attack.mp3", false, false);
	SOUNDMANAGER->addSound("공격사운드_아쳐", "Archor_Attack.mp3", false, false);
	SOUNDMANAGER->addSound("사운드_메테오", "Meteor.mp3", false, false);
	SOUNDMANAGER->addSound("힐_사운드", "heal.mp3", false, false);
	SOUNDMANAGER->addSound("블랙홀_사운드", "포탈2.wav", false, false);
	SOUNDMANAGER->addSound("블랙홀_바람", "포탈_바람.wav", false, false);

	//스테이지
	SOUNDMANAGER->addSound("다이_적", "348270__metekavruk__oops2.ogg", false, false); //적 다이
	SOUNDMANAGER->addSound("다이_아군", "76958__michel88__deathd.wav", false, false); //아군 다이
	SOUNDMANAGER->addSound("피격", "beHit.wav", false, false); //피격
	
	//결과 창
	SOUNDMANAGER->addSound("브금_승리", "victory.mp3", true, true); //승리 브금
	SOUNDMANAGER->addSound("브금_승리2", "victory2.wav", true, true); //승리 브금

	//브금
	SOUNDMANAGER->addSound("브금_타이틀", "bgm_title.mp3", true, true); //아군 다이
	SOUNDMANAGER->addSound("브금_로비", "bgm_lobby.mp3", true, true); //아군 다이
	SOUNDMANAGER->addSound("브금_스테이지", "bgm_stage.wma", true, true); //아군 다이

	
	
}
