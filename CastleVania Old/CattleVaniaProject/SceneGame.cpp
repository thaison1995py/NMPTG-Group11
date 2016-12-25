
#include "SceneGame.h"

#define BACKGROUND_FILE "Resources/black.png"
#define BACKGROUND_WHITE_FILE "Resources/white.png"

SceneGame::SceneGame(void) : Scene(ESceneState::Game_Scene)
{
	_loadLevel = false;
	_playedDie = false;
	_moveCameraDone = false;
	_beginMoveCamera = false;
	_moveCameraHaft = false;
	_rangeMoveCamera = 0;
	camera = new CCamera();
	bg = NULL;
	_gameScore = NULL;
	_levelNow = 1;
	_stageNow = 4;
	_score = 0;
	_lifes = 5;
	_stateCamera = EStateCamera::Update_Camera;
	stateGame = EState::None_State;

}

void SceneGame::LoadLevel(int level)
{
	bg = new QBackground(level);

	
	/*simon = new Simon(1619, 736);
	camera->viewport.y = 482+32*12;*/
	simon = new Simon(278, 1350);
	camera->viewport.y = 482 +32 * 12*3;
	_gameScore = new GameScore(G_Device, 22, G_ScreenWidth, G_ScreenHeight);
	_gameScore->initTimer(100);
	////ResetLevel();

	//switch (level)
	//{
	//case 3:
	//	{
	//		camera->viewport.y = 450;
	//		bg = new QBackground(level);
	//		bg->LoadTree();
	//		simon = new Simon(50, 64);
	//		_gameScore = new GameScore(G_Device,22,G_ScreenWidth,G_ScreenHeight);			
	//		_gameScore->initTimer(100);
	//		SoundManager::GetInst()->RemoveAllBGM();
	//		SoundManager::GetInst()->PlayBGSound(EBGSound::EStage1Sound);
	//	}
	//	break;
	//case 2:
	//	{
	//		camera->viewport.y = 834;
	//		bg = new QBackground(level);
	//		bg->LoadTree();
	//		simon->posX = 50;
	//		simon->posY = 450;
	//		simon->_action = Action::Idle;
	//		_stageReset = 2;
	//	}
	//	break;
	//case 1:
	//	{
	//		_gameScore->initTimer(300);
	//		camera->viewport.y = 242;
	//		bg = new QBackground(level);
	//		bg->LoadTree();
	//		simon = new Simon(50, 64);
	//		simon->posX = 1792;
	//		simon->posY = 48;

	//		//simon = new Simon(521 , 942);
	//		//simon = new Simon(3776 , 112);
	//		SoundManager::GetInst()->RemoveAllBGM();
	//		SoundManager::GetInst()->PlayBGSound(EBGSound::EStage2Sound);
	//		_stageReset = 4;
	//	}
	//	break;
	//default:
	//	break;
	//}
	posStageToReset.x = simon->posX;
	posStageToReset.y = simon->posY;
	posCamera = camera->viewport;
}

void SceneGame::LoadStage(int stage)
{
	if (stage == 4)
	{
		qGameObject = new QGameObject("Resources/Maps/ObjectInMap.txt",
										"Resources\\Maps\\QuadTree.txt");
	}
	_queenMedusa = qGameObject->getQueenMedusa();
	

	
	
	openDoor = new OpenDoor( 688,3088 );
	if (simon->posX > 2820 && simon->posX<3460)
	{
		posDoor.x = 3088;
		posDoor.y = 688;
		openDoor->SetPos(posDoor.x, posDoor.y);
	}
	else 	if (simon->posX< 1995 && simon->posX > 1220)
	{
		posDoor.x = 1560;
		posDoor.y = 1008;
		openDoor->SetPos(posDoor.x, posDoor.y);
	}

	if (simon->posX < 4096 && simon->posX>3105)
		G_MaxSize = 4096;
	else
		if (simon->posX < 3074 && simon->posX>1585)
			G_MaxSize = 3074;
		else if (simon->posX < 1550)
			G_MaxSize = 1536;

	if (simon->posY < 384)
		G_MinSize = 3584;
	else
		if (simon->posY < 770 && simon->posX < 4096 && simon->posX>3105)
			G_MinSize = 3072;
		else if (simon->posY < 770 && simon->posX < 3074 && simon->posX>1585)
			G_MinSize = 1536;
		else if (simon->posY < 1148 && simon->posX < 3074 && simon->posX>1585)
			G_MinSize = 1556;
		else if (simon->posY < 1148 && simon->posX < 1550)
			G_MinSize = 16;

		if (_queenMedusa->_hasGetUp)
		{
			G_MinSize = 16;
			G_MaxSize = 512;
		}
		camera->SetSizeMap(G_MaxSize, G_MinSize);

}

void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int deltaTime)
{
	if (simon->posX > 2820 && simon->posX<3460)
	{
		posDoor.x = 3088;
		posDoor.y = 688;
		openDoor->SetPos(posDoor.x,posDoor.y);
	}
	else 	if (simon->posX< 1995 && simon->posX > 1220)
	{
		posDoor.x = 1560;
		posDoor.y = 1008;
		openDoor->SetPos(posDoor.x, posDoor.y);
	}

	if (simon->posX < 4096 && simon->posX>3105)
		G_MaxSize = 4096;
	else
		if (simon->posX < 3074 && simon->posX>1585)
			G_MaxSize = 3074;
		else if (simon->posX < 1550)
			G_MaxSize = 1536;

	if (simon->posY < 384)
		G_MinSize = 3584;
	else
		if (simon->posY < 770 && simon->posX < 4096 && simon->posX>3105)
			G_MinSize = 3072;
		else if (simon->posY < 770 && simon->posX < 3074 && simon->posX>1585)
			G_MinSize = 1536;
		else if (simon->posY < 1148 && simon->posX < 3074 && simon->posX>1585)
			G_MinSize = 1556;
		else if (simon->posY < 1148 && simon->posX < 1550)
			G_MinSize = 16;
	
		if (_queenMedusa->_hasGetUp)
		{
			G_MinSize = 16;
			G_MaxSize = 512;
		}
		camera->SetSizeMap(G_MaxSize, G_MinSize);
	//#pragma region

	//
	//	if(_levelNow == 0)
	//	{
	//		_levelNow++;
	//		_stageNow++;
	//		LoadResources(G_Device);
	//		/*if(introScene->_loadOK)
	//		{
	//			_levelNow++;
	//			_stageNow++;
	//			LoadResources(G_Device);
	//		}
	//		else 
	//		{
	//			introScene->Update(deltaTime);
	//			G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//			introScene->Draw(camera);
	//			G_SpriteHandler->End();
	//		}*/
	//	}
	//	else if(_levelNow > 0)
	//	{
	//			_levelNow++;
	//			_stageNow ++;
	//			LoadResources(G_Device);
	//			//simon->_action = Action::Idle;
	//			simon->_colCastleGate = false;
	//			_loadLevel = true;
	//		////--------Xu ly di vao cong thanh----------
	//		//if(simon->_colCastleGate && simon->_action == Action::IntoCastle && !_loadLevel)
	//		//{
	//		//	_levelNow++;
	//		//	_stageNow ++;
	//		//	LoadResources(G_Device);
	//		//	//simon->_action = Action::Idle;
	//		//	simon->_colCastleGate = false;
	//		//	simon->sprite->SelectIndex(0);
	//		//	_loadLevel = true;
	//		//}
	//
	//		if(_stateCamera == EStateCamera::Update_Camera)
	//		{
	//			camera->UpdateCamera(simon->posX);
	//			ChangeCamera(simon->GetDirectDoor());
	//		}
	//		else
	//			//-------------Di chuyen camera, chuyen canh ------------
	if (_stateCamera == EStateCamera::Update_Camera)
	{
		camera->UpdateCamera(simon->posX);
		ChangeCamera(simon->GetDirectDoor());
	}
	else
		//-------------Di chuyen camera, chuyen canh ------------
#pragma region
	{
		if (_beginMoveCamera)
		{
			//qGameObject->RemoveAllObject();
			MoveCamera(_rangeMoveCamera);
		}
		if (_moveCameraHaft)
		{
			if (openDoor->GetOpenDoor())
				openDoor->RenderOpen();
			if (openDoor->GetOpenDoor() == false)
			{
				simon->AutoMove(_rangeMoveSimon, deltaTime);
				if (_rangeMoveSimon == 0)
				{
					simon->SetDirectDoor(EDirectDoor::NoneDoor);
					openDoor->RenderClose();
					if (openDoor->GetCloseDoor() == false)
					{
						MoveCamera(_rangeMoveCamera2);
					}
					else
					{
						simon->_allowPress = true;

					}
				}
			}
		}
	}
	//------Thao tac khi simon chet-------
#pragma region 
	if (simon->GetHPSimon() <= 0 && !simon->_simonDeath)
	{
		_timeToReset = 100;
		simon->_simonDeath = true;
	}
	if (simon->_simonDeath)
	{
		if (_timeToReset > 0)
		{
			if (!_playedDie)
			{
				SoundManager::GetInst()->RemoveAllBGM();
				SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_LifeLost);
				_playedDie = true;
			}
			simon->SimonDeath(_timeToReset);
		}
		else
		{
			_playedDie = false;
			simon->_simonDeath = false;
			simon = new Simon(posStageToReset.x, posStageToReset.y);
			LoadStage(_stageReset);
			camera->viewport = posCamera;
			_stageNow = _stageReset;
			_lifes--;
			if (_lifes <= 0)
			{
				sceneState = ESceneState::Menu_Scene;
			}
			else
			{
				SoundManager::GetInst()->RemoveAllBGM();
				SoundManager::GetInst()->PlayBGSound(EBGSound::EStage1Sound);
			}
		}
	}
#pragma endregion Simon Death Reponse

	//#pragma endregion Chuyen canh, dich chuyen camera
	//		//------Thao tac khi simon chet-------
	//#pragma region 
	//		if(simon->GetHPSimon() <= 0 && !simon->_simonDeath)
	//		{
	//			_timeToReset = 100;
	//			simon->_simonDeath = true;
	//		}
	//		if(simon->_simonDeath)
	//		{
	//			if(_timeToReset > 0)
	//			{
	//				if(!_playedDie)
	//				{
	//					SoundManager::GetInst()->RemoveAllBGM();
	//					SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_LifeLost);
	//					_playedDie = true;
	//				}
	//				simon->SimonDeath(_timeToReset);
	//			}
	//			else
	//			{
	//				_playedDie = false;
	//				simon->_simonDeath = false;
	//				simon = new Simon(posStageToReset.x, posStageToReset.y);
	//				LoadStage(_stageReset);
	//				camera->viewport = posCamera;
	//				_stageNow = _stageReset;
	//				_lifes--;
	//				if(_lifes <= 0)
	//				{
	//					sceneState = ESceneState::Menu_Scene;
	//				}
	//				else
	//				{
	//					if(_stageNow <= 4)
	//					{
	//						SoundManager::GetInst()->RemoveAllBGM();
	//						SoundManager::GetInst()->PlayBGSound(EBGSound::EStage1Sound);
	//					}
	//					else if(_stageNow >= 5)
	//					{
	//						SoundManager::GetInst()->RemoveAllBGM();
	//						SoundManager::GetInst()->PlayBGSound(EBGSound::EStage2Sound);
	//					}
	//				}
	//			}
	//		}
	//#pragma endregion Simon Death Reponse
	//		//-------Giet boss, qua man-------------
	//#pragma region
	//		if(simon->_eatMagicalCrystal)
	//		{
	//			if(simon->GetHPSimon() < 40)
	//			{
	//				simon->hp++;
	//			}
	//			else if(_gameScore->getTimer() > 0)
	//			{
	//				_gameScore->SetTimer(-1000);
	//				_score += 50;
	//				SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_GetScoreTimer);
	//			}
	//			else if(simon->hearts > 0)
	//			{
	//				simon->hearts--;				
	//				_score += 100;
	//				SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_GetScoreWeaponCount);
	//			}
	//			else if(_levelNow == 2)
	//			{
	//				_levelNow++;
	//				_stageNow++;
	//				LoadResources(G_Device);
	//				simon->_eatMagicalCrystal = false;
	//			}
	//			else if(_levelNow == 3)
	//			{
	//				simon->_eatMagicalCrystal = false;
	//				sceneState = ESceneState::EndGame_Scene;
	//			}
	//		}
	//#pragma endregion Giet Boss, qua level
	//		//--------------Over time-------------------
	//		if(_gameScore->getTimer() <= 0)
	//			sceneState = ESceneState::Menu_Scene;
	//		//------------------------------
	//		if(stateGame == EState::None_State)
	//		{
	//			if(simon->GetUsingWatch())
	//			{
	//				qGameObject->PauseUpdate();
	//				simon->SetUsingWatch(false);
	//			}
	//			qGameObject->Update(deltaTime);
	//			bg->GetTreeObject(camera->viewport.x, camera->viewport.y);
	//			simon->Update(deltaTime);
	//			_score += simon->point;
	//			simon->point = 0;		
	//			if(_stageNow == 4)
	//			{
	//				/*_phantomBat->Update(deltaTime,simon->getPos());
	//				if(_phantomBat->type == ObjectType::Enemy_Type)
	//				{
	//					camera->SetSizeMap(G_MaxSize, G_MinSize);
	//				}*/
	//				/*_gameScore->updateScore(_stageNow, _score, deltaTime, (int)((simon->hp + 1)/2), _lifes, simon->_weaponID, simon->hearts, _phantomBat->hp);	*/	
	//			}
	//			else if(_stageNow == 10)
	//			{
	//				_queenMedusa->Update(deltaTime,simon->getPos());		
	//				_gameScore->updateScore(_stageNow, _score, deltaTime, (int)((simon->hp + 1)/2), _lifes, simon->_weaponID, simon->hearts, _queenMedusa->hp);		
	//				/*if(_phantomBat->type == ObjectType::Enemy_Type)
	//				{
	//					camera->SetSizeMap(G_MaxSize, G_MinSize);
	//				}*/
	//			}
	//			else 
	//				_gameScore->updateScore(_stageNow, _score, deltaTime, (int)((simon->hp + 1)/2), _lifes, simon->_weaponID, simon->hearts);		
	//
	//
	//			simon->Collision(*(qGameObject->_staticObject), deltaTime);
	//			simon->Collision(*(qGameObject->_dynamicObject), deltaTime);
	//			if(simon->GetUsingCross())
	//			{
	//				_score += qGameObject->RemoveAllObjectInCamera(camera->viewport);
	//				simon->SetUsingCross(false);
	//
	//				// Background
	//				d3ddv->StretchRect(
	//					BackgroundWhite,			// from 
	//					NULL,				// which portion?
	//					G_BackBuffer,		// to 
	//					NULL,				// which portion?
	//					D3DTEXF_NONE);
	//			}
	//			else
	//			{			
	//				// Background
	//				d3ddv->StretchRect(
	//					Background,			// from 
	//					NULL,				// which portion?
	//					G_BackBuffer,		// to 
	//					NULL,				// which portion?
	//					D3DTEXF_NONE);
	//			}
	//			qGameObject->Collision(deltaTime);
	//		}
	//
	//		G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//
	//		bg->Draw(camera);
	//		qGameObject->Draw(camera);
	//		openDoor->Draw(camera, _doorDirect);
	//
	//		_gameScore->drawTable();
	//
	//		simon->Draw(camera);
	//
	//		G_SpriteHandler->End();
	//		_gameScore->drawScore();
	//	}
	//#pragma endregion Camera Update Binh thuong
	//Background
	if (simon->GetUsingCross())
					{
						_score += qGameObject->RemoveAllObjectInCamera(camera->viewport);
						simon->SetUsingCross(false);
					}
	d3ddv->StretchRect(
		Background,			// from 
		NULL,				// which portion?
		G_BackBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	
						

	
	simon->Update(deltaTime);
	_score += simon->point;
	simon->point = 0;
	simon->Collision(*(qGameObject->_staticObject), deltaTime);
	simon->Collision(*(qGameObject->_dynamicObject), deltaTime);
	qGameObject->Update(deltaTime);
	qGameObject->Collision(deltaTime);
	if (_queenMedusa->_hasGetUp)
	{
		_queenMedusa->Update(deltaTime, simon->getPos());
		_gameScore->updateScore(_stageNow, _score, deltaTime, (int)((simon->hp + 1) / 2), _lifes, simon->_weaponID, simon->hearts, _queenMedusa->hp);
	}
	else
	_gameScore->updateScore(_stageNow, _score, deltaTime, (int)((simon->hp + 1) / 2), _lifes, simon->_weaponID, simon->hearts);
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	bg->Draw(camera);

	qGameObject->Draw(camera);
	openDoor->Draw(camera, _doorDirect);
	_gameScore->drawTable();
	simon->Draw(camera);

	_gameScore->drawTable();
	G_SpriteHandler->End();
	_gameScore->drawScore();

	
	
}

void SceneGame::ProcessInput(int keyCode)
{
	switch(keyCode)
	{
	case DIK_RIGHT:
	case DIK_D:
	simon->TurnRight();
	break;
	case DIK_LEFT:
	case DIK_A:
	simon->TurnLeft();
	break;
	case DIK_DOWN:
	case DIK_S:
	if(simon->OnStair())
	{
	simon->DownStair();
	}
	else
	simon->Sit();
	break;
	case DIK_UP:
	case DIK_W:
	simon->UpStair();
	break;
	case DIK_Q:
	simon->UseWeapon();
	break;
	default:
	simon->Stop();
	break;
	}
}

void SceneGame::ResetLevel()
{
	/*if(simon != NULL)
		delete simon;*/
	if(bg != NULL)
		delete bg;
	if(qGameObject != NULL)
		delete qGameObject;
}

void SceneGame::ChangeCamera(EDirectDoor _directDoor)
{
	if(_directDoor != EDirectDoor::NoneDoor)
	{
		switch (_directDoor)
		{
		case DoorDown:
			{
				camera->viewport.y  -= (32*12); //do cao 1 stage = 32pixcel * 12 dong
				simon->posY -= 64;
				simon->SetDirectDoor(EDirectDoor::NoneDoor);
				
				break;
			}
			
		case DoorUp:
			{
				camera->viewport.y += (32*12); //do cao 1 stage = 32pixcel * 12 dong
				simon->posY += 64;
				simon->SetDirectDoor(EDirectDoor::NoneDoor);
				
				break;

			}
			
		case DoorLeft:
			{
				_stateCamera = EStateCamera::NoUpdate_Camera;
				_beginMoveCamera = true;
				_moveCameraHaft = false;
				_moveCameraDone = false;
				_rangeMoveCamera = -182;
				_rangeMoveCamera2 = -110;
				_rangeMoveSimon = -60;
				_doorDirect = -1;
				
				break;
			}
			
		case DoorRight:
			{
				_stateCamera = EStateCamera::NoUpdate_Camera;
				_beginMoveCamera = true;
				_moveCameraHaft = false;
				_moveCameraDone = false;
				_rangeMoveCamera = 182;
				_rangeMoveCamera2 = 176;
				_rangeMoveSimon = 60;
				_doorDirect = 1;
				
				break;
			}
			
		default:
			break;
		}
	}

}

void SceneGame::MoveCamera(int &_moveRange)
{
	//if(_rangeMoveCamera == 0)
	//	_rangeMoveCamera = _moveRange;
	if(_beginMoveCamera)
	{
		if(_rangeMoveCamera == 0 && !_moveCameraHaft)
		{
			_moveCameraHaft = true;
			_beginMoveCamera = false;
			return;
		}
		if(_rangeMoveCamera > 0)
		{
			_rangeMoveCamera -= 2;
			camera->viewport.x += 2;
		}
		else
		{
			_rangeMoveCamera += 2;
			camera->viewport.x -=2;
		}
	}
	else if(_moveCameraHaft)
	{
		if(_rangeMoveCamera2 == 0 && !_moveCameraDone)
		{
			_moveCameraHaft = false;
			_beginMoveCamera = false;
			_moveCameraDone = true;
			_stageNow++;
			LoadStage(_stageNow);
			_stateCamera = EStateCamera::Update_Camera;
			simon->SetDirectDoor(EDirectDoor::NoneDoor);
			openDoor->ResetDoor();
			//---------Luu vi tri stage moi de hoi sinh -----------------
			_stageReset = _stageNow;
			posStageToReset.x = simon->posX;
			posStageToReset.y = simon->posY;
			posCamera = camera->viewport;
			//-----------------------------
			return;
		}
		if(_rangeMoveCamera2 > 0)
		{
			_rangeMoveCamera2 -= 2;
			camera->viewport.x += 2;
		}
		else
		{
			_rangeMoveCamera2 += 2;
			camera->viewport.x -=2;
		}
	}

}

void SceneGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	Background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	BackgroundWhite = CreateSurfaceFromFile(d3ddv, BACKGROUND_WHITE_FILE);

	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	if (_levelNow != 0 && _stageNow != 0)
	{
		LoadLevel(_levelNow);
		LoadStage(_stageNow);
	}
	else
	{
	simon = new Simon(50, 50);
	///*introScene = new IntroGame();*/
	}
}

void SceneGame::OnKeyDown(int KeyCode)
{
	if(stateGame == EState::NoUpdate_State)
	{
	if(KeyCode == DIK_R)
	stateGame = EState::None_State;
	}
	else
	{
	switch (KeyCode)
	{
	case DIK_SPACE:
	simon->Jump();
	break;
	case DIK_RETURN:
	simon->Fight();
	break;
	case DIK_U:
	simon->UpgradeMorningStar();
	break;
	case DIK_X:
	simon->ChangeWeapon(EnumID::None_ID);
	break;
	case DIK_C:
	simon->ChangeWeapon(EnumID::Watch_ID);
	break;
	case DIK_V:
	simon->ChangeWeapon(EnumID::Dagger_ID);
	break;
	case DIK_B:
	simon->ChangeWeapon(EnumID::Boomerang_ID);
	break;
	case DIK_N:
	simon->ChangeWeapon(EnumID::FireBomb_ID);
	break;
	case DIK_M:
	simon->ChangeWeapon(EnumID::Axe_ID);
	break;
	case DIK_P:
	stateGame = EState::NoUpdate_State;
	break;
	case DIK_F1:
	simon->SetUsingCross(true);
	break;
	}
	}
}

SceneGame::~SceneGame(void)
{
	if (camera != NULL)
		delete camera;
}
