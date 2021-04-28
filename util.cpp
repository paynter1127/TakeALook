#include "stdafx.h"
#include "util.h"

float MY_UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

float MY_UTIL::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;
	float distance = sqrtf(x * x + y * y);
	float angle = acosf(x / distance);
	if (endY > startY)
	{
		angle = PI2 - angle;
	}
	return angle;
}


// < �̹����ѹ� > (string �̹���Ű, HDC hdc, int ���x��ǥ, int ���y��ǥ, int ��¼���, int ���ڰ���)
void MY_UTIL::imageNum(string keyName, HDC hdc, int x, int y, int num, int gapNum)
{
	if (num < 10)
	{
		IMAGEMANAGER->findImage(keyName)->setFrameX(num % 10);
		return IMAGEMANAGER->frameRender(keyName, hdc, x, y);
	}
	IMAGEMANAGER->findImage(keyName)->setFrameX(num % 10);
	IMAGEMANAGER->frameRender(keyName, hdc, x, y);
	return imageNum(keyName, hdc, x - gapNum, y, num / 10, gapNum);
}

void MY_UTIL::imagescaleNum(string keyName, HDC hdc, int x, int y, int num, int gapNum, float scale)
{
	if (num < 10)
	{
		IMAGEMANAGER->findImage(keyName)->setFrameX(num % 10);
		return IMAGEMANAGER->scaleFrameRender(keyName, hdc, x, y, IMAGEMANAGER->findImage("����2")->getFrameX(), IMAGEMANAGER->findImage("����2")->getFrameY(), scale);
	}
	IMAGEMANAGER->findImage(keyName)->setFrameX(num % 10);
	IMAGEMANAGER->scaleFrameRender(keyName, hdc, x, y, IMAGEMANAGER->findImage("����2")->getFrameX(), IMAGEMANAGER->findImage("����2")->getFrameY(), scale);
	return imagescaleNum(keyName, hdc, x - gapNum, y, num / 10, gapNum, scale);
}


void MY_UTIL::textOutMouse(HDC hdc)
{
	char strMouse[128];
	sprintf(strMouse, "x: %d, y: %d", _ptMouse.x, _ptMouse.y);
	TextOut(hdc, WINSIZEX - 100, 20, strMouse, strlen(strMouse));
}

void MY_UTIL::textOutDbug(HDC hdc, int x, int y, float num)
{
	char strDbug[128];
	sprintf(strDbug, "%.2f", num);
	TextOut(hdc, x, y, strDbug, strlen(strDbug));
}


void MY_UTIL::textOutFont(HDC hdc, int x, int y, const char* str, int size, COLORREF color)
{
	SetBkMode(hdc, 1);
	SetTextColor(hdc, color);

	HFONT hFont, oldFont;
	//(����, ��, ����, �ѱ��ڿ���(�ȵ�), �β�(�ȵ�), ?, ?, ?, ���ڼ�, �����Ȯ��, Ŭ������Ȯ��, ?, ��Ʈ��ġ�ͱ׷�, �۲��̸�)
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("�����ý��丮"));
	oldFont = (HFONT)SelectObject(hdc, hFont);
	TextOut(hdc, x, y, str, strlen(str));

	//����
	//SetBkMode(hdc, 2);
	//SetTextColor(hdc, RGB(0, 0, 0));
	//SelectObject(hdc, oldFont);
}


void MY_UTIL::savePlayer()
{
	//���̺� �׽�Ʈ
	char str[11][128];
	INIDATA->addData("��������", "���", itoa(playerInfo::getSingleton()->gold, str[0], 10));
	INIDATA->addData("��������", "��", itoa(playerInfo::getSingleton()->lv_castle, str[1], 10));
	INIDATA->addData("��������", "Ÿ��", itoa(playerInfo::getSingleton()->lv_tower, str[2], 10));
	INIDATA->addData("��������", "������", itoa(playerInfo::getSingleton()->lv_worrior, str[3], 10));
	INIDATA->addData("��������", "��ó", itoa(playerInfo::getSingleton()->lv_archer, str[4], 10));
	INIDATA->addData("��������", "������", itoa(playerInfo::getSingleton()->lv_megician, str[5], 10));
	INIDATA->addData("��������", "�����1", itoa(playerInfo::getSingleton()->lv_hero, str[6], 10));
	INIDATA->addData("��������", "��ų1", itoa(playerInfo::getSingleton()->num_skill1, str[7], 10));
	INIDATA->addData("��������", "��ų2", itoa(playerInfo::getSingleton()->num_skill2, str[8], 10));
	INIDATA->addData("��������", "��ų3", itoa(playerInfo::getSingleton()->num_skill3, str[9], 10));
	INIDATA->addData("��������", "������������", itoa(playerInfo::getSingleton()->lv_stage, str[10], 10));

	INIDATA->saveINI("playerInfo");
}

void MY_UTIL::loadPlayer()
{
	//�ε� �׽�Ʈ
	playerInfo::getSingleton()->gold = INIDATA->loadDataInteger("playerInfo", "��������", "���");
	playerInfo::getSingleton()->lv_castle = INIDATA->loadDataInteger("playerInfo", "��������", "��");
	playerInfo::getSingleton()->lv_tower = INIDATA->loadDataInteger("playerInfo", "��������", "Ÿ��");
	playerInfo::getSingleton()->lv_worrior = INIDATA->loadDataInteger("playerInfo", "��������", "������");
	playerInfo::getSingleton()->lv_archer = INIDATA->loadDataInteger("playerInfo", "��������", "��ó");
	playerInfo::getSingleton()->lv_megician = INIDATA->loadDataInteger("playerInfo", "��������", "������");
	playerInfo::getSingleton()->lv_hero = INIDATA->loadDataInteger("playerInfo", "��������", "�����1");
	playerInfo::getSingleton()->num_skill1 = INIDATA->loadDataInteger("playerInfo", "��������", "��ų1");
	playerInfo::getSingleton()->num_skill2 = INIDATA->loadDataInteger("playerInfo", "��������", "��ų2");
	playerInfo::getSingleton()->num_skill3 = INIDATA->loadDataInteger("playerInfo", "��������", "��ų3");
	playerInfo::getSingleton()->lv_stage = INIDATA->loadDataInteger("playerInfo", "��������", "������������");
}



void MY_UTIL::textOutFontNum(HDC hdc, int x, int y, int Stat, int size, COLORREF color)
{
	SetBkMode(hdc, 1);
	SetTextColor(hdc, color);

	char Num[128];
	sprintf(Num, "%d", Stat);

	HFONT hFont, oldFont;
	//(����, ��, ����, �ѱ��ڿ���(�ȵ�), �β�(�ȵ�), ?, ?, ?, ���ڼ�, �����Ȯ��, Ŭ������Ȯ��, ?, ��Ʈ��ġ�ͱ׷�, �۲��̸�)
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("�����ý��丮"));
	oldFont = (HFONT)SelectObject(hdc, hFont);

	TextOut(hdc, x, y, Num, strlen(Num));

	//����
	//SetBkMode(hdc, 2);
	//SetTextColor(hdc, RGB(0, 0, 0));
	//SelectObject(hdc, oldFont);
}
void MY_UTIL::textOutFont(HDC hdc, int x, int y, const char* str, const char* setting, int size, COLORREF color)
{
	SetBkMode(hdc, 1);
	SetTextColor(hdc, color);

	char Text[1024];

	sprintf(Text, setting, str);

	HFONT hFont, oldFont;
	//(����, ��, ����, �ѱ��ڿ���(�ȵ�), �β�(�ȵ�), ?, ?, ?, ���ڼ�, �����Ȯ��, Ŭ������Ȯ��, ?, ��Ʈ��ġ�ͱ׷�, �۲��̸�)
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("�����ý��丮"));
	oldFont = (HFONT)SelectObject(hdc, hFont);
	TextOut(hdc, x, y, Text, strlen(Text));

	//����
	//SetBkMode(hdc, 2);
	//SetTextColor(hdc, RGB(0, 0, 0));
	//SelectObject(hdc, oldFont);
}
int MY_UTIL::getPosition(int map, int position, int minimap)
{
	int a;

	a = (position*minimap) / map;


	return a;
}
