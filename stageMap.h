#pragma once
#include "gameNode.h"
#include "stage.h"

class stageMap : public gameNode
{
public:// < ���� ���� �� > =============================================================
	image* _map;
	image* _table;

	stage* _stage;

	RECT _rc[5];

	RECT stage_rc[5];

	RECT back_rc;

	int state;
	char buf[256];
	int lv_stage;
	int _alpha;
	bool _a;
	int a;
	int count;
public:// < �Լ� ���� �� > =============================================================


	HRESULT init();
	void release();
	void update();
	void render();
	void stagenum(int state, int num);
	void stagesel(int state, int num);

	stageMap() {}
	~stageMap() {}
};

