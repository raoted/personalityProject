#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## loadItem ## (�ε������)
//=============================================================
HRESULT loadItem::init(string strKey, int width, int height)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForSound(string keyName, const char* fileName, bool bgm, bool loop)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_SOUND;
	//���� ����ü �ʱ�ȭ
	_soundResource.keyName = keyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}

//=============================================================
//	## loading ## (�ε�Ŭ����)
//=============================================================

HRESULT loading::init()
{
	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "Image/Picture/Logo.bmp", 640 * 2, 480 * 2);

	//�ε��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("loadingBarFront", "Image/UI/loadingBarFront.bmp", 600, 20);
	IMAGEMANAGER->addImage("loadingBarBack", "Image/UI/loadingBarBack.bmp", 600, 20);

	//�ε��� Ŭ���� �ʱ�ȭ
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront", "loadingBarBack");
	//_loadingBar->setGauge(0, 0);
	//�ε��� ��ġ
	_loadingBar->setPos(340, 500);

	//���� ������
	_currentGauge = 0;

	return S_OK;
}

void loading::release()
{
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
}

void loading::update()
{
	_loadingBar->update();
}

void loading::render()
{
	//��׶��� ����
	_background->render(getMemDC());
	//�ε��� ����
	_loadingBar->render();
	TextOut(getMemDC(), WINSIZEX / 2 - str.length() / 2, 500, str.c_str(), strlen(str.c_str()));
}

void loading::loadImage(string strKey, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(strKey, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadSound(string keyName, const char* fileName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, fileName, bgm, loop);
	_vLoadItem.push_back(item);
}

bool loading::loadingDone()
{
	//�ε��Ϸ��
	if (_currentGauge >= _vLoadItem.size())
	{
		return true;
	}

	loadItem* item = _vLoadItem[_currentGauge];
	str = _vLoadItem[_currentGauge]->getImageResource().fileName;
	switch (item->getLoadKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	}
	break;

	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.isTrans, img.transColor);
	}
	break;

	case LOAD_KIND_IMAGE_2:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.isTrans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
	}
	break;

	//�� ���� ���� ���� ���� �غ���!!
	case LOAD_KIND_SOUND:
	{
		tagSoundResource soundResource = item->getSoundResource();
		SOUNDMANAGER->addSound(soundResource.keyName, soundResource.fileName, soundResource.bgm, soundResource.loop);
	}
	break;
	}

	//���� ������ ����
	_currentGauge++;

	//�ε��� �̹��� ����
	_loadingBar->setGauge(_vLoadItem.size(), _currentGauge);


	return false;
}