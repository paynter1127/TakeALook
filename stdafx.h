/* < 참고 > 
	쌤이 쓰셨던 버그 수정 적용 버전
	- fmod 사운드 매니저 내 pause 기능쪽 함수 틀린 것 수정
	- 이미지 메니저 폴더 image 로 변경
	- 사운드 매니저 폴더 SOUND 로 변경
	- 이미지 숫자 함수 제작
	- 디버그용 함수 제작(마우스, 숫자)
	- 이미지 클래스 마젠타 디폴트 매개변수로 변경
	- 이미지 클래스 루프 알파 렌더 쌤 오류난 것 수정 버전
	- 통합한 코드 안정성 검사
*/

// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include <SDKDDKVer.h>

//디버깅용 (주석치면 콘솔창이 사라진다)
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
using namespace std;
// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>

//=============================================================
//	## 내가 만든 헤더파일을 이곳에 추가한다 ##
//=============================================================
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "util.h"
using namespace MY_UTIL;
#include "playerInfo.h"
#include "iniData.h"


//=============================================================
//	## 싱글톤을 추가한다 ##
//=============================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define INIDATA iniData::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()


//=============================================================
//	## 디파인문 ## (윈도우창 초기화)
//=============================================================
#define WINNAME (LPTSTR)(TEXT(" programing by Team Take a look "))
#define WINSTARTX	32
#define WINSTARTY	0
#define WINSIZEX		800
#define WINSIZEY		600
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=============================================================
//	## 매크로함수 ## (클래스에서 동적할당된 부분 해제)
//=============================================================
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//=============================================================
//	## 전역변수 ##
//=============================================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;