#pragma once
//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

#define PI 3.141592f
#define PI2 (PI * 2)

//���߿� �̹��� ȸ���� ����� ��
#define PI_2 (PI / 2) //90��
#define PI_4 (PI / 4) //45��
#define PI_8 (PI / 8) //22.5��

namespace MY_UTIL //�̸��� ��������� �����ص� �ȴ�
{
	//���� ������ �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);

	//���� ������ ����
	float getAngle(float startX, float startY, float endX, float endY);

	// < �̹����ѹ� > (string �̹���Ű, HDC hdc, int ���x��ǥ, int ���y��ǥ, int ��¼���, int ���ڰ���)
	void imageNum(string keyName, HDC hdc, int x, int y, int num, int gapNum);

	// < ���콺 ��ǥ ��� >
	void textOutMouse(HDC hdc);

	// < ������ �ؽ�Ʈ ��� > (HDC hdc, ��� ����(�Ҽ�2° �ڸ� ����), int ���x��ǥ, int ���y��ǥ)
	void textOutDbug(HDC hdc, int x = 700, int y = 40, float num = 999);

	// < ��Ʈ > (���� ��� ����? �⺻ �����)
	void textOutFont(HDC hdc, int x, int y, const char* str, int size = 50, COLORREF color = RGB(0, 0, 0));

	// < ���� ������ ���̺� >
	void savePlayer();
	// < ���� ������ �ε� >
	void loadPlayer();
	
	


	void textOutFontNum(HDC hdc, int x, int y, int Stat, int size = 50, COLORREF color = RGB(0, 0, 0));

	void textOutFont(HDC hdc, int x, int y, const char* str, const char* setting, int size = 50, COLORREF color = RGB(0, 0, 0));


	void imagescaleNum(string keyName, HDC hdc, int x, int y, int num, int gapNum, float sclae);


	int getPosition(int map, int position, int minimap);


};