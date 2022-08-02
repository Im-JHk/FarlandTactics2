#include "Stdafx.h"
#include "MapToolScene.h"
#include "MapData.h"
#include "Tile.h"
#include "Button.h"
#include "Player.h"
#include "Enemy.h"

HRESULT MapToolScene::init()
{
	mcMapdata = new MapData;
	mcCurrMap = new Map;

	msBuffer = "";

	meObject = eMapObject::TILE_1;
	miObjectNum = 0;
	miObjectNumMax = 8;

	miStage = 0;
	miRow = 10;
	miCol = 10;
	mtStart.x = TileWidth * miRow;
	mtStart.y = TileHeight * 2;

	Button* button = new Button;
	button->init("floor_up", "¡ã", "button", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X - ButtonWidth * 0.5, ButtonHeight), PointMake(ButtonWidth, ButtonHeight));
	button->RegistVoidFuncAsVoid("floor_up", std::bind(&MapToolScene::TileFloorUp, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mvButton.push_back(button);

	button = new Button;
	button->init("floor_down", "¡å", "button", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X - ButtonWidth * 0.5, ButtonHeight * 2), PointMake(ButtonWidth, ButtonHeight));
	button->RegistVoidFuncAsVoid("floor_down", std::bind(&MapToolScene::TileFloorDown, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mvButton.push_back(button);

	button = new Button;
	button->init("object_previous", "¡ã", "button", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X - ButtonWidth * 0.5, ButtonHeight * 4), PointMake(ButtonWidth, ButtonHeight));
	button->RegistVoidFuncAsVoid("object_previous", std::bind(&MapToolScene::ObjectPrevious, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mvButton.push_back(button);

	button = new Button;
	button->init("object_next", "¡å", "button", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X - ButtonWidth * 0.5, ButtonHeight * 7), PointMake(ButtonWidth, ButtonHeight));
	button->RegistVoidFuncAsVoid("object_next", std::bind(&MapToolScene::ObjectNext, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mvButton.push_back(button);

	button = new Button;
	button->init("editbox_row", "", "button_small", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X - ButtonSmallWidth * 1.5, WINSIZE_Y - ButtonSmallHeight * 3), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("editbox_row", std::bind(&MapToolScene::EnableEditRow, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mvButton.push_back(button);

	button = new Button;
	button->init("editbox_column", "", "button_small", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X - ButtonSmallWidth * 0.5, WINSIZE_Y - ButtonSmallHeight * 3), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("editbox_column", std::bind(&MapToolScene::EnableEditCol, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mvButton.push_back(button);

	button = new Button;
	button->init("editbox_submit", "Submit", "button_small", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X - ButtonSmallWidth * 1.5, WINSIZE_Y - ButtonSmallHeight * 2), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("editbox_submit", std::bind(&MapToolScene::SubmitEdit, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mvButton.push_back(button);

	button = new Button;
	button->init("editbox_clear", "Clear", "button_small", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X - ButtonSmallWidth * 0.5, WINSIZE_Y - ButtonSmallHeight * 2), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("editbox_clear", std::bind(&MapToolScene::ClearEditBox, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mvButton.push_back(button);

	mtObjViewRc = RectMake(WINSIZE_X - 100, ButtonHeight * 4.5, 100, 100);

	for (int i = 0; i < miCol; i++) {
		for (int j = 0; j < miRow; j++) {
			Tile* tile = new Tile;
			tile->init(PointMake(miRow, miCol), j, i);
			tile->SetEnable(true);
			tile->SetVisible(true);
			tile->RegistVoidFuncAsInt("over", std::bind(&MapToolScene::OnTheTile, this, std::placeholders::_1));
			tile->RegistVoidFuncAsInt("tile", std::bind(&MapToolScene::SelectTile, this, std::placeholders::_1));
			mvTile.push_back(tile);
		}
	}
	MOUSEMANAGER->AddVecButton(mvButton);
	MOUSEMANAGER->AddVecTile(mvTile);

	mbIsMoveTile = false;

	EVENTMANAGER->SetSelectable(eSelectableType::BUTTON);
	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);

	return S_OK;
}

void MapToolScene::release()
{
	for (int i = 0; i < mvButton.size(); i++) {
		SAFE_DELETE(mvButton[i]);
	}
	for (int i = 0; i < mvTile.size(); i++) {
		SAFE_DELETE(mvTile[i]);
	}
	for (int i = 0; i < mvPlayer.size(); i++) {
		SAFE_DELETE(mvPlayer[i]);
	}
	for (int i = 0; i < mvEnemy.size(); i++) {
		SAFE_DELETE(mvEnemy[i]);
	}
	mvButton.clear();
	mvTile.clear();
	mvPlayer.clear();
	mvEnemy.clear();
	mcMapdata->Release();
	SAFE_DELETE(mcMapdata);
	mcCurrMap->Release();
	SAFE_DELETE(mcCurrMap);
	MOUSEMANAGER->release();
}

void MapToolScene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_CONTROL)) {
		if (KEYMANAGER->isStayKeyDown('A')) {
			if (KEYMANAGER->isOnceKeyDown(0x30)) {
				SetAllOfTile(0);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('S')) {
		SaveTheMapInfo();
	}
	if (KEYMANAGER->isOnceKeyDown('L')) {
		LoadTheMapInfo();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
		this->release();
		MOUSEMANAGER->release();
		SCENEMANAGER->changeScene("Select");
	}

	mtCameraRect = CAMERAMANAGER->GetCameraRect();
}

void MapToolScene::render()
{
	IMAGEMANAGER->render("bg_white", getMemDC());
	
	for (auto iter : mvTile) {
		if ((*iter).GetType() == eObjectType::TILE) {
			DrawIsometric(getMemDC(), CAMERAMANAGER->ReviseRelativePosition((*iter).GetIsometric()));
		}
		for (int i = 0; i <= (*iter).GetFloorLevel(); i++) {
			IMAGEMANAGER->frameRender("floor", getMemDC(), (*iter).GetFloorRect().left - mtCameraRect.left, (*iter).GetFloorRect().top + i * FloorHeight - mtCameraRect.top, (*iter).GetFloorFrameX(), 0);
		}
		if ((*iter).GetTileFrameX() != -1) {
			IMAGEMANAGER->frameRender("tile", getMemDC(), (*iter).GetTileRect().left - mtCameraRect.left, (*iter).GetFloorRect().top - FloorHeight - mtCameraRect.top, (*iter).GetTileFrameX(), 0);
		}
	}
	
	IMAGEMANAGER->frameRender("tile_select", getMemDC(), mvTile[miTileIndex]->GetTileRect().left - mtCameraRect.left, mvTile[miTileIndex]->GetTileRect().top - mtCameraRect.top, 0, 0);

	for (auto iter : mvPlayer) {
		IMAGEMANAGER->frameRender((*iter).GetName() + "_idle", getMemDC(), (*iter).GetCenter().x - mtCameraRect.left - 50, (*iter).GetCenter().y - mtCameraRect.top - 80, 0, static_cast<int>((*iter).GetDirection()));
	}
	for (auto iter : mvEnemy) {
		IMAGEMANAGER->frameRender((*iter).GetName() + "_idle", getMemDC(), (*iter).GetCenter().x - mtCameraRect.left - 50, (*iter).GetCenter().y - mtCameraRect.top - 80, 0, static_cast<int>((*iter).GetDirection()));
	}

	IMAGEMANAGER->render("bg_side", getMemDC(), WINSIZE_X - 100, 0);
	for (int i = 0; i < mvButton.size(); i++) {
		Rectangle(getMemDC(), mvButton[i]->GetRect().left, mvButton[i]->GetRect().top, mvButton[i]->GetRect().right, mvButton[i]->GetRect().bottom);
		mvButton[i]->render();
	}
	switch (static_cast<eMapObject>(miObjectNum))
	{
	case eMapObject::TILE_1:
		IMAGEMANAGER->frameRender("tile", getMemDC(), mtObjViewRc.left + 16, mtObjViewRc.top + 32, 0, 0);
		break;
	case eMapObject::TILE_2:
		IMAGEMANAGER->frameRender("tile", getMemDC(), mtObjViewRc.left + 16, mtObjViewRc.top + 32, 1, 0);
		break;
	case eMapObject::TILE_3:
		IMAGEMANAGER->frameRender("tile", getMemDC(), mtObjViewRc.left + 16, mtObjViewRc.top + 32, 2, 0);
		break;
	case eMapObject::TILE_4:
		IMAGEMANAGER->frameRender("tile", getMemDC(), mtObjViewRc.left + 16, mtObjViewRc.top + 32, 3, 0);
		break;
	case eMapObject::TILE_5:
		IMAGEMANAGER->frameRender("tile", getMemDC(), mtObjViewRc.left + 16, mtObjViewRc.top + 32, 4, 0);
		break;
	case eMapObject::TILE_6:
		IMAGEMANAGER->frameRender("tile", getMemDC(), mtObjViewRc.left + 16, mtObjViewRc.top + 32, 5, 0);
		break;
	case eMapObject::KARIN:
		IMAGEMANAGER->frameRender("karin_idle", getMemDC(), mtObjViewRc.left, mtObjViewRc.top, 0, 3);
		break;
	case eMapObject::AL:
		IMAGEMANAGER->frameRender("al_idle", getMemDC(), mtObjViewRc.left, mtObjViewRc.top, 0, 3);
		break;
	case eMapObject::ROGUE_1:
		IMAGEMANAGER->frameRender("rogue1_idle", getMemDC(), mtObjViewRc.left, mtObjViewRc.top, 0, 3);
		break;
	}
}

void MapToolScene::SetAllOfTile(int num)
{
	for (auto& iter : mvTile) {
		iter->SetTileFrameX(num);
		iter->SetFloorLevel(num);
		switch (miObjectNum)
		{
		case 0:
			iter->SetFloorFrameX(0);
			break;
		case 1:
			iter->SetFloorFrameX(1);
			break;
		case 2: case 3: case 4: case 5:
			iter->SetFloorFrameX(2);
			break;
		}
	}
}

void MapToolScene::SaveTheMapInfo(void)
{
	mcMapdata->SaveMapData(mvTile, mvPlayer, mvEnemy, miRow, miCol, 1);
}

void MapToolScene::LoadTheMapInfo(void)
{
	mcMapdata->LoadMapData(mvTile, mvPlayer, mvEnemy, miRow, miCol, miStage);
	mcCurrMap = mcMapdata->GetMap(0);
	mvTile = mcCurrMap->GetVecTile();
	mvPlayer = mcCurrMap->GetVecPlayer();
	mvEnemy = mcCurrMap->GetVecEnemy();
}

void MapToolScene::TileFloorUp(void)
{
	mvTile[miPickTileIndex]->SetFloorLevel(mvTile[miPickTileIndex]->GetFloorLevel() + 1);
	mvTile[miPickTileIndex]->SetFloorRect(RectMake(
		mvTile[miPickTileIndex]->GetCenter().x - TileWidth / 2,
		mvTile[miPickTileIndex]->GetCenter().y - mvTile[miPickTileIndex]->GetFloorLevel() * FloorHeight,
		TileWidth, mvTile[miPickTileIndex]->GetFloorLevel() * FloorHeight
	));
	mvTile[miPickTileIndex]->SetIsometric(MakeIsometric(
		PointMake(mvTile[miPickTileIndex]->GetCenter().x, mvTile[miPickTileIndex]->GetFloorRect().top),
		mvTile[miPickTileIndex]->GetSize()
	));
}

void MapToolScene::TileFloorDown(void)
{
	mvTile[miPickTileIndex]->SetFloorLevel(mvTile[miPickTileIndex]->GetFloorLevel() - 1);
	mvTile[miPickTileIndex]->SetFloorRect(RectMake(
		mvTile[miPickTileIndex]->GetCenter().x - TileWidth / 2,
		mvTile[miPickTileIndex]->GetCenter().y - mvTile[miPickTileIndex]->GetFloorLevel() * FloorHeight,
		TileWidth, mvTile[miPickTileIndex]->GetFloorLevel() * FloorHeight
	));
	mvTile[miPickTileIndex]->SetIsometric(MakeIsometric(
		PointMake(mvTile[miPickTileIndex]->GetCenter().x, mvTile[miPickTileIndex]->GetFloorRect().top),
		mvTile[miPickTileIndex]->GetSize()
	));
}

void MapToolScene::ObjectPrevious(void)
{
	miObjectNum -= 1;
	if (miObjectNum < 0) {
		miObjectNum = miObjectNumMax;
	}
	cout << miObjectNum << endl;
}

void MapToolScene::ObjectNext(void)
{
	miObjectNum += 1;
	if (miObjectNum > miObjectNumMax) {
		miObjectNum = 0;;
	}
	cout << miObjectNum << endl;
}

void MapToolScene::EnableEditRow(void)
{
	cout << "EnableEditRow" << endl;
}

void MapToolScene::EnableEditCol(void)
{
	cout << "EnableEditCol" << endl;
}

void MapToolScene::SubmitEdit()
{
	cout << "SubmitEdit" << endl;
}

void MapToolScene::ClearEditBox()
{
	cout << "ClearEditBox" << endl;
}

void MapToolScene::SelectTile(int index)
{
	miPickTileIndex = index;
	if (miObjectNum >= 0 && miObjectNum <= 5) {
		mvTile[index]->SetTileFrameX(miObjectNum);
		switch (miObjectNum) 
		{
		case 0:
			mvTile[index]->SetFloorFrameX(0);
			break;
		case 1:
			mvTile[index]->SetFloorFrameX(1);
			break;
		case 2: case 3: case 4: case 5:
			mvTile[index]->SetFloorFrameX(2);
			break;
		}
	}
	else if(miObjectNum == 6) {
		Player* player = new Player;
		player->init("karin", eDirection::LEFT, mvTile[index]->GetCenter(), PointMake(mvTile[index]->GetRow(), mvTile[index]->GetCol()), index);
		mvPlayer.push_back(player);
		mvTile[index]->SetType(eObjectType::PLAYER);
	}
	else if (miObjectNum == 7) {
		Player* player = new Player;
		player->init("al", eDirection::LEFT, mvTile[index]->GetCenter(), PointMake(mvTile[index]->GetRow(), mvTile[index]->GetCol()), index);
		mvPlayer.push_back(player);
		mvTile[index]->SetType(eObjectType::PLAYER);
	}
	else if (miObjectNum == 8) {
		Enemy* enemy = new Enemy;
		enemy->init("rogue1", eDirection::RIGHT, mvTile[index]->GetCenter(), PointMake(mvTile[index]->GetRow(), mvTile[index]->GetCol()), index);
		mvEnemy.push_back(enemy);
		mvTile[index]->SetType(eObjectType::ENEMY);
	}
}

void MapToolScene::OnTheTile(int index)
{
	miTileIndex = index;
}
