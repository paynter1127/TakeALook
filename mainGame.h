#pragma once
#include "gameNode.h"
//���ΰ��ӿ� �� ������ ��������� ��Ŭ��� ���ֽʼ�
//��� ��Ŭ��� ������ ���ΰ���.cpp �� init �� �� �޴����� �� �߰� ���ֽʼ�
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

