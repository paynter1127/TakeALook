#pragma once
#include "singletonBase.h"

//싱글톤을 상속받은 아이들은 static 으로 만들어 지기때문에 일반 클래스인 게임노드를 사용하려고 하면 터진다.

//게임노드 클래스 전방선언(터지는거 막기 위해)
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	mSceneList _mSceneList;	//각각의 씬(화면)들을 담아둘 맵
	gameNode* _currentScene;//현재 씬


public:
	HRESULT init();
	void release();
	void update();
	void render();

	//씬 추가
	gameNode* addScene(string sceneName, gameNode* scene);
	//씬 변경(해당 씬 로드)
	HRESULT loadScene(string sceneName);

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

