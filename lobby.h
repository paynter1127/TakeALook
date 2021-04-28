#pragma once
#include "gameNode.h"

class lobby : public gameNode
{
public:// < 변수 선언 부 > =============================================================

	int state;
	int a;
	int count;
	int _speed;
	RECT _rc[4];
	RECT window;
	RECT ex;
	RECT save;
	RECT speed;


	RECT sound;
	RECT set_rc;
	RECT gold_rc;
	RECT exit_rc;
	char str[10];
	bool onoff;
	bool win;
public:// < 함수 선언 부 > =============================================================





	HRESULT init();
	void release();
	void update();
	void render();


	void popup();

	lobby() {}
	~lobby() {}
};

