#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//이곳에서 초기화를 한다

	//씬 추가
	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("lobby", new lobby);

	SCENEMANAGER->addScene("upgrade", new upgrade);
	SCENEMANAGER->addScene("Shop", new shop);
	SCENEMANAGER->addScene("logo", new logo);

	SCENEMANAGER->addScene("stageMap", new stageMap);
	SCENEMANAGER->addScene("stage", new stage);
	SCENEMANAGER->addScene("로딩화면", new loadingScene);



	//현재 씬 설정
	SCENEMANAGER->loadScene("로딩화면");
	//SCENEMANAGER->loadScene("stage");
	//브금

	//폰트 추가
	AddFontResource("Maplestory Bold.ttf");



	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//이미지 클래스를 나갈때까진 사용할 일 없다
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE() 사용한다
	RemoveFontResource("Maplestory Bold.ttf");
}


//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다
	SCENEMANAGER->update();
	SOUNDMANAGER->update();

	//강현 씬 이동
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->loadScene("stage");
	}
	//재혁 씬 이동
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->loadScene("lobby");
	}
	//형준 씬 이동
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->loadScene("upgrade");
	}

	//세이브
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		savePlayer();
	}
	//로드
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		loadPlayer();
	}

}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void mainGame::render()
{
	//흰색 빈 비트맵 (이것도 렌더에 그냥 두기)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	SCENEMANAGER->render();
	//textOutMouse(getMemDC()); //완료
	//textOutDbug(getMemDC(), playerInfo::getSingleton()->gold);


	//textOutFont(getMemDC(), 20, 20, "글꼴테스트", 40, RGB(255, 255, 255) );
	//TextOut(getMemDC(), 20, 0, "복귀 테스트", strlen("복귀 테스트"));


	//TextOut(getMemDC(), 20, 20, "로비", strlen("로비"));
//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC());
}
