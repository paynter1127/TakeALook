#pragma once
#include "gameNode.h"
class logo : public gameNode
{
	char a[10];
	int num;
	int count;
	bool take;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	logo() {}
	~logo() {}
};

