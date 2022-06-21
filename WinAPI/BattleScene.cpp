#include "Stdafx.h"
#include "BattleScene.h"
#include "MapData.h"
#include "AStar.h"
#include "Range.h"
#include "Tile.h"
#include "Button.h"
#include "Player.h"
#include "Enemy.h"

HRESULT BattleScene::init()
{	
	mcMapdata = new MapData;
	mcCurrMap = new Map;

	meCurrObj = eObjectType::TILE;

	miStage = 0;
	miRow = 10;
	miCol = 10;

	miTurnCount = 1;
	miCurrTile = -1;

	miEnemyBehaviorCount = 0;

	mbIsAddPlayer = false;
	mbIsAddEnemy = false;
	mbPlayerExist = false;
	mbIsPlayerTurn = true;
	mbIsGameOver = false;
	mbIsGameEnd = false;

	mbIsMoveTile = false;

	mbIsPathOn = false;
	mbIsMoveOn = false;
	mbIsStartMove = false;

	mbIsAttackRangeOn = false;
	mbIsAttackHitRangeOn = false;
	mbIsSpellRangeOn = false;
	mbIsSpellHitRangeOn = false;

	//for (int i = 0; i < miCol; i++) {
	//	for (int j = 0; j < miRow; j++) {
	//		Tile* tile = new Tile;
	//		tile->init(PointMake(miRow, miCol), j, i);
	//		tile->SetEnable(true);
	//		tile->SetVisible(true);
	//		tile->RegistVoidFuncAsInt("over", std::bind(&BattleScene::ShowInfomation, this, std::placeholders::_1));
	//		tile->RegistVoidFuncAsInt("unit", std::bind(&BattleScene::SelectUnit, this, std::placeholders::_1));
	//		tile->RegistVoidFuncAsInt("move", std::bind(&BattleScene::SelectMoveTile, this, std::placeholders::_1));
	//		tile->RegistVoidFuncAsInt("attack_type", std::bind(&BattleScene::SelectAttackType, this, std::placeholders::_1));
	//		tile->RegistVoidFuncAsInt("attack", std::bind(&BattleScene::SelectAttackTile, this, std::placeholders::_1));
	//		tile->RegistVoidFuncAsInt("spell", std::bind(&BattleScene::SelectSpellTile, this, std::placeholders::_1));
	//		mvTile.push_back(tile);
	//	}
	//}
	LoadTheMapInfo();

	mcAStar = new AStar;
	mcAStar->init(mvTile, miRow, miCol);
	mcRange = new Range;
	mcRange->init(mvTile, miRow, miCol);

	Button* button = new Button;
	button->init("attack_button", "공격 r", "button_small", eButtonShapeType::RECTANGLE, PointMake(0, 0), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("attack_button", std::bind(&BattleScene::AttackButton, this));
	mvBTN.push_back(button);

	button = new Button;
	button->init("select_attack", "공격", "button_small", eButtonShapeType::RECTANGLE, PointMake(0, 0), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("select_attack", std::bind(&BattleScene::ShowAttackRange, this));
	mvBTN.push_back(button);

	button = new Button;
	button->init("attack_okay", "공격 시전", "button_small", eButtonShapeType::RECTANGLE, PointMake(0, 0), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("attack_okay", std::bind(&BattleScene::DoAttackPlayer, this));
	mvBTN.push_back(button);

	button = new Button;
	button->init("spell_button", "주문 r", "button_small", eButtonShapeType::RECTANGLE, PointMake(0, 0), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("spell_button", std::bind(&BattleScene::SpellButton, this));
	mvBTN.push_back(button);

	button = new Button;
	button->init("select_spell", "주문", "button_small", eButtonShapeType::RECTANGLE, PointMake(0, 0), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("select_spell", std::bind(&BattleScene::ShowSpellRange, this));
	mvBTN.push_back(button);

	button = new Button;
	button->init("spell_okay", "주문 시전", "button_small", eButtonShapeType::RECTANGLE, PointMake(0, 0), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("spell_okay", std::bind(&BattleScene::DoSpellPlayer, this));
	mvBTN.push_back(button);

	button = new Button;
	button->init("cancel", "취소", "button_small", eButtonShapeType::RECTANGLE, PointMake(0, 0), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("cancel", std::bind(&BattleScene::CancelButton, this));
	mvBTN.push_back(button);

	button = new Button;
	button->init("end_of_turn", "턴 종료", "button_small", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X / 2, WINSIZE_Y / 2), PointMake(ButtonSmallWidth, ButtonSmallHeight));
	button->RegistVoidFuncAsVoid("end_of_turn", std::bind(&BattleScene::EndOfTurn, this));
	mvBTN.push_back(button);

	MOUSEMANAGER->AddVecButton(mvBTN);
	MOUSEMANAGER->AddVecTile(mvTile);

	EFFECTMANAGER->RegistVoidFuncAs4Int(std::bind(&BattleScene::EffectIsStart, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	EFFECTMANAGER->RegistVoidFuncAs2Int(std::bind(&BattleScene::EffectIsEnd, this, std::placeholders::_1, std::placeholders::_2));

	PLAYERMANAGER->SetAStar(mcAStar);
	PLAYERMANAGER->SetRange(mcRange);
	PLAYERMANAGER->SetVecTile(mvTile);
	PLAYERMANAGER->SetRowColMax(PointMake(miRow, miCol));

	EVENTMANAGER->SetPhase(eSelectPhase::UNIT_SELECT);
	EVENTMANAGER->SetSelectable(eSelectableType::TILE);

	return S_OK;
}

void BattleScene::release()
{
	for (int i = 0; i < mvTile.size(); i++) {
		SAFE_DELETE(mvTile[i]);
	}
	for (int i = 0; i < mvBTN.size(); i++) {
		SAFE_DELETE(mvBTN[i]);
	}
	PLAYERMANAGER->release();
	MOUSEMANAGER->release();
	mcAStar->release();
	SAFE_DELETE(mcAStar);
	SAFE_DELETE(mcRange);
	mcMapdata->Release();
	SAFE_DELETE(mcMapdata);
	//mcCurrMap->Release();
	//SAFE_DELETE(mcCurrMap);
}

void BattleScene::update()
{

	if (mbIsGameOver) {
		this->release();
		SCENEMANAGER->changeScene("GameOver");
	}
	else {
		if (PLAYERMANAGER->IsPlayerAllDie()) mbIsGameOver = true;
	}
	if (mbIsGameEnd) {
		this->release();
		SCENEMANAGER->changeScene("Ending");
	}
	else {
		if (PLAYERMANAGER->IsEnemyAllDie()) mbIsGameEnd = true;
	}

	if (!mbIsGameEnd && !mbIsGameOver) {
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
			CancelButton();
		}
		if (!EFFECTMANAGER->GetIsEffectOn()) {
			if (mbIsPathOn) {
				MoveCharacter(meCurrObj);
			}
			if (mbIsPlayerTurn) {
				if (KEYMANAGER->isOnceKeyDown(VK_F10)) {
					TurnButton();
				}
			}
			else {
				if (!PLAYERMANAGER->GetLockOn()) {
					if (PLAYERMANAGER->AutoEnemyBehavior(miEnemyBehaviorCount)) {
						PLAYERMANAGER->SetPlayerAllCanMoveAndAttack(true);
						ClearPhase();
						mbIsPlayerTurn = true;
					}
					else {
						switch (PLAYERMANAGER->GetEnemyState())
						{
						case eState::MOVE:
							meCurrObj = eObjectType::ENEMY;
							mqPath = mcAStar->GetPath();
							mcAStar->ClearPath();
							mbIsPathOn = true;
							break;
						case eState::ATTACK:
							break;
						case eState::IDLE:
							PLAYERMANAGER->SetLockOn(false);
							miEnemyBehaviorCount++;
							break;
						}
					}
				}
			}
		}

		PLAYERMANAGER->update();
		EFFECTMANAGER->update();

		if (PLAYERMANAGER->GetLockOn()) {
			if (mbIsPlayerTurn) CAMERAMANAGER->SetFocus(PLAYERMANAGER->GetPlayer(), true);
			else CAMERAMANAGER->SetFocus(PLAYERMANAGER->GetEnemy(), true);
		}

		mtCameraRect = CAMERAMANAGER->GetCameraRect();
	}
}

void BattleScene::render()
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

	if (mbIsSpellRangeOn && !mbIsSpellHitRangeOn) {
		for (auto iter : msSpellRange) {
			IMAGEMANAGER->frameRender("tile_select", getMemDC(), mvTile[iter]->GetTileRect().left - mtCameraRect.left , mvTile[iter]->GetTileRect().top - mtCameraRect.top, 1, 1);
		}
	}
	if (mbIsSpellHitRangeOn) {
		for (auto iter : msSpellHitRange) {
			IMAGEMANAGER->frameRender("tile_select", getMemDC(), mvTile[iter]->GetTileRect().left - mtCameraRect.left, mvTile[iter]->GetTileRect().top - mtCameraRect.top, 1, 1);
		}
	}
	for (auto iter : msMoveRange) {
		IMAGEMANAGER->render("system", getMemDC(), mvTile[iter]->GetTileRect().left - mtCameraRect.left, mvTile[iter]->GetTileRect().top - mtCameraRect.top, 224, 0, 64, 32);
	}
	for (auto iter : msAttackRange) {
		IMAGEMANAGER->render("system", getMemDC(), mvTile[iter]->GetTileRect().left - mtCameraRect.left, mvTile[iter]->GetTileRect().top - mtCameraRect.top, 224, 32, 64, 32);
	}
	IMAGEMANAGER->frameRender("tile_select", getMemDC(), mvTile[miTileIndex]->GetTileRect().left - mtCameraRect.left, mvTile[miTileIndex]->GetTileRect().top - mtCameraRect.top, 0, 0);
	
	PLAYERMANAGER->render(mtCameraRect);
	EFFECTMANAGER->render(mtCameraRect);
	
	for (auto iter : mvBTN) {
		iter->render();
	}
}

void BattleScene::LoadTheMapInfo()
{
	mcMapdata->LoadMapData(mvTile, mvPlayer, mvEnemy, miRow, miCol, miStage);
	mcCurrMap = mcMapdata->GetMap(0);
	mvTile = mcCurrMap->GetVecTile();
	mvPlayer = mcCurrMap->GetVecPlayer();
	mvEnemy = mcCurrMap->GetVecEnemy();
	for (auto iter : mvTile) {
		(*iter).SetEnable(true);
		(*iter).SetVisible(true);
		(*iter).RegistVoidFuncAsInt("over", std::bind(&BattleScene::ShowInfomation, this, std::placeholders::_1));
		(*iter).RegistVoidFuncAsInt("unit", std::bind(&BattleScene::SelectUnit, this, std::placeholders::_1));
		(*iter).RegistVoidFuncAsInt("move", std::bind(&BattleScene::SelectMoveTile, this, std::placeholders::_1));
		(*iter).RegistVoidFuncAsInt("attack_type", std::bind(&BattleScene::SelectAttackType, this, std::placeholders::_1));
		(*iter).RegistVoidFuncAsInt("attack", std::bind(&BattleScene::SelectAttackTile, this, std::placeholders::_1));
		(*iter).RegistVoidFuncAsInt("spell", std::bind(&BattleScene::SelectSpellTile, this, std::placeholders::_1));
	}
	PLAYERMANAGER->AddAllPlayer(mcCurrMap->GetVecPlayer());
	PLAYERMANAGER->AddAllEnemy(mcCurrMap->GetVecEnemy());
}

bool BattleScene::OnTheTile(eMouseEventType type)
{
	//for (int i = 0; i < mvTile.size(); i++) {
	//	ISOMETRIC iso = MoveIsometric(mvTile[i]->GetIsometric(), mtCameraRect);
	//	HRGN hRgn = CreatePolygonRgn(iso.point, 4, ALTERNATE);
	//	if (PtInRegion(hRgn, _ptMouse.x, _ptMouse.y)) {
	//		miTileIndex = i;
	//		if (type == eMouseEventType::UP) {
	//			miPickTileIndex = i;
	//			if(mbIsAddPlayer && !mbIsAddEnemy){
	//				PLAYERMANAGER->AddPlayer("karin", eDirection::DOWN, mvTile[i]->GetCenter(), PointMake(mvTile[i]->GetRow(), mvTile[i]->GetCol()) , i);
	//				mvTile[i]->SetType(eObjectType::PLAYER);
	//				mbIsAddPlayer = false;
	//			}
	//			else if(mbIsAddEnemy && !mbIsAddPlayer){
	//				PLAYERMANAGER->AddEnemy("rogue1", eDirection::DOWN, mvTile[i]->GetCenter(), PointMake(mvTile[i]->GetRow(), mvTile[i]->GetCol()), i);
	//				mvTile[i]->SetType(eObjectType::ENEMY);
	//				mbIsAddEnemy = false;
	//			}
	//		}
	//		DeleteObject(hRgn);
	//		return true;
	//	}
	//	DeleteObject(hRgn);
	//}
	return false;
}

void BattleScene::StartAStar()
{
	mcAStar->Algorithm(miStart, miEnd);
	msTile = mcAStar->GetTile();
	mqPath = mcAStar->GetPath();
	mcAStar->ClearPath();
	mbIsPathOn = true;
}

void BattleScene::MoveCharacter(eObjectType type)
{
	if (type == eObjectType::PLAYER) {
		if (!mbIsStartMove) {
			PLAYERMANAGER->SetStatePlayer(eState::MOVE);
			mvTile[(*mqPath.begin())]->SetType(eObjectType::TILE);
			mbIsStartMove = true;
		}
		auto iter = mqPath.begin();
		int prevIndex = (*iter++);
		int nextIndex = (*iter);

		eDirection dir = FindDirection(prevIndex, nextIndex);
		if (PLAYERMANAGER->MovePlayer(mvTile[prevIndex], mvTile[nextIndex], dir)) {
			if (mqPath.size() > 2) mqPath.pop_front();
			else ClearMove(type, nextIndex);
		}
	}
	else if (type == eObjectType::ENEMY) {
		if (!mbIsStartMove) {
			//PLAYERMANAGER->SetStateEnemy(eState::MOVE);
			mvTile[(*mqPath.begin())]->SetType(eObjectType::TILE);
			mbIsStartMove = true;
		}
		auto iter = mqPath.begin();
		int prevIndex = (*iter++);
		int nextIndex = (*iter);

		eDirection dir = FindDirection(prevIndex, nextIndex);
		if (PLAYERMANAGER->MoveEnemy(mvTile[prevIndex], mvTile[nextIndex], dir)) {
			if (mqPath.size() > 2) mqPath.pop_front();
			else ClearMove(type, nextIndex);
		}
	}
}

eDirection BattleScene::FindDirection(int prev, int next)
{
	int sub = next - prev;

	if(sub == -1) return eDirection::LEFT;
	else if (sub == 1) return eDirection::RIGHT;
	else if (sub == -miRow) return eDirection::UP;
	else if (sub == miRow) return eDirection::DOWN;
}

void BattleScene::DoAttackPlayer(void)
{
	ClearAllButton();
	PLAYERMANAGER->AttackPlayer(miAttackHitIndex);
	PLAYERMANAGER->SetPlayerCanAttack(false);
}

void BattleScene::DoSpellPlayer()
{
	ClearAllButton();
	PLAYERMANAGER->SpellPlayer("flame_burst", msSpellHitRange);
	PLAYERMANAGER->SetPlayerCanAttack(false);
}

void BattleScene::EffectIsStart(int evType, int atkType, int rcvType, int index)
{
	eEventType eventType = static_cast<eEventType>(evType);
	eAttackType attackType = static_cast<eAttackType>(atkType);
	eObjectType receiverType = static_cast<eObjectType>(rcvType);
	
	switch (eventType)
	{
	case eEventType::NONE:
		break;
	case eEventType::ATTACK:
		if(receiverType == eObjectType::PLAYER) PLAYERMANAGER->DamageStartPlayer(attackType, index);
		else if (receiverType == eObjectType::ENEMY) PLAYERMANAGER->DamageStartEnemy(attackType, index);
		break;
	case eEventType::ATTACKED:
		break;
	case eEventType::DIE:
		break;
	}
}

void BattleScene::EffectIsEnd(int evType, int rcvType)
{
	eEventType eventType = static_cast<eEventType>(evType);
	eObjectType receiverType = static_cast<eObjectType>(rcvType);
	switch (eventType)
	{
	case eEventType::NONE:
		break;
	case eEventType::ATTACK:
		if (receiverType == eObjectType::PLAYER) {
			PLAYERMANAGER->SetStateEnemy(eState::IDLE);
			PLAYERMANAGER->DamageEndPlayer();
		}
		else if (receiverType == eObjectType::ENEMY) {
			PLAYERMANAGER->SetStatePlayer(eState::IDLE);
			PLAYERMANAGER->DamageEndEnemy();
		}
		break;
	case eEventType::ATTACKED:
		if (receiverType == eObjectType::PLAYER) {
			PLAYERMANAGER->IsDiePlayer();
			PLAYERMANAGER->SetStateAllPlayer(eState::IDLE);
			if (EFFECTMANAGER->GetEventType() != eEventType::DIE) {
				ClearPhase();
			}
		}
		else if (receiverType == eObjectType::ENEMY) {
			PLAYERMANAGER->IsDieEnemy();
			PLAYERMANAGER->SetStateAllEnemy(eState::IDLE);
			if (EFFECTMANAGER->GetEventType() != eEventType::DIE) {
				ClearPhase();
			}
		}
		break;
	case eEventType::DIE:
		ClearPhase();
		break;
	}
}

void BattleScene::ShowInfomation(int index)
{
	miTileIndex = index;
	PLAYERMANAGER->ShowInfomation(index);
}

void BattleScene::AttackButton(void)
{
	ClearAllButton();

	int count = 0;
	POINT pCenter = PLAYERMANAGER->GetPlayerCenter();
	POINT cCenter = CAMERAMANAGER->GetCameraPos();
	POINT pt = { pCenter.x - cCenter.x, pCenter.y - cCenter.y };
	for (auto& iter = mvBTN.begin(); iter != mvBTN.end(); ++iter) {
		if ((*iter)->GetKeyName() == "attack_okay") {
			(*iter)->Offset(pt);
			(*iter)->SetEnable(true);
			(*iter)->SetVisible(true);
			count++;
		}
		else if ((*iter)->GetKeyName() == "cancel") {
			(*iter)->Offset(PointMake(pt.x, (pt.y + ButtonSmallHeight)));
			(*iter)->SetEnable(true);
			(*iter)->SetVisible(true);
			count++;
		}
		if (count >= 2) break;
	}
	EVENTMANAGER->SetSelectable(eSelectableType::BUTTON);
	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);
}

void BattleScene::SpellButton(void)
{
	ClearAllButton();

	int count = 0;
	POINT pCenter = PLAYERMANAGER->GetPlayerCenter();
	POINT cCenter = CAMERAMANAGER->GetCameraPos();
	POINT pt = { pCenter.x - cCenter.x, pCenter.y - cCenter.y };
	for (auto& iter = mvBTN.begin(); iter != mvBTN.end(); ++iter) {
		if ((*iter)->GetKeyName() == "spell_okay") {
			(*iter)->Offset(pt);
			(*iter)->SetEnable(true);
			(*iter)->SetVisible(true);
			count++;
		}
		else if ((*iter)->GetKeyName() == "cancel") {
			(*iter)->Offset(PointMake(pt.x, (pt.y + ButtonSmallHeight)));
			(*iter)->SetEnable(true);
			(*iter)->SetVisible(true);
			count++;
		}
		if (count >= 2) break;
	}
	EVENTMANAGER->SetSelectable(eSelectableType::BUTTON);
	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);
}

void BattleScene::CancelButton(void)
{
	ClearAllButton();
	ClearAttack();
	ClearSpell();
	mbIsMoveOn = false;
	mbIsMoveTile = false;
	mqPath.clear();
	msMoveRange.clear();
	mcRange->SetRangeinit();
	PLAYERMANAGER->SetLockOn(false);

	EVENTMANAGER->SetSelectable(eSelectableType::TILE);
	EVENTMANAGER->SetPhase(eSelectPhase::UNIT_SELECT);
}

void BattleScene::ShowAttackRange(void)
{
	ClearAllButton();

	int index = PLAYERMANAGER->GetPlayerOnTileIndex();
	mbIsAttackRangeOn = true;
	mcRange->CalculateAttackRange(eObjectType::ENEMY, index, 1, true);
	msAttackRange = mcRange->GetRange();
	MOUSEMANAGER->SetAttackRange(msAttackRange);
	EVENTMANAGER->SetSelectable(eSelectableType::TILE);
	EVENTMANAGER->SetPhase(eSelectPhase::ATTACK_SELECT);
	mcRange->SetRangeinit();
}

void BattleScene::ShowSpellRange(void)
{
	ClearAllButton();

	int index = PLAYERMANAGER->GetPlayerOnTileIndex();
	mbIsSpellRangeOn = true;
	mcRange->CalculateAttackRange(eObjectType::ENEMY, index, 3, true);
	msSpellRange = mcRange->GetRange();
	MOUSEMANAGER->SetSpellRange(msSpellRange);
	EVENTMANAGER->SetSelectable(eSelectableType::TILE);
	EVENTMANAGER->SetPhase(eSelectPhase::SPELL_SELECT);
	mcRange->SetRangeinit();

}

void BattleScene::SelectUnit(int index)
{
	ClearAllButton();

	meCurrObj = mvTile[index]->GetType();
	if(meCurrObj == eObjectType::PLAYER) PLAYERMANAGER->LockOnPlayerIndex(index);
	else if (meCurrObj == eObjectType::ENEMY) PLAYERMANAGER->LockOnEnemyIndex(index);
	
	cout << PLAYERMANAGER->GetPlayerCanMove() << endl;
	if (PLAYERMANAGER->GetPlayerCanMove()) {
		miStart = index;
		cout << miStart << endl;
		mbIsMoveOn = true;
		mcRange->CalculateRange(index, 3);
		msMoveRange = mcRange->GetRange();
		for (auto iter : msMoveRange) {
			cout << iter << "->";
		}
		cout << endl;
		mcRange->SetRangeinit();
		MOUSEMANAGER->SetMoveRange(msMoveRange);
		EVENTMANAGER->SetPhase(eSelectPhase::MOVE_SELECT);
	}
	else if (PLAYERMANAGER->GetPlayerCanAttack()) {
		EVENTMANAGER->SetPhase(eSelectPhase::ATK_TYPE_SELECT);
		SelectAttackType(index);
	}
}

void BattleScene::SelectMoveTile(int dest)
{
	if (mbIsMoveOn) {
		miEnd = dest;
		StartAStar();
		mbIsMoveOn = false;
	}
	EVENTMANAGER->SetPhase(eSelectPhase::ATK_TYPE_SELECT);
}

void BattleScene::SelectAttackType(int index)
{
	ClearAllButton();

	int count = 0;
	POINT tCenter = mvTile[index]->GetCenter();
	POINT cCenter = CAMERAMANAGER->GetCameraPos();
	POINT pt = { tCenter.x - cCenter.x, tCenter.y - cCenter.y };
	for (auto& iter = mvBTN.begin(); iter != mvBTN.end(); ++iter) {
		if ((*iter)->GetKeyName() == "select_attack") {
			(*iter)->Offset(pt);
			if (PLAYERMANAGER->FindImmediateEnemy({ miRow, miCol }, index)) (*iter)->SetEnable(true);
			else (*iter)->SetEnable(false);
			(*iter)->SetVisible(true);
			count++;
		}
		else if ((*iter)->GetKeyName() == "select_spell") {
			(*iter)->Offset(PointMake(pt.x, (pt.y + ButtonSmallHeight)));
			(*iter)->SetEnable(true);
			(*iter)->SetVisible(true);
			count++;
		}
		else if ((*iter)->GetKeyName() == "cancel") {
			(*iter)->Offset(PointMake(pt.x, (pt.y + ButtonSmallHeight * 2)));
			(*iter)->SetEnable(true);
			(*iter)->SetVisible(true);
			count++;
		}
		if (count >= 3) break;
	}
	EVENTMANAGER->SetSelectable(eSelectableType::BUTTON);
	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);
}

void BattleScene::SelectAttackTile(int dest)
{
	ClearAllButton();

	mbIsAttackHitRangeOn = true;
	miAttackHitIndex = dest;


	int count = 0;
	POINT tCenter = mvTile[dest]->GetCenter();
	POINT cCenter = CAMERAMANAGER->GetCameraPos();
	POINT pt = { tCenter.x - cCenter.x, tCenter.y - cCenter.y };
	for (auto& iter = mvBTN.begin(); iter != mvBTN.end(); ++iter) {
		if ((*iter)->GetKeyName() == "attack_okay") {
			(*iter)->Offset(pt);
			if (PLAYERMANAGER->FindEnemy(dest)) (*iter)->SetEnable(true);
			else (*iter)->SetEnable(false);
			(*iter)->SetVisible(true);
			count++;
		}
		else if ((*iter)->GetKeyName() == "cancel") {
			(*iter)->Offset(PointMake(pt.x, (pt.y + ButtonSmallHeight)));
			(*iter)->SetEnable(true);
			(*iter)->SetVisible(true);
			count++;
		}
		if (count >= 2) break;
	}
	EVENTMANAGER->SetSelectable(eSelectableType::BUTTON);
	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);
}

void BattleScene::SelectSpellTile(int dest)
{
	ClearAllButton();
	msSpellHitRange.clear();

	mbIsSpellHitRangeOn = true;
	mcRange->CalculateAttackRange(eObjectType::ENEMY, dest, 2, false);
	msSpellHitRange = mcRange->GetRange();
	MOUSEMANAGER->SetSpellHitRange(msSpellHitRange);

	int count = 0;
	POINT tCenter = mvTile[dest]->GetCenter();
	POINT cCenter = CAMERAMANAGER->GetCameraPos();
	POINT pt = { tCenter.x - cCenter.x, tCenter.y - cCenter.y };
	for (auto& iter = mvBTN.begin(); iter != mvBTN.end(); ++iter) {
		if ((*iter)->GetKeyName() == "spell_okay") {
			(*iter)->Offset(pt);
			if (PLAYERMANAGER->FindEnemy(msSpellHitRange)) (*iter)->SetEnable(true);
			else (*iter)->SetEnable(false);
			(*iter)->SetVisible(true);
			count++;
		}
		else if ((*iter)->GetKeyName() == "cancel") {
			(*iter)->Offset(PointMake(pt.x, (pt.y + ButtonSmallHeight)));
			(*iter)->SetEnable(true);
			(*iter)->SetVisible(true);
			count++;
		}
		if (count >= 2) break;
	}
	EVENTMANAGER->SetSelectable(eSelectableType::BUTTON);
	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);
}

void BattleScene::ClearMove(eObjectType type, int nextIndex)
{
	ClearAllButton();

	mbIsPathOn = false;
	mbIsStartMove = false;
	if (type == eObjectType::PLAYER) {
		mvTile[nextIndex]->SetType(eObjectType::PLAYER);
		PLAYERMANAGER->SetPlayerOnTileIndex(nextIndex);
		PLAYERMANAGER->SetPlayerOnTileRowCol({ mvTile[nextIndex]->GetRow(), mvTile[nextIndex]->GetCol() });
		PLAYERMANAGER->SetStatePlayer(eState::IDLE);
		PLAYERMANAGER->SetPlayerCanMove(false);
	}
	else if (type == eObjectType::ENEMY) {
		mvTile[nextIndex]->SetType(eObjectType::ENEMY);
		PLAYERMANAGER->SetEnemyOnTileIndex(nextIndex);
		PLAYERMANAGER->SetEnemyOnTileRowCol({ mvTile[nextIndex]->GetRow(), mvTile[nextIndex]->GetCol() });
		PLAYERMANAGER->SetStateEnemy(eState::IDLE);
		PLAYERMANAGER->SetEnemyCanMove(false);
	}
	PLAYERMANAGER->SetLockOn(false);
	mqPath.clear();
	msMoveRange.clear();
	mcRange->SetRangeinit();
}

void BattleScene::ClearAttack()
{
	msAttackRange.clear();
	miAttackHitIndex = -1;
	mbIsAttackRangeOn = false;
	mbIsAttackHitRangeOn = false;
}

void BattleScene::ClearSpell()
{
	msSpellRange.clear();
	msSpellHitRange.clear();
	mbIsSpellRangeOn = false;
	mbIsSpellHitRangeOn = false;
}

void BattleScene::ClearPhase()
{
	ClearAttack();
	ClearSpell();
	PLAYERMANAGER->SetLockOnPlayerIndex(-1);
	PLAYERMANAGER->SetLockOn(false);
	mqPath.clear();
	msMoveRange.clear();
	mcRange->SetRangeinit();
	EVENTMANAGER->SetSelectable(eSelectableType::TILE);
	EVENTMANAGER->SetPhase(eSelectPhase::UNIT_SELECT);
}

void BattleScene::ClearAllButton(const char* str)
{
	for (auto iter = mvBTN.begin(); iter != mvBTN.end(); ++iter) {
		if ((*iter)->GetKeyName() == str) continue;
		(*iter)->SetEnable(false);
		(*iter)->SetVisible(false);
	}
}

void BattleScene::TurnButton()
{
	CancelButton();

	for (auto& iter = mvBTN.begin(); iter != mvBTN.end(); ++iter) {
		if ((*iter)->GetKeyName() == "end_of_turn") {
			(*iter)->SetEnable(true);
			(*iter)->SetVisible(true);
			break;
		}
	}
	EVENTMANAGER->SetSelectable(eSelectableType::BUTTON);
	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);
}

void BattleScene::EndOfTurn()
{
	ClearAllButton();
	mbIsPlayerTurn = false;
	miEnemyBehaviorCount = 0;
	PLAYERMANAGER->SetEnemyAllCanMoveAndAttack(true);
}