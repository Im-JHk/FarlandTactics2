#include "Stdafx.h"
#include "Map.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"

void Map::Init(vector<Tile*> vTile, vector<Player*> vPlayer, vector<Enemy*> vEnemy, int stage, int row, int col)
{
	mvTile = vTile;
	mvPlayer = vPlayer;
	mvEnemy = vEnemy;
	miStage = stage;
	miRow = row;
	miColumn = col;
}

void Map::Release()
{
	mvTile.clear();
	mvPlayer.clear();
	mvEnemy.clear();
}
