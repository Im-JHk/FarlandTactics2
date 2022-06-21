#pragma once
#include "GameNode.h"

class Map;
class MapData;

class MapToolScene : public GameNode
{
private:
	vector<Tile*> mvTile;
	vector<Button*> mvButton;
	vector<Player*> mvPlayer;
	vector<Enemy*> mvEnemy;
	MapData* mcMapdata;
	Map* mcCurrMap;

	eMapObject meObject;
	POINT mtStart;
	POINT mtPickTile;
	RECT mtObjViewRc;
	RECT mtCameraRect;
	POINT mtCameraPos;

	const char* msBuffer;
	
	int miStage;
	int miRow;
	int miCol;

	int miObjectNum;
	int miObjectNumMax;

	int miTileIndex;
	int miPickTileIndex;
	bool mbIsMoveTile;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void SetAllOfTile(int num);

	void SaveTheMapInfo(void);
	void LoadTheMapInfo(void);

	// CallBack
	void TileFloorUp(void);
	void TileFloorDown(void);
	void ObjectPrevious(void);
	void ObjectNext(void);
	void EnableEditRow(void);
	void EnableEditCol(void);
	void SubmitEdit();
	void ClearEditBox();
	void SelectTile(int index);
	void OnTheTile(int index);

	MapToolScene() {}
	~MapToolScene() {}
};

