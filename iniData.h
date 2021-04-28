#pragma once
#include "singletonBase.h"

/* <��� ���(�� ����� ����>

if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//����, Ű, ���
		//[�ù�15��]
		//����=50
		//����=100
		//...

		INIDATA->addData("�ù�15��", "����", "50.5");
		INIDATA->addData("�ù�15��", "����", "100");
		INIDATA->addData("�ù�15��", "����", "8");

		//���� �̸����� ���̺�
		INIDATA->saveINI("�ù��ù�");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		float num = INIDATA->loadDataFloat("�ù��ù�", "�ù�15��", "����");
	}
*/

//ini������ ����ü
struct tagIniData
{
	char* section; //[Player] => ����
	char* key;		//HP=100 => HP�� Ű��
	char* value;	//HP=100 => 100�� �ش� ��	
};

class iniData : public singletonBase <iniData>
{
private:
	vector<tagIniData> _vIniData;

public:
	HRESULT init();
	void release();

	//������ �߰��ϱ�
	void addData(const char* section, const char* key, const char* value);
	//���̺� �����̸�
	void saveINI(const char* fileName);

	//���ڷ� ���� �ε��ϱ�(�����̸�, ����, Ű)
	char* loadDataString(const char* fileName, const char* section, const char* key);
	//������ ���� �ε��ϱ�(�����̸�, ����, Ű)
	int loadDataInteger(const char* fileName, const char* section, const char* key);
	//�Ǽ��� ���� �ε��ϱ�(�����̸�, ����, Ű)
	float loadDataFloat(const char* fileName, const char* section, const char* key);


	iniData() {}
	~iniData() {}
};

