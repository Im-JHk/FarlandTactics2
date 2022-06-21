#pragma once
class Tile;
class Player;
class Enemy;

class Map
{
private:
	vector<Tile*> mvTile;
	vector<Player*> mvPlayer;
	vector<Enemy*> mvEnemy;

	int miStage;
	int miRow;
	int miColumn;
public:
	void Init(vector<Tile*> vTile, vector<Player*> vPlayer, vector<Enemy*> vEnemy, int stage, int row, int col);
	void Release();

	vector<Tile*> GetVecTile() { return mvTile; }
	vector<Player*> GetVecPlayer() { return mvPlayer; }
	vector<Enemy*> GetVecEnemy() { return mvEnemy; }
	int GetStageNumber() { return miStage; }
	int GetRow() { return miRow; }
	int GetColumn() { return miColumn; }

	void SetVecTiles(vector<Tile*> vTile) { mvTile = vTile; }
	void SetVecAddTile(Tile* tile) { mvTile.push_back(tile); }
	void SetVecPlayers(vector<Player*> vPlayer) { mvPlayer = vPlayer; }
	void SetVecAddPlayer(Player* player) { mvPlayer.push_back(player); }
	void SetVecEnemies(vector<Enemy*> vEnemy) { mvEnemy = vEnemy; }
	void SetVecAddEnemy(Enemy* enemy) { mvEnemy.push_back(enemy); }
	void SetStageNumber(int num) { miStage = num; }
	void SetRow(int row) { miRow = row; }
	void SetColumn(int col) { miColumn = col; }

	Map() {}
	~Map() {}
};

