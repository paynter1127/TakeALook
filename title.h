#pragma once
#include "gameNode.h"
class title : public gameNode
{
public:// < ���� ���� �� > =============================================================


	RECT rc;

	bool check;
	int count;



	int a;


public:// < �Լ� ���� �� > =============================================================


	HRESULT init();
	void release();
	void update();
	void render();

	title() {}
	~title() {}
};

