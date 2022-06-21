#pragma once
#include "Button.h"

class Tile : public Button
{
private:
	ImageBase* mcTileImage;
	ImageBase* mcFloorImage;
	eObjectType meType;
	NODE mtNode;
	RECT mtTileRect;
	RECT mtFloorRect;
	POINT mtRowColMax;
	POINT mtRowCol;
	int miIndex;
	int miTileFrameX;
	int miFloorFrameX;
	int miFloorLevel;
	bool mbIsSelect;

public:
	HRESULT init(eObjectType type, POINT center, POINT size, POINT rowColMax, POINT rowCol, int index, int tileFrameX, int floorFrameX, int floorLevel);
	HRESULT init(POINT rowColMax, int row, int col);

	eObjectType GetType() { return meType; }
	RECT GetTileRect() { return mtTileRect; }
	RECT GetFloorRect() { return mtFloorRect; }
	int GetIndex() { return miIndex; }
	int GetRow() { return mtRowCol.x; }
	int GetCol() { return mtRowCol.y; }
	int GetTileFrameX() { return miTileFrameX; }
	int GetFloorFrameX() { return miFloorFrameX; }
	int GetFloorLevel() { return miFloorLevel; }

	void SetType(eObjectType type) { meType = type; }
	void SetIndex(int i) { miIndex = i; }
	void SetTileFrameX(int x) { miTileFrameX = x; }
	void SetFloorFrameX(int x) { miFloorFrameX = x; }
	void SetFloorRect(RECT rc) { mtFloorRect = rc; }
	void SetFloorLevel(int lv) { miFloorLevel = lv; }

	Tile() {}
	~Tile() {}
};

