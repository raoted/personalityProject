#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�ε� �̹��� �� ���� �ʱ�ȭ
	this->loadingImage();
	//this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	
}

void loadingScene::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ�� ����
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("����ȭ��");
	}
}

void loadingScene::render()
{
	//�ε�Ŭ���� ����
	_loading->render();
}


//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	
	//��׶��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("��׶���", "Image/Picture", 640, 480);
	
	//======================================= �� �� �� ==============================================================
	//#=============================================================================================================
	//#									��� �̹��� �ҷ�����
	//#=============================================================================================================

	//#=============================================================================================================
	//#									���� �ҷ�����
	//#=============================================================================================================
	_loading->loadImage("Intro1", "Image/Picture/Intro1.bmp", 320, 240);
	_loading->loadImage("Intro2", "Image/Picture/Intro2.bmp", 320, 240);
	_loading->loadImage("Intro3", "Image/Picture/Intro3.bmp", 320, 240);
	_loading->loadImage("Intro4", "Image/Picture/Intro4.bmp", 320, 240);
	_loading->loadImage("Intro5", "Image/Picture/Intro5.bmp", 320, 240);
	_loading->loadImage("Intro6", "Image/Picture/Intro6.bmp", 320, 240);
	_loading->loadImage("Intro7", "Image/Picture/Intro7.bmp", 320, 240);
	_loading->loadImage("Intro8", "Image/Picture/Intro8.bmp", 320, 240);
	_loading->loadImage("Intro9", "Image/Picture/Intro9.bmp", 320, 350);
	_loading->loadImage("Logo", "Image/Picture/Logo.bmp", 640, 320);
	_loading->loadImage("GameOver", "Image/GameOver/GameOver.bmp", 422, 182);
	_loading->loadImage("Black", "Image/Picture/Black.bmp", 1280, 720);
	_loading->loadImage("White", "Image/Picture/White.bmp", 1280, 720);
	
	//#=============================================================================================================
	//#									UI �ҷ�����
	//#=============================================================================================================
	_loading->loadImage("tileMouse", "Image/UI/tileMouse.bmp", 40, 40);
	//#====================================== B a t t l e ==========================================================
	_loading->loadImage("AttackBar", "Image/UI/Battle/AttackBar.bmp", 720, 300);
	_loading->loadFrameImage("AttackStick", "Image/UI/Battle/AttackStick.bmp", 28, 150, 2, 1);

	_loading->loadImage("TextSide", "Image/UI/Battle/TextSide.bmp", 3, 3);
	_loading->loadImage("TextFloar", "Image/UI/Battle/TextFloar.bmp", 283, 3);
	_loading->loadImage("TextWall", "Image/UI/Battle/TextWall.bmp", 3, 283);
	//#====================================== B u t t o n ==========================================================
	_loading->loadFrameImage("Act", "Image/UI/Button/Act.bmp", 112, 88, 1, 2);
	_loading->loadFrameImage("Fight", "Image/UI/Button/Fight.bmp", 112, 88, 1, 2);
	_loading->loadFrameImage("Item", "Image/UI/Button/Item.bmp", 112, 88, 1, 2);
	_loading->loadFrameImage("Marcy", "Image/UI/Button/Marcy.bmp", 112, 88, 1, 2);
	_loading->loadFrameImage("Confirm", "Image/UI/Button/Confirm.bmp", 44, 68, 1, 2);
	_loading->loadFrameImage("Cancle", "Image/UI/Button/Cancle.bmp", 44, 68, 1, 2);
	_loading->loadFrameImage("Start", "Image/UI/Button/Start.bmp", 200, 300, 1, 3);
	_loading->loadImage("Menu", "Image/UI/Button/Menu.bmp", 250, 250);
	//#======================================== T o o l ============================================================
	_loading->loadImage("NewMap", "Image/UI/Tool/map.bmp", 32, 32);
	_loading->loadImage("SaveMap", "Image/UI/Tool/save.bmp", 32, 32);
	_loading->loadFrameImage("MapLayer", "Image/UI/Tool/layer.bmp", 96, 32, 3, 1);
	_loading->loadImage("Event", "Image/UI/Tool/event.bmp", 32, 32);
	_loading->loadImage("Eraser", "Image/UI/Tool/eraser.bmp", 32, 32);
	_loading->loadImage("Pencle", "Image/UI/Tool/pencle.bmp", 32, 32);
	_loading->loadImage("Rectangle", "Image/UI/Tool/rectangle.bmp", 32, 32);
	_loading->loadImage("Paint", "Image/UI/Tool/paint.bmp", 32, 32);
	_loading->loadImage("Setting", "Image/UI/Tool/setting.bmp", 32, 32);
	_loading->loadImage("Home", "Image/UI/Tool/home.bmp", 32, 32);
	//#============================== S p e e c h B u b b l e ======================================================
	_loading->loadImage("Bubble1", "Image/UI/Battle/TalkBubble/1.bmp", 99, 66);
	//#======================================== F o n t ============================================================
	_loading->loadFrameImage("Number", "Image/UI/Font/Number.bmp", 280, 28, 10, 1);
	//#======================================== G a g e ============================================================
	_loading->loadImage("maxHP", "Image/UI/Gage/maxHP.bmp", 1, 30);
	_loading->loadImage("curHP", "Image/UI/Gage/curHP.bmp", 1, 30);
	//#======================================== T e x t ============================================================
	_loading->loadImage("HP", "Image/UI/Font/HP.bmp", 24, 12);
	_loading->loadImage("KR", "Image/UI/Font/KR.bmp", 24, 12);
	_loading->loadImage("SansStart", "Image/UI/Font/SansStart.bmp", 536, 26);
	_loading->loadImage("NapstablookStart", "Image/UI/Font/NapstablookStart.bmp", 451, 22);
	_loading->loadImage("DummyStart", "Image/UI/Font/DummyStart.bmp", 222, 22);
	

	//#=============================================================================================================
	//#									Ÿ�� �̹��� �ҷ�����
	//#=============================================================================================================
	_loading->loadImage("null", "Image/Tileset/nullTile.bmp", 40, 40);
	_loading->loadFrameImage("Tile1", "Image/Tileset/Home1.bmp", 160, 100, 8, 5);
	_loading->loadFrameImage("Tile2", "Image/Tileset/Ruin1.bmp", 160, 100, 8, 5);
	_loading->loadFrameImage("Tile3", "Image/Tileset/Ruin2.bmp", 160, 100, 8, 5);
	_loading->loadFrameImage("Tile4", "Image/Tileset/Ruin3.bmp", 160, 100, 8, 5);
	_loading->loadFrameImage("Tile5", "Image/Tileset/Ruin4.bmp", 160, 100, 8, 5);
	_loading->loadFrameImage("Tile6", "Image/Tileset/RuinObject.bmp", 160, 100, 8, 5);
	//#=============================================================================================================
	//#									ĳ���� �̹��� �ҷ�����
	//#=============================================================================================================
	_loading->loadFrameImage("Frisk", "Image/Character/Frisk.bmp", 76, 116, 4, 4);
	_loading->loadFrameImage("Red", "Image/Character/Red.bmp", 16, 32, 1, 2);
	_loading->loadFrameImage("Flee", "Image/Character/Flee.bmp", 32, 16, 2, 1);
	_loading->loadFrameImage("Blue", "Image/Character/Blue.bmp", 64, 32, 4, 2);
	_loading->loadFrameImage("LightBlue", "Image/Character/LightBlue.bmp", 16, 32, 1, 2);
	_loading->loadFrameImage("Orange", "Image/Character/Orange.bmp", 16, 32, 1, 2);
	_loading->loadFrameImage("Yellow", "Image/Character/Yellow.bmp", 32, 32, 2, 2);
	_loading->loadImage("Break", "Image/Character/Break.bmp", 20, 16);
	//#=============================================================================================================
	//#									���ʹ� �̹��� �ҷ�����
	//#=============================================================================================================
	_loading->loadImage("Dummy", "Image/Enemy/Dummy/Dummy.bmp", 39, 52);
	_loading->loadFrameImage("Napstablook", "Image/Enemy/Napstablook/Napstablook.bmp", 104, 83, 2, 1);
	_loading->loadFrameImage("SansFace", "Image/Enemy/Sans/Face/face.bmp", 160, 90, 5, 3);
	_loading->loadImage("SansBody", "Image/Enemy/Sans/Body/body.bmp", 54, 72);
	_loading->loadFrameImage("SansHandDown", "Image/Enemy/Sans/Body/HandDown.bmp", 310, 72, 4, 1);
	_loading->loadFrameImage("SansHandRight", "Image/Enemy/Sans/Body/HandRight.bmp", 310, 72, 4, 1);
	//#=============================================================================================================
	//#									���ʹ� ���� �̹��� �ҷ�����
	//#=============================================================================================================
	_loading->loadImage("Tear", "Image/AttackEffect/Tear.bmp", 12, 13);
	_loading->loadFrameImage("GasterBlaster", "Image/AttackEffect/GasterBlaster.bmp", 252, 57, 6, 1);
	_loading->loadFrameImage("KnifeSlash", "Image/AttackEffect/KnifeSlash.bmp", 112, 66, 7, 1);
	_loading->loadImage("Bone1", "Image/AttackEffect/Bone1.bmp", 14, 44);
	_loading->loadFrameImage("BlueBone", "Image/AttackEffect/BlueBone.bmp", 10, 18, 1, 3);
	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����

}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound()
{
	//======================================= �� �� �� ==============================================================
	//#=============================================================================================================
	//#									BGM �ҷ�����
	//#=============================================================================================================
	_loading->loadSound("Megalovania", "SOUND/BGM/Megalovania.mp3");
	_loading->loadSound("GhoseFight", "SOUND/BGM/Ghose Fight.mp3");
	_loading->loadSound("VGM", "SOUND/BGM/VGM.mp3");
	//#=============================================================================================================
	//#									SE �ҷ�����
	//#=============================================================================================================



}