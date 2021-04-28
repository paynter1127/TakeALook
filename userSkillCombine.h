#pragma once
#include "gameNode.h"
#include "userSkill.h"
#include "userSkill2.h"
#include "userSkill3.h"


class userSKillCombine : public gameNode
{
public:

	userSkill* _Meteor;
	userSkill2* _BlackHole;
	userSkill3* _Heal;



public:


	HRESULT init();
	void release();
	void update();
	void render();



	userSKillCombine() {}
	~userSKillCombine() {}
};

