#pragma once

template <class T>
class singletonBase
{
protected:
	//�̱��� ��ü ����
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}
public:
	//�̱��� ��ü ��������
	static T* getSingleton();
	//�̱��� ��ü �����ϱ�
	void releaseSingleton();
};

//�̱��� �ʱ�ȭ
template<class T>
T* singletonBase<T>::singleton = 0;

//�̱��� ��ü ��������
template<class T>
inline T * singletonBase<T>::getSingleton()
{
	//�̱����� ������ ���� ����
	if (!singleton) singleton = new T;
	return singleton;
}

//�̱��� ��ü �����ϱ�
template<class T>
inline void singletonBase<T>::releaseSingleton()
{
	//�̱����� �ִٸ� �޸𸮿��� ����
	if (singleton)
	{
		delete singleton;
		singleton = NULL;
	}
}
