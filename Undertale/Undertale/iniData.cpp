#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init()
{
	return S_OK;
}

void iniData::release()
{
}
//������ �߰��ϱ�
void iniData::addData(const char * section, const char * key, const char * value)
{
	//ini������ ����ü �ʱ�ȭ
	tagIniData data;
	data.section = (char*)section;
	data.key = (char*)key;
	data.value = (char*)value;

	//���� INI�����Ϳ� ���
	_vIniData.push_back(data);
}

//���̺�
void iniData::saveINI(const char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	//c:/�����/�ڼ���/~ 
	strcat_s(dir, str); //���ڿ� ����
	//dir = "abc", str = "def"
	//strcat(dir, str) => dir => "abcdef"

	for (int i = 0; i < _vIniData.size(); i++)
	{
		WritePrivateProfileString(_vIniData[i].section, _vIniData[i].key, _vIniData[i].value, dir);
	}
	this->clearIniData();
}

//���ڷ� ���� �ε��ϱ�(�����̸�, ����, Ű)
char * iniData::loadDataString(const char * fileName, const char * section, const char * key)
{
	char data[64] = { 0 };
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat_s(dir, str);

	GetPrivateProfileString(section, key, "", data, sizeof(data), dir);

	return data;
}

//������ ���� �ε��ϱ�(�����̸�, ����, Ű)
int iniData::loadDataInteger(const char * fileName, const char * section, const char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat_s(dir, str);

	return GetPrivateProfileInt(section, key, 0, dir);;
}

//�Ǽ��� ���� �ε��ϱ�(�����̸�, ����, Ű) => ���� �����
float iniData::loadDataFloat(const char * fileName, const char * section, const char * key)
{
	return (atof)(loadDataString(fileName, section, key));
}