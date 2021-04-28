#pragma once
#include "gameNode.h"
class title : public gameNode
{
public:// < 변수 선언 부 > =============================================================


	RECT rc;

	bool check;
	int count;



	int a;


public:// < 함수 선언 부 > =============================================================


	HRESULT init();
	void release();
	void update();
	void render();

	title() {}
	~title() {}
};

