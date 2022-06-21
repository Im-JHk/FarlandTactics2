#pragma once
#include "SingletonBase.h"

class Enemy;

class EnemyManager : public SingletonBase<EnemyManager>
{
private:
	vector<Enemy*> mvEnemy;

	int miLockIndex;
	bool mbIsLockOn;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bool Move(string name, Tile* prevTile, Tile* nextTile, eDirection dir);
	void Attack(string name);
	void Spell(string name);
	void Item(string name);

	bool GetLockOn(void) { return mbIsLockOn; }

	void SetStateIndex();
	void SetLockOn(bool b) { mbIsLockOn = b; }
	void SetLockOnIndex(int i) { miLockIndex = i; }

	void AddEnemy(string name, eDirection dir, POINT pos, int index);
	void LockOnIndex(string name);

	EnemyManager() {}
	~EnemyManager() {}
};

