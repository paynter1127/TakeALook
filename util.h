#pragma once
//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

#define PI 3.141592f
#define PI2 (PI * 2)

//나중에 이미지 회전시 사용할 값
#define PI_2 (PI / 2) //90도
#define PI_4 (PI / 4) //45도
#define PI_8 (PI / 8) //22.5도

namespace MY_UTIL //이름은 너희마음대로 변경해도 된다
{
	//두점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);

	//두점 사이의 각도
	float getAngle(float startX, float startY, float endX, float endY);

	// < 이미지넘버 > (string 이미지키, HDC hdc, int 출력x좌표, int 출력y좌표, int 출력숫자, int 숫자간격)
	void imageNum(string keyName, HDC hdc, int x, int y, int num, int gapNum);

	// < 마우스 좌표 출력 >
	void textOutMouse(HDC hdc);

	// < 디버깅용 텍스트 출력 > (HDC hdc, 출력 숫자(소수2째 자리 까지), int 출력x좌표, int 출력y좌표)
	void textOutDbug(HDC hdc, int x = 700, int y = 40, float num = 999);

	// < 폰트 > (설명 없어도 알지? 기본 흰색임)
	void textOutFont(HDC hdc, int x, int y, const char* str, int size = 50, COLORREF color = RGB(0, 0, 0));

	// < 유저 데이터 세이브 >
	void savePlayer();
	// < 유저 데이터 로드 >
	void loadPlayer();
	
	


	void textOutFontNum(HDC hdc, int x, int y, int Stat, int size = 50, COLORREF color = RGB(0, 0, 0));

	void textOutFont(HDC hdc, int x, int y, const char* str, const char* setting, int size = 50, COLORREF color = RGB(0, 0, 0));


	void imagescaleNum(string keyName, HDC hdc, int x, int y, int num, int gapNum, float sclae);


	int getPosition(int map, int position, int minimap);


};