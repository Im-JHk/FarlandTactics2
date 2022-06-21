#include "Stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("ROGUE1_IDLE", "Resources/Images/Object/Enemy/rogue1_idle.bmp", 300, 400, 3, 4, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("ROGUE1_MOVE", "Resources/Images/Object/Enemy/rogue1_move.bmp", 400, 400, 4, 4, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("ROGUE1_ATTACK", "Resources/Images/Object/Enemy/rogue1_attack.bmp", 600, 400, 6, 4, true, RGB(0, 255, 255));
	return S_OK;
}

void EnemyManager::release(void)
{
	for (int i = 0; i < mvEnemy.size(); i++) {
		mvEnemy[i]->release();
		SAFE_DELETE(mvEnemy[i]);
	}
}

void EnemyManager::update(void)
{
	for (auto iter = mvEnemy.begin(); iter != mvEnemy.end(); ++iter) {
		(*iter)->update();
	}
}

void EnemyManager::render(void)
{
	for (auto iter = mvEnemy.begin(); iter != mvEnemy.end(); ++iter) {
		(*iter)->render();
	}
}

bool EnemyManager::Move(string name, Tile * prevTile, Tile * nextTile, eDirection dir)
{
	mvEnemy[miLockIndex]->SetState(eState::MOVE);
	if (mvEnemy[miLockIndex]->Move(name, prevTile, nextTile, dir)) return true;
	return false;
}

void EnemyManager::Attack(string name)
{
}

void EnemyManager::Spell(string name)
{
}

void EnemyManager::Item(string name)
{
}

void EnemyManager::SetStateIndex()
{
}

void EnemyManager::AddEnemy(string name, eDirection dir, POINT pos, int index)
{
	Enemy* enemy = new Enemy;
	//enemy->init(name, dir, pos, , index);
	mvEnemy.push_back(enemy);
}

void EnemyManager::LockOnIndex(string name)
{
	if (!mbIsLockOn) {
		for (int i = 0; i < mvEnemy.size(); i++) {
			if (mvEnemy[i]->GetName() == name) {
				miLockIndex = i;
				mbIsLockOn = true;
				break;
			}
		}
	}
}
