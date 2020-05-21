#include "stdafx.h"
#include "inGameScene.h"

HRESULT inGameScene::init()
{
	_ingameScreen = { 0, 0, WINSIZEX, WINSIZEY };								//_ingameScreen Rect ��ġ�� ũ�� ����
	_statInfo = RectMake(341, 60, 800, 600);			//_statInfo Rect ��ġ�� ũ�� ����
	_inven = _statInfo;															//_inven Rect ��ġ�� ũ��� _statInfo�� ����.
	_menuRect = RectMakeCenter(200, WINSIZEY / 2, 250, 250);					//_menuRect Rect ��ġ�� ũ�� ����
	//_menu Rect�� ��ġ�� ũ�� ����
	_menu[0] = RectMake(_menuRect.left + 90, _menuRect.top + 10, 140, 70);		
	_menu[1] = RectMake(_menuRect.left + 90, _menu[0].bottom + 10, 140, 70);	
	_menu[2] = RectMake(_menuRect.left + 90, _menu[1].bottom + 10, 140, 70);	
	////_menu Rect ���� ����
	_text[0] = "��ǰ";
	_text[1] = "����";
	_text[2] = "��ȭ";

	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = new player;
	_player->init(WINSIZEX / 2, WINSIZEY / 2);
	_player->setImage(IMAGEMANAGER->findImage("Frisk"));

	//���Ŵ��� Ŭ���� �ʱ�ȭ

	//_astar
	_astar = new astar;
	_astar->init();
	//��ȣ����
	_mapNumber = 1;

	//map�� LT ��ǥ
	_mapPoint.x = 0;
	_mapPoint.y = 0;
	_wait = 0.0f;
	if (PLAYERDATA->getHp() != -1)
	{
		_player->setPlayerHP(PLAYERDATA->getHp());
		_player->setPlayerMaxHP(PLAYERDATA->getMaxHP());
		_player->setPlayerGold(PLAYERDATA->getGold());
		_player->setPlayerPoint(PLAYERDATA->getPlayerPoint());
		_mapNumber = PLAYERDATA->getMapNumber();
		_mapPoint.x = PLAYERDATA->getMapPoint().x;
		_mapPoint.y = PLAYERDATA->getMapPoint().y;
		_ePoint.x = PLAYERDATA->getEPoint().x;
		_ePoint.y = PLAYERDATA->getEPoint().y;
		_wait = 5.0f;
	}
	//���� �ҷ����� ���� mapName�� �� �̸� ����
	sprintf_s(mapName, "Data/Map/MAP%d", _mapNumber);

	//�� �ҷ�����
	loadMap();

	//A*�� ��� ���� ����(_map�� xSize, ySize);
	_astar->setMapData(_map.xSize, _map.ySize);

	//������ ������ Rect �ʱ�ȭ
	for (int i = 0; i < _map.tile.size(); i++)
	{
		_astar->setTotalNodeRc(i, _map.tile[i].rc);
	}

	//NODE_WALL ����
	for (int i = 0; i < _map.tile.size(); i++)
	{
		for (int layer = 0; layer < 3; layer++)
		{
			if (_map.tile[i].canMove[layer] == FALSE) { _astar->setWall(i); }
		}
	}

	//A* ���� ��Ʈ ����
	_astar->setStartNode(0, 0);
	
	//EnemySpawner�� ��ǥ�� �ϴ� A*�� ���
	_eSpawnerGoal = 0;
	if (PLAYERDATA->getHp() == -1)
	{
		_ePoint = { _astar->getStartNode()->idx + 20, _astar->getStartNode()->idy + 20 };
	}
	_enemySpawner = RectMakeCenter(_ePoint.x, _ePoint.y, 40, 40);

	_isMenu = FALSE;
	_isInven = FALSE;
	_isState = FALSE;
	_isCall = FALSE;
	_isDialog = FALSE;

	_count = 0;
	_dialogCount = 0;
	_dialogSize = 0;
	_menuCount = 0;
	_selectCount = 0;
	
	_timer = TIMEMANAGER->getWorldTime();
	_debugMode = TRUE;

	return S_OK;
}

void inGameScene::release()
{

}

void inGameScene::update()
{
	if (_isDialog)
	{
		if(INPUT->GetKeyDown(0x43)) 
		{
			_dialogCount = _dialogText[_dialogSize].size();
		}
		if (INPUT->GetKeyDown(0x5A))
		{
			if (_dialogCount == _dialogText[_dialogSize].size())
			{
				if (_dialogSize+1 >= _dialogText.size())
				{
					_isDialog = FALSE;
					_isCall = FALSE;
					_isMenu = FALSE;
					_isState = FALSE;
					_isInven = FALSE;
					_dialogSize = 0;
					_dialogCount = 0;
					_dialogText.clear();
					return;
				}
				else
				{
					_dialogSize++; 
					_dialogCount = 0;
				}
			}
			
		}
		if (_dialogCount < _dialogText[_dialogSize].size())
		{
			if (TIMEMANAGER->getWorldTime() - _timer >= 0.01f)
			{
				_count++;
				_timer = TIMEMANAGER->getWorldTime();


				if (_count == 3)
				{
					if ((_dialogText[_dialogSize][_dialogCount] & 0x80) == 0x80) { _dialogCount += 2; }
					else { _dialogCount++; }
					_count = 0;
				}
			}
		}
	}
	if (_isMenu)
	{
		if (INPUT->GetKeyDown(0x43)) 
		{
			if (_isInven) { _isInven = FALSE; }
			else if (_isState) { _isState = FALSE; }
			else if (_isCall) { _isCall = FALSE; }
			else { _isMenu = FALSE; }
		}
		if (INPUT->GetKeyDown(0x5A))
		{
			if (!_isInven && !_isState && !_isCall && !_isDialog)
			{
				switch (_menuCount)
				{
				case 0:
					_isInven = TRUE;
					break;
				case 1:
					_isState = TRUE;
					break;
				case 2:
					_isCall = TRUE;
					_dialogText.push_back("* �� ��ȭ��� ���峵��.");
					_dialogSize = 0;
					_isDialog = TRUE;
					break;
				}
			}
		}
		if (INPUT->GetKeyDown(VK_LEFT))
		{
			if (_player->getInven()->getItem().size() > 0)
			{
				if (_selectCount > 0) { _selectCount--; }
			}
		}
		if (INPUT->GetKeyDown(VK_RIGHT))
		{
			if (_player->getInven()->getItem().size() > 0)
			{
				if (_selectCount < _player->getInven()->getItem().size() - 1) { _selectCount++; }
			}
		}
		if (INPUT->GetKeyDown(VK_UP))
		{
			if (!_isInven && !_isState && !_isCall)
			{
				if (_menuCount > 0) { _menuCount--; }
			}
		}
		if (INPUT->GetKeyDown(VK_DOWN))
		{
			if (!_isInven && !_isState && !_isCall)
			{
				if (_menuCount < 2) { _menuCount++; }
			}
		}

		if (_player->getPlayerPoint().y < WINSIZEY / 2)
		{
			_smallInfo = RectMakeCenter(200, 140, 250, 160);
			_dialog = RectMake(_smallInfo.left, WINSIZEY - 220, _statInfo.right - _smallInfo.left, 160);
		}
		else
		{
			_smallInfo = RectMakeCenter(200, WINSIZEY - 140, 250, 160);
			_dialog = RectMake(_smallInfo.left, 60, _statInfo.right - _smallInfo.left, 160);
		}
	}
	else
	{
		if (INPUT->GetKeyDown(VK_SPACE)) { _debugMode = !_debugMode; }
		if (_wait > 0.0f)
		{
			if (TIMEMANAGER->getWorldTime() - _timer >= 0.1f)
			{
				_wait -= 0.1f;
				_timer = TIMEMANAGER->getWorldTime();
			}
		}
		else
		{
			if (!PtInRect(&_astar->getEndNode()->rc, _player->getPlayerPoint()))
			{
				for (int i = 0; i < _map.tile.size(); i++)
				{
					if (PtInRect(&_astar->getTotalNode()[i]->rc, _player->getPlayerPoint()))
					{
						_eSpawnerGoal = 0;

						_astar->setEndNode(i);
						moveStartNode();
						_astar->pathFinding();

						break;
					}
				}
			}

			if (_astar->getFinalList().size() != 0)
			{
				if (_ePoint.x == _astar->getFinalList()[_eSpawnerGoal]->rc.left + 20
					&& _ePoint.y == _astar->getFinalList()[_eSpawnerGoal]->rc.top + 20)
				{
					if (_eSpawnerGoal != _astar->getFinalList().size() - 1)
					{
						_astar->eraseFinalList();
					}
				}
				else
				{
					if (_ePoint.x < _astar->getFinalList()[_eSpawnerGoal]->rc.left + 20) { _ePoint.x += 4; }
					if (_ePoint.x > _astar->getFinalList()[_eSpawnerGoal]->rc.left + 20) { _ePoint.x -= 4; }
					if (_ePoint.y < _astar->getFinalList()[_eSpawnerGoal]->rc.top + 20) { _ePoint.y += 4; }
					if (_ePoint.y > _astar->getFinalList()[_eSpawnerGoal]->rc.top + 20) { _ePoint.y -= 4; }
					_enemySpawner = RectMakeCenter(_ePoint.x, _ePoint.y, 50, 50);
				}
			}
			if (IntersectRect(&rc, &_enemySpawner, &_player->getPlayerRect()))
			{
				_player->setBattle(TRUE);
				PLAYERDATA->setHp(_player->getPlayerHP());
				PLAYERDATA->setMaxHP(_player->getPlayerMaxHP());
				PLAYERDATA->setPlayerPoint(_pPoint.x, _pPoint.y);
				PLAYERDATA->setMapNumber(_mapNumber);
				PLAYERDATA->setMapPoint(_mapPoint.x, _mapPoint.y);
				PLAYERDATA->setEPoint(_ePoint.x, _ePoint.y);
				SCENEMANAGER->loadScene("����ȭ��");
			}
		}

		//�÷��̾� Ŭ���� ������Ʈ
		_player->update();
		//���Ŵ��� ������Ʈ
		_mapRect = RectMake(_mapPoint.x, _mapPoint.y, _map.xSize * 40, _map.ySize);
		_walkPOINT[0] = { _pRect.left + 5, _pRect.top + 5 };
		_walkPOINT[1] = { _pRect.right - 5, _pRect.top + 5 };
		_walkPOINT[2] = { _pRect.left + 5, _pRect.bottom - 5 };
		_walkPOINT[3] = { _pRect.right - 5, _pRect.bottom - 5 };

		_pPoint = _player->getPlayerPoint();
		_pRect = _player->getPlayerRect();
		this->playerControl();
	}
}

void inGameScene::render()
{
	for (int i = 0; i < _mapSize; i++)
	{
		if (IntersectRect(&rc, &_map.tile[i].rc, &_ingameScreen))
		{
			for (int layer = 0; layer < 1; layer++)
			{
				sprintf_s(tileName, "Tile%d", _map.tile[i].imagePage[layer]);
				IMAGEMANAGER->scaleFrameRender(tileName, getMemDC(), _map.tile[i].rc.left, _map.tile[i].rc.top, _map.tile[i].tileFrameX[layer],
					_map.tile[i].tileFrameY[layer], 2.0f);
			}
		}
		if (_map.tile[i].rc.top > WINSIZEY) { break; }
	}
	_player->render();
	if(_debugMode)
	{ 
		_astar->render();
	}

	HBRUSH brush, oldBrush;
	brush = CreateSolidBrush(RGB(128, 0, 128));
	oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Rectangle(getMemDC(), _enemySpawner);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	if (_isMenu)
	{
		string s;
	
		SetTextColor(getMemDC(), RGB(255, 255, 255));	//�ؽ�Ʈ �÷� = WHITE
		SetBkColor(getMemDC(), RGB(0, 0, 0));			//�ؽ�Ʈ ��� = BLACK
		HFONT font, oldFont;				//��Ʈ ����
		font = CreateFont(30, 30, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "DungGeunMo");
		oldFont = (HFONT)SelectObject(getMemDC(), font);


		brush = CreateSolidBrush(RGB(0, 0, 0));			//���� �÷� = BLACK
		oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

		//������ ���� �׸��� ����
		Rectangle(getMemDC(), _smallInfo);
		TextOut(getMemDC(), _smallInfo.left, _smallInfo.top, _player->getPlayerName().c_str(), _player->getPlayerName().size());

		font = CreateFont(30, 25, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "DungGeunMo");
		oldFont = (HFONT)SelectObject(getMemDC(), font);

		TextOut(getMemDC(), _smallInfo.left + 20, _smallInfo.top+20, "LV", strlen("LV"));
		s = to_string(_player->getPlayerLV());
		TextOut(getMemDC(), _smallInfo.left + 100, _smallInfo.top+20, s.c_str(), s.size());

		TextOut(getMemDC(), _smallInfo.left + 20, _smallInfo.top + 60, "HP", strlen("HP"));
		s = to_string(_player->getPlayerHP()) + "/" + to_string(_player->getPlayerMaxHP());
		TextOut(getMemDC(), _smallInfo.left + 100, _smallInfo.top + 60, s.c_str(), s.size());

		TextOut(getMemDC(), _smallInfo.left + 20, _smallInfo.top + 100, "G", strlen("G"));
		s = to_string(_player->getPlayerGold());
		TextOut(getMemDC(), _smallInfo.left + 100, _smallInfo.top + 100, s.c_str(), s.size());

		frameDraw(_smallInfo);
		//������ ���� ��� ����

		//�޴�â �׸��� ����
		IMAGEMANAGER->render("Menu", getMemDC(), _menuRect.left, _menuRect.top);
		frameDraw(_menuRect);
		//�޴�â �׸��� ����

		if (!_isState && !_isInven && !_isCall)
		{
			IMAGEMANAGER->frameRender("Red", getMemDC(), _menu[_menuCount].left - 30, _menu[_menuCount].top + 25, 0, 0);
		}
		//�׸��� ����
		//����â �׸��� ����
		if (_isState)
		{
			Rectangle(getMemDC(), _statInfo);
			frameDraw(_statInfo);
		}
		//�׸��� ����
		//�κ��丮 ���빰 �׸��� ����
		if (_isInven)
		{
			font = CreateFont(50, 25, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "DungGeunMo");
			oldFont = (HFONT)SelectObject(getMemDC(), font);

			Rectangle(getMemDC(), _inven);
			for (int i = 0; i < _player->getInven()->getItem().size(); i++)
			{
				TextOut(getMemDC(), _inven.left + 40 + 430 * (i % 2), _inven.top + 65 * ((i / 2) + 1),
					_player->getInven()->getItem()[i]->getItemName(), strlen(_player->getInven()->getItem()[i]->getItemName()));
				if (_selectCount == i)
				{
					IMAGEMANAGER->scaleFrameRender("Red", getMemDC(), _inven.left + 7 + 430 * (i % 2), (_inven.top + 12) + 65 * ((i / 2) + 1), 0, 0, 1.6f);
				}
			}
			frameDraw(_inven);

			font = CreateFont(50, 30, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "DungGeunMo");
			oldFont = (HFONT)SelectObject(getMemDC(), font);

		}
		//�׸��� ����
		//��ȭâ �׸��� ����
		if (_isDialog)
		{
			Rectangle(getMemDC(), _dialog);
			TextOut(getMemDC(), _dialog.left, _dialog.top, _dialogText[_dialogSize].c_str(), _dialogCount);
			frameDraw(_dialog);
		}
		//��ȭâ �׸��� ����
		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetTextColor(getMemDC(), RGB(0, 0, 0));

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
	}
}

void inGameScene::loadMap()
{
	ifstream in(mapName, ios::in | ios::binary);

	in >> _map.xSize >> _map.ySize;

	_mapSize = _map.xSize * _map.ySize;
	_map.tile.resize(_mapSize);

	for (int y = 0; y < _map.xSize; y++)
	{
		for (int x = 0; x < _map.ySize; x++)
		{
			for (int layer = 0; layer < 3; layer++)
			{
				in >> _map.tile[y * _map.xSize + x].canMove[layer] >> _map.tile[y * _map.xSize + x].imagePage[layer] >>
					_map.tile[y * _map.xSize + x].tileFrameX[layer] >> _map.tile[y * _map.xSize + x].tileFrameY[layer];
			}
			in >> _map.tile[y * _map.xSize + x].rc.left >> _map.tile[y * _map.xSize + x].rc.top >> _map.tile[y * _map.xSize + x].rc.right >> _map.tile[y * _map.xSize + x].rc.bottom;
			in >> _map.tile[y * _map.xSize + x].terrain.x >> _map.tile[y * _map.xSize + x].terrain.y;
			_map.tile[y * _map.xSize + x].rc.left = _mapPoint.x + (x * 40);
			_map.tile[y * _map.xSize + x].rc.right = _map.tile[y * _map.xSize + x].rc.left + 40;
			_map.tile[y * _map.xSize + x].rc.top = _mapPoint.y + (y * 40);
			_map.tile[y * _map.xSize + x].rc.bottom = _map.tile[y * _map.xSize + x].rc.top + 40;
		}
	}
}

void inGameScene::moveStartNode()
{
	for (int i = 0; i < _mapSize; i++)
	{
		if (PtInRect(&_map.tile[i].rc, _ePoint))
		{
			_astar->setStartNode(i % _map.xSize, i / _map.xSize);
			break;
		}
	}
}
void inGameScene::directCheck()
{
	for (int i = 0; i < _mapSize; i++)
	{
		if (PtInRect(&_map.tile[i].rc, _walkPOINT[0]) || PtInRect(&_map.tile[i].rc, _walkPOINT[1]))
		{
			for (int layer = 0; layer < 3; layer++)
			{
				if (_map.tile[i].canMove[layer] == FALSE)
				{
					_walkCheck[0] = FALSE;
					break;
				}
				else { _walkCheck[0] = TRUE; }
			}
		}
		if (PtInRect(&_map.tile[i].rc, _walkPOINT[2]) || PtInRect(&_map.tile[i].rc, _walkPOINT[3]))
		{
			for (int layer = 0; layer < 3; layer++)
			{
				if (_map.tile[i].canMove[layer] == FALSE)
				{
					_walkCheck[1] = FALSE;
					break;
				}
				else { _walkCheck[1] = TRUE; }

			}
		}
		if (PtInRect(&_map.tile[i].rc, _walkPOINT[0]) || PtInRect(&_map.tile[i].rc, _walkPOINT[2]))
		{
			for (int layer = 0; layer < 3; layer++)
			{
				if (_map.tile[i].canMove[layer] == FALSE)
				{
					_walkCheck[2] = FALSE;
					break;
				}
				else { _walkCheck[2] = TRUE; }
			}
		}
		if (PtInRect(&_map.tile[i].rc, _walkPOINT[1]) || PtInRect(&_map.tile[i].rc, _walkPOINT[3]))
		{
			for (int layer = 0; layer < 3; layer++)
			{
				if (_map.tile[i].canMove[layer] == FALSE)
				{
					_walkCheck[3] = FALSE;
					break;
				}
				else { _walkCheck[3] = TRUE; }
			}
		}

	}
}

void inGameScene::playerControl()
{
	this->directCheck();

	if (INPUT->GetKeyDown(0x43)) { _isMenu = TRUE; }
	if (INPUT->GetKey(VK_UP) && _walkCheck[0])
	{
		if (_pPoint.y <= 240)
		{
			if (_map.tile[0].rc.top < 0)
			{
				for (int i = 0; i < (int)_map.tile.size(); i++)
				{
					_map.tile[i].rc.top += _player->getPlayerSpeed();
					_map.tile[i].rc.bottom += _player->getPlayerSpeed();
					_astar->setTotalNodeRc(i, _map.tile[i].rc);
				}
			}
			else
			{
				if (_pPoint.y - 20 <= 0) { _pPoint.y = 20; }
				else
				{
					_pPoint.y -= _player->getPlayerSpeed();
				}
			}
		}
		else
		{
			if (_pPoint.y - 20 <= 0) { _pPoint.y = 20; }
			else
			{
				_pPoint.y -= _player->getPlayerSpeed();
			}
		}
	}
	if (INPUT->GetKey(VK_DOWN) && _walkCheck[1])
	{
		if (_pPoint.y >= 480)
		{
			if (_map.tile[(int)_map.tile.size() - 1].rc.bottom > WINSIZEY)
			{
				for (int i = 0; i < (int)_map.tile.size(); i++)
				{
					_map.tile[i].rc.top -= _player->getPlayerSpeed();
					_map.tile[i].rc.bottom -= _player->getPlayerSpeed();
					_astar->setTotalNodeRc(i, _map.tile[i].rc);
				}
			}
			else
			{
				if (_pPoint.y + 20 > _map.tile[(int)_map.tile.size() - 1].rc.bottom)
				{
					_pPoint.y = _map.tile[(int)_map.tile.size() - 1].rc.bottom - 20;
				}
				else
				{
					_pPoint.y += _player->getPlayerSpeed();
				}
			}
		}
		else
		{
			if (_pPoint.y + 20 >= _map.tile[(int)_map.tile.size() - 1].rc.bottom) 
			{
				_pPoint.y = _map.tile[(int)_map.tile.size() - 1].rc.bottom - 20;
			}
			else
			{
				_pPoint.y += _player->getPlayerSpeed();
			}
		}
	}
	if (INPUT->GetKey(VK_LEFT) && _walkCheck[2])
	{
		if (_pPoint.x <= 320)
		{
			if (_map.tile[0].rc.left < 0)
			{
				for (int i = 0; i < (int)_map.tile.size(); i++)
				{
					_map.tile[i].rc.left += _player->getPlayerSpeed();
					_map.tile[i].rc.right += _player->getPlayerSpeed();
					_astar->setTotalNodeRc(i, _map.tile[i].rc);
				}
			}
			else
			{
				if (_pPoint.x - 20 <= _map.tile[0].rc.left)
				{
					_pPoint.x = _map.tile[0].rc.left + 20;
				}
				else
				{
					_pPoint.x -= _player->getPlayerSpeed();
				}
			}
		}
		else
		{
			if (_pPoint.x - 20 <= _map.tile[0].rc.left)
			{
				_pPoint.x = _map.tile[0].rc.left + 20;
			}
			else
			{
				_pPoint.x -= _player->getPlayerSpeed();
			}
		}
	}
	if (INPUT->GetKey(VK_RIGHT) && _walkCheck[3])
	{
		if (_pPoint.x >= 920)
		{
			if (_map.tile[(int)_map.tile.size() - 1].rc.right > WINSIZEX)
			{
				for (int i = 0; i < (int)_map.tile.size(); i++)
				{
					_map.tile[i].rc.left -= _player->getPlayerSpeed();
					_map.tile[i].rc.right -= _player->getPlayerSpeed();
					_astar->setTotalNodeRc(i, _map.tile[i].rc);
				}
			}
			else
			{
				if (_pPoint.x + 20 >= _map.tile[(int)_map.tile.size() - 1].rc.right) 
				{
					_pPoint.x = _map.tile[(int)_map.tile.size() - 1].rc.right - 20;
				}
				else
				{
					_pPoint.x += _player->getPlayerSpeed();
				}
			}
		}
		else
		{
			if (_pPoint.x + 20 >= _map.tile[(int)_map.tile.size() - 1].rc.right)
			{
				_pPoint.x = _map.tile[(int)_map.tile.size() - 1].rc.right - 20;
			}
			else
			{
				_pPoint.x += _player->getPlayerSpeed();
			}
		}
	}
	_player->setPlayerPoint(_pPoint);
}

void inGameScene::savePlayerInfo()
{
	PLAYERDATA->setPlayerPoint(_pPoint);
	PLAYERDATA->setMapNumber(_mapNumber);
}

void inGameScene::map1WarpPoint()
{
	_vWarp.clear();
	_warp.mapNum = 2;
	//�� ������ Rect �����Ű��
	//_warp.rc = ;
	_vWarp.push_back(_warp);
}

void inGameScene::map2WarpPoint()
{
	_vWarp.clear();
	_warp.mapNum = 1;
	//_warp.rc = ;
	_vWarp.push_back(_warp);
	_warp.mapNum = 3;
	//_warp.rc = ;
	_vWarp.push_back(_warp);
}

void inGameScene::map3WarpPoint()
{
	_vWarp.clear();
	_warp.mapNum = 2;
	//_warp.rc = ;
	_vWarp.push_back(_warp);
}

void inGameScene::frameDraw(RECT rc)
{
	FrameRect(getMemDC(), rc, (RGB(255, 255, 255)));
}