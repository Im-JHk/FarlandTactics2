#pragma once
#include "SingletonBase.h"

class Object;
class Player;
class Enemy;
class AStar;
class Range;
class Tile;

class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	vector<Tile*> mvTile;
	vector<Tile*>::iterator mviTile;
	vector<Player*> mvPlayer;
	vector<Player*>::iterator mviPlayer;
	vector<Enemy*> mvEnemy;
	vector<Enemy*>::iterator mviEnemy;

	set<int> msDamagedIndex;
	AStar* mcAStar;
	Range* mcRange;

	eAttackType meAtkType;
	POINT mtRowAndColMax;

	int miLockPlayerIndex;
	int miLockEnemyIndex;
	bool mbIsLockOn;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(RECT cameraRect);

public:	
	bool MovePlayer(Tile* prevTile, Tile* nextTile, eDirection dir);
	bool MoveEnemy(Tile* prevTile, Tile* nextTile, eDirection dir);
	void AttackPlayer(int targetIndex);
	void AttackEnemy(POINT eRowCol, POINT pRowCol);
	void SpellPlayer(string spellName, set<int> msRange);
	void SpellEnemy(string spellName, set<int> msRange);
	void ItemPlayer(string name, set<int> msRange);
	void ItemEnemy(string name, set<int> msRange);
	void DamageStartPlayer(eAttackType atkType, int index);
	void DamageEndPlayer();
	void DamageStartEnemy(eAttackType atkType, int index);
	void DamageEndEnemy();
	void DamageEnemy(int index);
	
	void IsDiePlayer();
	void IsDieEnemy();

	void DeleteEnemy(int arrNum);

	void ShowInfomation(int index);

	Object* GetPlayer(void);
	Object* GetEnemy(void);
	set<int> GetDamagedIndex(void) { return msDamagedIndex; }
	eState GetEnemyState(void);
	POINT GetPlayerCenter(void);
	int GetPlayerLockOnIndex(void) { return miLockPlayerIndex; }
	int GetEnemyLockOnIndex(void) { return miLockEnemyIndex; }
	int GetPlayerOnTileIndex(void);
	int GetEnemyOnTileIndex(void);
	bool GetLockOn(void) { return mbIsLockOn; }
	bool GetPlayerCanMove(void);
	bool GetPlayerCanAttack(void);

	void SetVecTile(vector<Tile*> vTile) { mvTile = vTile; }
	void SetRowColMax(POINT rowcol) { mtRowAndColMax = rowcol; }
	void SetAStar(AStar* astar) { mcAStar = astar; }
	void SetRange(Range* range) { mcRange = range; }

	void SetLockOn(bool b) { mbIsLockOn = b; }

	void SetPlayerAllCanMoveAndAttack(bool b);
	void SetPlayerCanMove(bool b);
	void SetPlayerCanAttack(bool b);
	void SetPlayerOnTileRowCol(POINT rowCol);
	void SetPlayerOnTileIndex(int index);
	void SetStatePlayer(eState state);
	void SetStateAllPlayer(eState state);
	void SetDirectionPlayer(eDirection dir);
	void SetLockOnPlayerIndex(int i) { miLockPlayerIndex = i; }
	
	void SetEnemyAllCanMoveAndAttack(bool b);
	void SetEnemyCanMove(bool b);
	void SetEnemyCanAttack(bool b);
	void SetEnemyOnTileRowCol(POINT rowCol);
	void SetEnemyOnTileIndex(int index);
	void SetStateEnemy(eState state);
	void SetStateAllEnemy(eState state);
	void SetDirectionEnemy(eDirection dir);
	void SetLockOnEnemyIndex(int i) { miLockEnemyIndex = i; }
	void SetDamagedEnemyIndex(set<int> range);

	void AddAllPlayer(vector<Player*> vPlayer) { mvPlayer = vPlayer; }
	void AddAllEnemy(vector<Enemy*> vEnemy) { mvEnemy = vEnemy; }
	void AddPlayer(string name, eDirection dir, POINT pos, POINT rowcol, int index);
	void AddEnemy(string name, eDirection dir, POINT pos, POINT rowcol, int index);
	void LockOnPlayerIndex(int index);
	void LockOnPlayerIndex(string name);
	void LockOnEnemyIndex(int index);
	void LockOnEnemyIndex(string name);

	bool FindImmediateEnemy(POINT rowColMax, int source);
	bool FindEnemy(int index);
	bool FindEnemy(set<int> sRange);

	bool AutoEnemyBehavior(int index);
	int FindNearestDestination(POINT eRowCol, POINT pRowCol, int pIndex);
	void FindNearestPlayerUnit(POINT rowCol, POINT &pRowCol, int &pIndex, int &pTileIndex);
	void FindNearestEnemyUnit(POINT rowCol, POINT &pRowCol, int &pIndex);
	bool CompareDistance(POINT start, POINT left, POINT right);
	bool IsPlayerImmediate(POINT eRowCol, POINT pRowCol);

	bool IsPlayerAllDie();
	bool IsEnemyAllDie();

	PlayerManager() {}
	~PlayerManager() {}
};

