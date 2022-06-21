#pragma once

class Range
{
private:
	vector<Tile*> mvTile;
	set<int> msRange;

	int miCenterIndex;
	int miRowMax;
	int miColMax;
public:
	HRESULT init(vector<Tile*> vTiles, int row, int col);

	set<int> GetRange() { return msRange; }
	void SetRangeinit() { msRange.clear(); }
	void SetTiles(vector<Tile*> vTiles) { mvTile = vTiles; }

	void CalculateRange(int center, int maxCost);
	void CalculateAttackRange(eObjectType rcvType, int center, int maxCost, bool exceptCenter);
	void FindFourDirectionTile(Tile* tile, int cost, int maxCost);
	void FindFourDirectionTileExceptRceceiver(Tile* tile, eObjectType rcvType, int cost, int maxCost);
	
	Range() {}
	~Range() {}
};

