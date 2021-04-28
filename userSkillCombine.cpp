#include "stdafx.h"
#include "userSKillCombine.h"



HRESULT userSKillCombine::init()
{
	_Meteor = new userSkill;
	_Meteor->init();

	_Heal = new userSkill3;
	_Heal->init();

	_BlackHole = new userSkill2;
	_BlackHole->init();
	return S_OK;
}

void userSKillCombine::release()
{
	SAFE_DELETE(_Meteor);
	SAFE_DELETE(_Heal);
	SAFE_DELETE(_BlackHole);
}

void userSKillCombine::update()
{
	_Meteor->update();
	_Heal->update();
	_BlackHole->update();
}

void userSKillCombine::render()
{
	_Meteor->render();
	_Heal->render();
	_BlackHole->render();
}

