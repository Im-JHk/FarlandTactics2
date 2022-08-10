#include "Stdafx.h"
#include "Range.h"
#include "Tile.h"

HRESULT Range::init(vector<Tile*> vTiles, int row, int col)
{
	mvTile = vTiles;
	miRowMax = row;
	miColMax = col;

	return S_OK;
}

void Range::CalculateRange(int center, int maxCost)
{
	if (!msRange.empty()) msRange.clear();
	FindFourDirectionTile(mvTile[center], 0, maxCost);
}

void Range::CalculateAttackRange(eObjectType rcvType, int center, int maxCost, bool exceptCenter)
{
	if (!msRange.empty()) msRange.clear();
	FindFourDirectionTileExceptRceceiver(mvTile[center], rcvType, 0, maxCost);
	if(!exceptCenter) msRange.insert(center);
}

void Range::FindFourDirectionTile(Tile* tile, int cost, int maxCost)
{
	if (cost >= maxCost) return;

	int row = tile->GetRow();
	int col = tile->GetCol();
	int index = tile->GetIndex();

	int left = index - 1;
	int right = index + 1;
	int up = index - miRowMax;
	int down = index + miRowMax;

	if (row - 1 >= 0) {
		if (mvTile[left]->GetType() == eObjectType::TILE) {
			msRange.insert(left);
		}
		FindFourDirectionTile(mvTile[left], cost + 1, maxCost);
	}
	if (row + 1 < miRowMax) {
		if (mvTile[right]->GetType() == eObjectType::TILE) {
			msRange.insert(right);
		}
		FindFourDirectionTile(mvTile[right], cost + 1, maxCost);
	}
	if (col - 1 >= 0) {
		if (mvTile[up]->GetType() == eObjectType::TILE) {
			msRange.insert(up);
		}
		FindFourDirectionTile(mvTile[up], cost + 1, maxCost);
	}
	if (col + 1 < miColMax) {
		if (mvTile[down]->GetType() == eObjectType::TILE) {
			msRange.insert(down);
		}
		FindFourDirectionTile(mvTile[down], cost + 1, maxCost);
	}
}

void Range::FindFourDirectionTileExceptRceceiver(Tile * tile, eObjectType rcvType, int cost, int maxCost)
{
	if (cost >= maxCost) return;

	int row = tile->GetRow();
	int col = tile->GetCol();
	int index = tile->GetIndex();

	int left = index - 1;
	int right = index + 1;
	int up = index - miRowMax;
	int down = index + miRowMax;

	if (row - 1 >= 0) {
		if (mvTile[left]->GetType() == eObjectType::TILE || mvTile[left]->GetType() == rcvType) {
			msRange.insert(left);
		}
		FindFourDirectionTileExceptRceceiver(mvTile[left], rcvType, cost + 1, maxCost);
	}
	if (row + 1 < miRowMax) {
		if (mvTile[right]->GetType() == eObjectType::TILE || mvTile[right]->GetType() == rcvType) {
			msRange.insert(right);
		}
		FindFourDirectionTileExceptRceceiver(mvTile[right], rcvType, cost + 1, maxCost);
	}
	if (col - 1 >= 0) {
		if (mvTile[up]->GetType() == eObjectType::TILE || mvTile[up]->GetType() == rcvType) {
			msRange.insert(up);
		}
		FindFourDirectionTileExceptRceceiver(mvTile[up], rcvType, cost + 1, maxCost);
	}
	if (col + 1 < miColMax) {
		if (mvTile[down]->GetType() == eObjectType::TILE || mvTile[down]->GetType() == rcvType) {
			msRange.insert(down);
		}
		FindFourDirectionTileExceptRceceiver(mvTile[down], rcvType, cost + 1, maxCost);
	}
}
