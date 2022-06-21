#include "Stdafx.h"
#include "Tile.h"

HRESULT Tile::init(eObjectType type, POINT center, POINT size, POINT rowColMax, POINT rowCol, int index, int tileFrameX, int floorFrameX, int floorLevel)
{
	Button::init("tile_button", 0, "tile", eButtonShapeType::ISOMETRIC, center, size);

	mcTileImage = IMAGEMANAGER->findImage("tile");
	mcFloorImage = IMAGEMANAGER->findImage("floor");
	meType = type;
	mtTileRect = RectMakeCenter(mtCenter.x, mtCenter.y, TileWidth, TileHeight);
	mtFloorRect = RectMake(mtCenter.x - TileWidth / 2, mtCenter.y, TileWidth, FloorHeight);
	mtRowColMax = rowColMax;
	mtRowCol = rowCol;
	miTileFrameX = tileFrameX;
	miFloorFrameX = floorFrameX;
	miFloorLevel = floorLevel;
	miIndex = index;
	mbIsSelect = false;

	return S_OK();
}

HRESULT Tile::init(POINT rowColMax, int row, int col)
{
	POINT size = { TileWidth , TileHeight };
	POINT center = { 
		(TileWidth * rowColMax.x + row * TileWidth / 2 - col * TileWidth / 2), 
		(TileHeight * 2 + row * TileHeight / 2 + col * TileHeight / 2) 
	};
	miIndex = col * rowColMax.y + row;
	
	Button::init("tile_button", 0, "tile", eButtonShapeType::ISOMETRIC, center, size);

	mcTileImage = IMAGEMANAGER->findImage("tile");
	mcFloorImage = IMAGEMANAGER->findImage("floor");
	meType = eObjectType::TILE;
	mtTileRect = RectMakeCenter(mtCenter.x, mtCenter.y, TileWidth, TileHeight);
	mtFloorRect = RectMake(mtCenter.x - TileWidth / 2, mtCenter.y, TileWidth, FloorHeight);
	mtRowColMax = rowColMax;
	mtRowCol = { row, col };
	miFloorLevel = 0;
	miTileFrameX = -1;
	miFloorFrameX = -1;
	mbIsSelect = false;

	return S_OK;
}
