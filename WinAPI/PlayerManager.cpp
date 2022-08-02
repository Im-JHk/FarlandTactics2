#include "Stdafx.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Object.h"
#include "AStar.h"
#include "Range.h"
#include "Tile.h"

HRESULT PlayerManager::init(void)
{
	mtRowAndColMax = { 0, };
	miLockPlayerIndex = 0;
	miLockEnemyIndex = 0;
	mbIsLockOn = false;

	return S_OK;
}

void PlayerManager::release(void)
{
	cout << "rel" << endl;
	for (int i = 0; i < mvPlayer.size(); i++) {
		SAFE_DELETE(mvPlayer[i]);
	}
	for (int i = 0; i < mvEnemy.size(); i++) {
		SAFE_DELETE(mvEnemy[i]);
	}
}

void PlayerManager::update(void)
{
	for (auto iter = mvPlayer.begin(); iter != mvPlayer.end(); ++iter) {
		(*iter)->update();
	}
	for (auto iter = mvEnemy.begin(); iter != mvEnemy.end(); ++iter) {
		(*iter)->update();
	}
}

void PlayerManager::render(RECT cameraRect)
{
	for (auto iter = mvPlayer.begin(); iter != mvPlayer.end(); ++iter) {
		(*iter)->render(cameraRect);
	}
	for (auto iter = mvEnemy.begin(); iter != mvEnemy.end(); ++iter) {
		(*iter)->render(cameraRect);
	}
}

bool PlayerManager::MovePlayer(Tile* prevTile, Tile* nextTile, eDirection dir)
{
	if (mvPlayer[miLockPlayerIndex]->Move(prevTile, nextTile, dir)) return true;
	return false;
}

bool PlayerManager::MoveEnemy(Tile * prevTile, Tile * nextTile, eDirection dir)
{
	if (mvEnemy[miLockEnemyIndex]->Move(prevTile, nextTile, dir)) return true;
	return false;
}

void PlayerManager::AttackPlayer(int targetIndex)
{
	eDirection dir;
	POINT pRowCol = mvPlayer[miLockPlayerIndex]->GetRowAndCol();
	POINT eRowCol;
	int index = mvPlayer[miLockPlayerIndex]->GetIndex();
	int frameY;

	for (auto iter : mvEnemy) {
		if ((*iter).GetIndex() == targetIndex) {
			eRowCol = (*iter).GetRowAndCol();
			break;
		}
	}

	mvPlayer[miLockPlayerIndex]->SetState(eState::ATTACK);
	if ((eRowCol.x == pRowCol.x - 1 && eRowCol.y == pRowCol.y)) {
		dir = eDirection::LEFT;
		frameY = 0;
		targetIndex = index - 1;
	}
	else if ((eRowCol.x == pRowCol.x + 1 && eRowCol.y == pRowCol.y)) {
		dir = eDirection::RIGHT;
		frameY = 1;
		targetIndex = index + 1;
	}
	else if ((eRowCol.x == pRowCol.x && eRowCol.y == pRowCol.y - 1)) {
		dir = eDirection::UP;
		frameY = 2;
		targetIndex = index - mtRowAndColMax.x;
	}
	else if ((eRowCol.x == pRowCol.x && eRowCol.y == pRowCol.y + 1)) {
		dir = eDirection::DOWN;
		frameY = 3;
		targetIndex = index + mtRowAndColMax.x;
	}
	SetDirectionPlayer(dir);
	EFFECTMANAGER->AddEffect(mvPlayer[miLockPlayerIndex]->GetName() + "_attack", eEventType::ATTACK, eAttackType::NORMAL, eObjectType::ENEMY, eAnimationType::ONE, mvPlayer[miLockPlayerIndex]->GetCenter(), index, targetIndex, 0, frameY);
}

void PlayerManager::AttackEnemy(POINT eRowCol, POINT pRowCol)
{
	eDirection dir;
	int frameY;
	int targetIndex;
	int index = mvEnemy[miLockEnemyIndex]->GetIndex();

	if ((pRowCol.x == eRowCol.x - 1 && pRowCol.y == eRowCol.y)) {
		dir = eDirection::LEFT;
		frameY = 0;
		targetIndex = index - 1;
	}
	else if ((pRowCol.x == eRowCol.x + 1 && pRowCol.y == eRowCol.y)) {
		dir = eDirection::RIGHT;
		frameY = 1;
		targetIndex = index + 1;
	}
	else if ((pRowCol.x == eRowCol.x && pRowCol.y == eRowCol.y - 1)) {
		dir = eDirection::UP;
		frameY = 2;
		targetIndex = index - mtRowAndColMax.y;
	}
	else if ((pRowCol.x == eRowCol.x && pRowCol.y == eRowCol.y + 1)) {
		dir = eDirection::DOWN;
		frameY = 3;
		targetIndex = index + mtRowAndColMax.y;
	}
	SetDirectionEnemy(dir);
	EFFECTMANAGER->AddEffect(mvEnemy[miLockEnemyIndex]->GetName() + "_attack", eEventType::ATTACK, eAttackType::NORMAL, eObjectType::PLAYER, eAnimationType::ONE, mvEnemy[miLockEnemyIndex]->GetCenter(), index, targetIndex, 0, frameY);
}

void PlayerManager::SpellPlayer(string spellName, set<int> msRange)
{
	mvPlayer[miLockPlayerIndex]->SetState(eState::SPELL);
	SetDamagedEnemyIndex(msRange);
	int count = 0;
	for (auto iter : msRange) {
		EFFECTMANAGER->AddEffect(spellName, eEventType::ATTACK, eAttackType::SPELL, eObjectType::ENEMY, eAnimationType::ONE, mvTile[iter]->GetCenter(), iter, iter, count * 0.15f, 0);
		count++;
	}
}

void PlayerManager::SpellEnemy(string spellName, set<int> msRange)
{
}

void PlayerManager::ItemPlayer(string name, set<int> msRange)
{
}

void PlayerManager::ItemEnemy(string name, set<int> msRange)
{
}

void PlayerManager::DamageStartPlayer(eAttackType atkType, int index)
{
	for (mviPlayer = mvPlayer.begin(); mviPlayer != mvPlayer.end(); ++mviPlayer) {
		if ((*mviPlayer)->GetIndex() == index) {
			(*mviPlayer)->SetIsDamaged(true);
			(*mviPlayer)->SetState(eState::DAMAGE);
			if (atkType == eAttackType::NORMAL) (*mviPlayer)->CalcDamage(atkType, mvEnemy[miLockEnemyIndex]->GetPower());
			else if (atkType == eAttackType::SPELL) (*mviPlayer)->CalcDamage(atkType, mvEnemy[miLockEnemyIndex]->GetMGPower());
			break;
		}
	}
}

void PlayerManager::DamageEndPlayer()
{
	int quotient;
	int remainder;
	for (mviPlayer = mvPlayer.begin(); mviPlayer != mvPlayer.end(); ++mviPlayer) {
		if ((*mviPlayer)->GetIsDamaged() == true) {
			vector<PAIR_INT> mvDamageNum;
			int count = 0;
			for (int quotient = (*mviPlayer)->Damaged(); quotient != 0; quotient = quotient / 10) {
				remainder = quotient % 10;
				mvDamageNum.push_back(make_pair(count, remainder));
				count++;
			}
			for (int i = 0; i < mvDamageNum.size(); i++) {
				POINT ct = (*mviPlayer)->GetCenter();
				if (mvDamageNum.size() == 1) {
					EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::PLAYER, eAnimationType::ALL_LOOP, { ct.x, ct.y - NumberDownMax }, (*mviPlayer)->GetIndex(), mvDamageNum[i].second);
				}
				else if (mvDamageNum.size() == 2) {
					if (mvDamageNum[i].first == 0) {
						EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::PLAYER, eAnimationType::ALL_LOOP, { ct.x + NumberWidth, ct.y - NumberDownMax }, (*mviPlayer)->GetIndex(), mvDamageNum[i].second);
					}
					else if (mvDamageNum[i].first == 1) {
						EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::PLAYER, eAnimationType::ALL_LOOP, { ct.x - NumberWidth, ct.y - NumberDownMax }, (*mviPlayer)->GetIndex(), mvDamageNum[i].second);
					}
				}
				else if (mvDamageNum.size() == 3) {
					if (mvDamageNum[i].first == 0) {
						EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::PLAYER, eAnimationType::ALL_LOOP, { ct.x + NumberWidth * 2, ct.y - NumberDownMax }, (*mviPlayer)->GetIndex(), mvDamageNum[i].second);
					}
					else if (mvDamageNum[i].first == 1) {
						EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::PLAYER, eAnimationType::ALL_LOOP, { ct.x, ct.y - NumberDownMax }, (*mviPlayer)->GetIndex(), mvDamageNum[i].second);
					}
					else if (mvDamageNum[i].first == 2) {
						EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::PLAYER, eAnimationType::ALL_LOOP, { ct.x - NumberWidth * 2, ct.y - NumberDownMax }, (*mviPlayer)->GetIndex(), mvDamageNum[i].second);
					}
				}
			}
			(*mviPlayer)->SetIsDamaged(false);
		}
	}
}

void PlayerManager::DamageStartEnemy(eAttackType atkType, int index)
{
	for (mviEnemy = mvEnemy.begin(); mviEnemy != mvEnemy.end(); ++mviEnemy) {
		if ((*mviEnemy)->GetIndex() == index) {
			(*mviEnemy)->SetIsDamaged(true);
			(*mviEnemy)->SetState(eState::DAMAGE);
			if (atkType == eAttackType::NORMAL) (*mviEnemy)->CalcDamage(atkType, mvPlayer[miLockPlayerIndex]->GetPower());
			else if (atkType == eAttackType::SPELL) (*mviEnemy)->CalcDamage(atkType, mvPlayer[miLockPlayerIndex]->GetMGPower());
		}
	}
}

void PlayerManager::DamageEndEnemy()
{
	int quotient;
	int remainder;
	for (mviEnemy = mvEnemy.begin(); mviEnemy != mvEnemy.end(); ++mviEnemy) {
		if ((*mviEnemy)->GetIsDamaged() == true) {
			vector<PAIR_INT> mvDamageNum;
			int count = 0;
			for (int quotient = (*mviEnemy)->Damaged(); quotient != 0; quotient = quotient / 10) {
				remainder = quotient % 10;
				mvDamageNum.push_back(make_pair(count, remainder));
				count++;
			}
			for (int i = 0; i < mvDamageNum.size(); i++) {
				POINT ct = (*mviEnemy)->GetCenter();
				if (mvDamageNum.size() == 1) {
					EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::ENEMY, eAnimationType::ALL_LOOP, { ct.x, ct.y - NumberDownMax }, (*mviEnemy)->GetIndex(), mvDamageNum[i].second);
				}
				else if (mvDamageNum.size() == 2) {
					if (mvDamageNum[i].first == 0) {
						EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::ENEMY, eAnimationType::ALL_LOOP, { ct.x + NumberWidth, ct.y - NumberDownMax }, (*mviEnemy)->GetIndex(), mvDamageNum[i].second);
					}
					else if (mvDamageNum[i].first == 1) {
						EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::ENEMY, eAnimationType::ALL_LOOP, { ct.x - NumberWidth, ct.y - NumberDownMax }, (*mviEnemy)->GetIndex(), mvDamageNum[i].second);
					}
				}
				else if (mvDamageNum.size() == 3) {
					if (mvDamageNum[i].first == 0) {
						EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::ENEMY, eAnimationType::ALL_LOOP, { ct.x + NumberWidth * 2, ct.y - NumberDownMax }, (*mviEnemy)->GetIndex(), mvDamageNum[i].second);
					}
					else if (mvDamageNum[i].first == 1) {
						EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::ENEMY, eAnimationType::ALL_LOOP, { ct.x, ct.y - NumberDownMax }, (*mviEnemy)->GetIndex(), mvDamageNum[i].second);
					}
					else if (mvDamageNum[i].first == 2) {
						EFFECTMANAGER->AddEffect("number_red", eEventType::ATTACKED, eAttackType::NONE, eObjectType::ENEMY, eAnimationType::ALL_LOOP, { ct.x - NumberWidth * 2, ct.y - NumberDownMax }, (*mviEnemy)->GetIndex(), mvDamageNum[i].second);
					}
				}
			}
			(*mviEnemy)->SetIsDamaged(false);
		}
	}
}

void PlayerManager::DamageEnemy(int index)
{
	for (mviEnemy = mvEnemy.begin(); mviEnemy != mvEnemy.end(); ++mviEnemy) {
		if ((*mviEnemy)->GetIndex() == index) {
			(*mviEnemy)->SetIsDamaged(true);
			(*mviEnemy)->SetState(eState::DAMAGE);
		}
	}
}

void PlayerManager::IsDiePlayer()
{
	for (mviPlayer = mvPlayer.begin(); mviPlayer != mvPlayer.end(); ++mviPlayer) {
		if ((*mviPlayer)->GetIsDie()) {
			(*mviPlayer)->SetState(eState::DEATH);
		}
	}
}

void PlayerManager::IsDieEnemy()
{
	for (mviEnemy = mvEnemy.begin(); mviEnemy != mvEnemy.end();) {
		if ((*mviEnemy)->GetIsDie()) {
			mvTile[(*mviEnemy)->GetIndex()]->SetType(eObjectType::TILE);
			EFFECTMANAGER->AddEffect("rogue1_death", eEventType::DIE, eAttackType::NONE, eObjectType::ENEMY, eAnimationType::ALL_LOOP, (*mviEnemy)->GetCenter(), (*mviEnemy)->GetIndex(), (*mviEnemy)->GetIndex(), 0, static_cast<int>((*mviEnemy)->GetDirection()));
			SAFE_DELETE((*mviEnemy));
			mviEnemy = mvEnemy.erase(mviEnemy);
		}
		else ++mviEnemy;
	}
}

void PlayerManager::DeleteEnemy(int arrNum)
{
	SAFE_DELETE(mvEnemy[arrNum]);
	mvEnemy.erase(mvEnemy.begin() + arrNum);
}

void PlayerManager::ShowInfomation(int index)
{
	switch (mvTile[index]->GetType())
	{
	case eObjectType::PLAYER:
		for (int i = 0; i < mvPlayer.size(); i++) {
			if (mvPlayer[i]->GetIndex() == index) {
				mvPlayer[i]->ShowInfomation();
				break;
			}
		}
		break;
	case eObjectType::ENEMY:
		for (int i = 0; i < mvEnemy.size(); i++) {
			if (mvEnemy[i]->GetIndex() == index) {
				mvEnemy[i]->ShowInfomation();
				break;
			}
		}
		break;
	}
	for (auto iter : mvPlayer) {
		if (iter->GetIndex() != index) (*iter).SetShowOn(false);
	}
	for (auto iter : mvEnemy) {
		if (iter->GetIndex() != index) (*iter).SetShowOn(false);
	}
}

Object * PlayerManager::GetPlayer(void)
{
	return mvPlayer[miLockPlayerIndex];
}

Object * PlayerManager::GetEnemy(void)
{
	return mvEnemy[miLockEnemyIndex];
}

eState PlayerManager::GetEnemyState(void)
{
	return mvEnemy[miLockEnemyIndex]->GetState();
}

POINT PlayerManager::GetPlayerCenter(void)
{
	return mvPlayer[miLockPlayerIndex]->GetCenter();
}

int PlayerManager::GetPlayerOnTileIndex(void)
{
	return mvPlayer[miLockPlayerIndex]->GetIndex();
}

int PlayerManager::GetEnemyOnTileIndex(void)
{
	return mvEnemy[miLockEnemyIndex]->GetIndex();
}

bool PlayerManager::GetPlayerCanMove(void)
{
	if (mvPlayer[miLockPlayerIndex]->GetCanMove()) return true;
	else return false;
}

bool PlayerManager::GetPlayerCanAttack(void)
{
	if (mvPlayer[miLockPlayerIndex]->GetCanAttack()) return true;
	else return false;
}

void PlayerManager::SetPlayerAllCanMoveAndAttack(bool b)
{
	for (auto iter : mvPlayer) {
		iter->SetCanMove(b);
		iter->SetCanAttack(b);
	}
}

void PlayerManager::SetPlayerCanMove(bool b)
{
	mvPlayer[miLockPlayerIndex]->SetCanMove(b);
}

void PlayerManager::SetPlayerCanAttack(bool b)
{
	mvPlayer[miLockPlayerIndex]->SetCanAttack(b);
}

void PlayerManager::SetEnemyAllCanMoveAndAttack(bool b)
{
	for (auto iter : mvEnemy) {
		iter->SetCanMove(b);
		iter->SetCanAttack(b);
	}
}

void PlayerManager::SetEnemyCanMove(bool b)
{
	mvEnemy[miLockEnemyIndex]->SetCanMove(b);
}

void PlayerManager::SetEnemyCanAttack(bool b)
{
	mvEnemy[miLockEnemyIndex]->SetCanAttack(b);
}

void PlayerManager::SetPlayerOnTileRowCol(POINT rowCol)
{
	mvPlayer[miLockPlayerIndex]->SetRowAndCol(rowCol);
}

void PlayerManager::SetPlayerOnTileIndex(int index)
{
	mvPlayer[miLockPlayerIndex]->SetIndex(index);
}

void PlayerManager::SetEnemyOnTileRowCol(POINT rowCol)
{
	mvEnemy[miLockEnemyIndex]->SetRowAndCol(rowCol);
}

void PlayerManager::SetEnemyOnTileIndex(int index)
{
	mvEnemy[miLockEnemyIndex]->SetIndex(index);
}

void PlayerManager::SetStatePlayer(eState state)
{
	mvPlayer[miLockPlayerIndex]->SetState(state);
}

void PlayerManager::SetStateEnemy(eState state)
{
	mvEnemy[miLockEnemyIndex]->SetState(state);
}

void PlayerManager::SetStateAllPlayer(eState state)
{
	for (mviPlayer = mvPlayer.begin(); mviPlayer != mvPlayer.end(); ++mviPlayer) {
		if ((*mviPlayer)->GetState() != eState::DEATH) (*mviPlayer)->SetState(state);
	}
}

void PlayerManager::SetDirectionPlayer(eDirection dir)
{
	mvPlayer[miLockPlayerIndex]->SetDirection(dir);
}

void PlayerManager::SetStateAllEnemy(eState state)
{
	for (mviEnemy = mvEnemy.begin(); mviEnemy != mvEnemy.end(); ++mviEnemy) {
		(*mviEnemy)->SetState(state);
	}
}

void PlayerManager::SetDirectionEnemy(eDirection dir)
{
	mvEnemy[miLockEnemyIndex]->SetDirection(dir);
}

void PlayerManager::SetDamagedEnemyIndex(set<int> range)
{
	for (int i = 0; i < mvEnemy.size(); i++) {
		for (auto iter : range) {
			if (mvEnemy[i]->GetIndex() == iter) {
				msDamagedIndex.insert(i);
			}
		}
	}
}

void PlayerManager::AddPlayer(string name, eDirection dir, POINT pos, POINT rowcol, int index)
{
	Player* player = new Player;
	player->init(name, dir, pos, rowcol,  index);
	mvPlayer.push_back(player);
}

void PlayerManager::AddEnemy(string name, eDirection dir, POINT pos, POINT rowcol, int index)
{
	Enemy* enemy = new Enemy;
	enemy->init(name, dir, pos, rowcol, index);
	mvEnemy.push_back(enemy);
}

void PlayerManager::LockOnPlayerIndex(int index)
{
	if (!mbIsLockOn) {
		for (int i = 0; i < mvPlayer.size(); i++) {
			if (mvPlayer[i]->GetIndex() == index) {
				miLockPlayerIndex = i;
				mbIsLockOn = true;
				break;
			}
		}
	}
}

void PlayerManager::LockOnPlayerIndex(string name)
{
	if (!mbIsLockOn) {
		for (int i = 0; i < mvPlayer.size(); i++) {
			if (mvPlayer[i]->GetName() == name) {
				miLockPlayerIndex = i;
				mbIsLockOn = true;
				break;
			}
		}
	}
}

void PlayerManager::LockOnEnemyIndex(int index)
{
	if (!mbIsLockOn) {
		for (int i = 0; i < mvEnemy.size(); i++) {
			if (mvEnemy[i]->GetIndex() == index) {
				miLockEnemyIndex = i;
				mbIsLockOn = true;
				break;
			}
		}
	}
}

void PlayerManager::LockOnEnemyIndex(string name)
{
	if (!mbIsLockOn) {
		for (int i = 0; i < mvEnemy.size(); i++) {
			if (mvEnemy[i]->GetName() == name) {
				miLockEnemyIndex = i;
				mbIsLockOn = true;
				break;
			}
		}
	}
}

bool PlayerManager::FindImmediateEnemy(POINT rowColMax, int source)
{
	int row = mvTile[source]->GetRow();
	int col = mvTile[source]->GetCol();

	int left = source - 1;
	int right = source + 1;
	int up = source - rowColMax.x;
	int down = source + rowColMax.y;

	if (row - 1 >= 0 && left >= 0) {
		if (mvTile[left]->GetType() == eObjectType::ENEMY) return true;
	}
	if (row + 1 < rowColMax.x && right < rowColMax.x * rowColMax.y) {
		if (mvTile[right]->GetType() == eObjectType::ENEMY) return true;
	}
	if (col - 1 >= 0 && up >= 0) {
		if (mvTile[up]->GetType() == eObjectType::ENEMY) return true;
	}
	if (col + 1 < rowColMax.y && down < rowColMax.x * rowColMax.y) {
		if (mvTile[down]->GetType() == eObjectType::ENEMY) return true;
	}

	return false;
}

bool PlayerManager::FindEnemy(int index)
{
	if (mvTile[index]->GetType() == eObjectType::ENEMY) return true;
	else return false;
}

bool PlayerManager::FindEnemy(set<int> sRange)
{
	for (auto iter : sRange) {
		if (mvTile[iter]->GetType() == eObjectType::ENEMY) {
			return true;
		}
	}
	return false;
}

bool PlayerManager::AutoEnemyBehavior(int index)
{
	if (mvEnemy.size() <= index) return true;
	if (!mbIsLockOn) {
		mbIsLockOn = true;
		miLockEnemyIndex = index;
	}
	int dest;
	int enemyTileIndex = mvEnemy[index]->GetIndex();
	int playerIndex = 0;
	int playerTileIndex = (*mvPlayer.begin())->GetIndex();
	POINT playerRowColPick = (*mvPlayer.begin())->GetRowAndCol();

	FindNearestPlayerUnit(mvEnemy[index]->GetRowAndCol(), playerRowColPick, playerIndex, playerTileIndex);
	if (mvPlayer[playerIndex]->GetState() == eState::DEATH) return true;

	POINT eRowCol = mvEnemy[miLockEnemyIndex]->GetRowAndCol();
	POINT pRowCol = mvPlayer[playerIndex]->GetRowAndCol();

	if (IsPlayerImmediate(eRowCol, pRowCol)) {
		SetEnemyCanMove(false);
	}
	if (mvEnemy[index]->GetCanMove()) {
		dest = FindNearestDestination(mvEnemy[index]->GetRowAndCol(), mvPlayer[playerIndex]->GetRowAndCol(), playerIndex);
		if (dest == -1) {
			PLAYERMANAGER->SetEnemyAllCanMoveAndAttack(false);
			return true;
		}
		mvEnemy[index]->SetState(eState::MOVE);
		mcRange->CalculateRange(enemyTileIndex, 3);
		mcAStar->Algorithm(mcRange->GetRange(), enemyTileIndex, dest);
		mcRange->SetRangeinit();
	}
	else if (mvEnemy[index]->GetCanAttack()) {
		if (IsPlayerImmediate(eRowCol, pRowCol)) {
			mvEnemy[index]->SetState(eState::ATTACK);
			AttackEnemy(eRowCol, pRowCol);
			mbIsLockOn = false;
		}
		SetEnemyCanAttack(false);
	}
	else {
		mvEnemy[index]->SetState(eState::IDLE);
		mbIsLockOn = false;
	}

	return false;
}


void PlayerManager::FindNearestPlayerUnit(POINT rowCol, POINT &pRowCol, int &pIndex, int &pTileIndex)
{
	POINT playerRowColCom;
	for (int i = 0; i < mvPlayer.size(); i++) {
		if (mvPlayer[i]->GetState() != eState::DEATH) {
			pIndex = i;
			break;
		}
	}
	for (int i = pIndex + 1; i < mvPlayer.size(); i++) {
		if (mvPlayer[i]->GetState() == eState::DEATH) continue;
		playerRowColCom = mvPlayer[i]->GetRowAndCol();
		if (CompareDistance(rowCol, pRowCol, playerRowColCom)) {
			pRowCol = mvPlayer[i]->GetRowAndCol();
			pTileIndex = mvPlayer[i]->GetIndex();
			pIndex = i;
		}
	}
}

void PlayerManager::FindNearestEnemyUnit(POINT rowCol, POINT & pRowCol, int & pIndex)
{
	int enemyIndexPick = (*mvEnemy.begin())->GetIndex();
	POINT enemyRowColPick = (*mvEnemy.begin())->GetRowAndCol();
	POINT enemyRowColCom;
	for (auto iter = mvEnemy.begin() + 1; iter != mvEnemy.end(); ++iter) {
		enemyRowColCom = (*iter)->GetRowAndCol();
		if (CompareDistance(rowCol, enemyRowColPick, enemyRowColCom)) {
			enemyRowColPick = (*iter)->GetRowAndCol();
			enemyIndexPick = (*iter)->GetIndex();
		}
	}
	pRowCol = enemyRowColCom;
	pIndex = enemyIndexPick;
}

int PlayerManager::FindNearestDestination(POINT eRowCol, POINT pRowCol, int pIndex)
{
	vector<POINT> fourDirTile;
	POINT finalRowCol;
	int finalIndex;
	int center, left, right, up, down;

	center = mvPlayer[pIndex]->GetIndex();
	left = center - 1;
	right = center + 1;
	up = center - mtRowAndColMax.x;
	down = center + mtRowAndColMax.x;
	if (pRowCol.x - 1 >= 0 && mvTile[left]->GetType() == eObjectType::TILE) fourDirTile.push_back({ pRowCol.x - 1, pRowCol.y });
	if (pRowCol.x + 1 < mtRowAndColMax.x && mvTile[right]->GetType() == eObjectType::TILE) fourDirTile.push_back({ pRowCol.x + 1, pRowCol.y });
	if (pRowCol.y - 1 >= 0 && mvTile[up]->GetType() == eObjectType::TILE) fourDirTile.push_back({ pRowCol.x, pRowCol.y - 1 });
	if (pRowCol.y + 1 < mtRowAndColMax.y && mvTile[down]->GetType() == eObjectType::TILE) fourDirTile.push_back({ pRowCol.x, pRowCol.y + 1 });
	if (fourDirTile.empty()) return -1;

	finalRowCol = fourDirTile[0];
	for (int i = 1; i < fourDirTile.size(); i++) {
		if (CompareDistance(eRowCol, finalRowCol, fourDirTile[i])) finalRowCol = fourDirTile[i];
	}
	for (int i = 0; i < mvTile.size(); i++) {
		if (mvTile[i]->GetRow() == finalRowCol.x && mvTile[i]->GetCol() == finalRowCol.y) {
			finalIndex = i;
			break;
		}
	}

	return finalIndex;
}

bool PlayerManager::CompareDistance(POINT start, POINT left, POINT right)
{
	int lValue = abs(start.x - left.x) + abs(start.y - left.y);
	int rValue = abs(start.x - right.x) + abs(start.y - right.y);
	if (lValue > rValue) return true;
	else return false;
}

bool PlayerManager::IsPlayerImmediate(POINT eRowCol, POINT pRowCol)
{
	if ((pRowCol.x == eRowCol.x - 1 && pRowCol.y == eRowCol.y) ||
		(pRowCol.x == eRowCol.x + 1 && pRowCol.y == eRowCol.y) ||
		(pRowCol.y == eRowCol.y - 1 && pRowCol.x == eRowCol.x) ||
		(pRowCol.y == eRowCol.y + 1 && pRowCol.x == eRowCol.x)) {
		return true;
	}
	return false;
}

bool PlayerManager::IsPlayerAllDie()
{
	bool b = true;
	for (auto iter : mvPlayer) {
		if (iter->GetState() != eState::DEATH) {
			b = false;
			break;
		}
	}
	return b;
}

bool PlayerManager::IsEnemyAllDie()
{
	if (mvEnemy.empty()) return true;
	else false;
}
