#pragma once
#include "Map.h"

class MapData
{
private:
	queue<Map*> mqMap;
public:
	void Init(void);
	void Release(void);

	void SaveMapData(const vector<Tile*> vTile, const vector<Player*> vPlayer, const vector<Enemy*> vEnemy, const int row, const int col, const int stageNum);
	void LoadMapData(vector<Tile*> &vTile, vector<Player*> &vPlayer, vector<Enemy*> &vEnemy, int &row, int &col, int &num);

	void MakeStringAttachInt(string &output, string str, int i);

	Map* GetMap(int num) { if (mqMap.size() >= num) return mqMap.front() + num; }
	queue<Map*>* GetQueueMaps(void) { if (!mqMap.empty()) return &mqMap; }

	MapData() {}
	~MapData() {}
};

