#pragma once
#include "gameNode.h"
#include "bullet.h"


//�� �Ŵ��� ��ȣ������ ���� Ŭ���� ���� ����
class enemyManager;

class player : public gameNode
{
private:
	image* _rocket;		//����(�÷��̾�) �̹���
	//RECT _rcPlayer;
	missile* _missile;	//�̻��� Ŭ����
	bomb* _bomb;		//��ź Ŭ����

	enemyManager* eeenemyManager; //�����Ҵ��ϸ� �ȵȴ�

public:
	HRESULT init();
	void release();
	void update();
	void render();

	vector<tagBullet> _getMissile() { return _missile->getMissile(); }
	//missile* _getMissile() { return _missile; }
	void getRemoveMissile(int index) { return _missile->removeMissile(index); }
	RECT getRc() { return _rocket->boudingBox(); };

	player() {}
	~player() {}


	void setEm(enemyManager *em) { eeenemyManager = em; }
};

