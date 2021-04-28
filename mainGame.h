#pragma once
#include "gameNode.h"
//메인게임에 각 씬들의 헤더파일을 인클루드 해주십셔
//헤더 인클루드 했으면 메인게임.cpp 의 init 에 씬 메니저로 씬 추가 해주십셔
#include "loadingScene.h"
#include "title.h"
#include "lobby.h"
#include "upgrade.h"
#include "shop.h"
#include "logo.h"
#include "stageMap.h"
#include "stage.h"

class mainGame : public gameNode
{
public:


	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

