#pragma once
#include "GameNode.h"

class Object : public GameNode
{
protected:
	string mstrName;
	eDirection meDir;
	POINT mtAbsPoint;
	POINT mtRowCol;
	int miOnTileIndex;
	bool mbIsMovable;
public:
	virtual HRESULT init(string name, POINT pos, int index);
	virtual HRESULT init(string name, eDirection dir, POINT pos, POINT rowcol, int index, bool isMovable = true);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	eDirection GetDirection() { return meDir; }
	POINT GetCenter() { return mtAbsPoint; }
	POINT GetRowAndCol() { return mtRowCol; }
	int GetIndex() { return miOnTileIndex; }

	bool SetOffsetY(POINT start, int value, bool &isDown);
	bool SetOffset(POINT next, POINT value, int nextIndex);
	void SetRowAndCol(POINT rowCol) { mtRowCol = rowCol; }
	void SetIndex(int index) { miOnTileIndex = index; }

	Object();
	virtual ~Object();
};

