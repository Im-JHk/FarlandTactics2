#pragma once
#include "SingletonBase.h"

class Button;
class Tile;

class MouseManager : public SingletonBase <MouseManager>
{
private:
	vector<Tile*> mvTile;
	vector<Button*> mvButton;
	set<int> msMoveRange;
	set<int> msAttackRange;
	set<int> msAttackHitRange;
	set<int> msSpellRange;
	set<int> msSpellHitRange;

	eMouseEventType meEvent;
	POINT mtDownPoint;
	POINT mtUpPoint;
	int miDownIndex;
	int miUpindex;
	float mfBeforeMoveTime;
	bool mbIsPassiveMove;
	bool mbIsDown;

private:
	RECT mtCameraRect;
public:
	HRESULT init(void);
	void update(int x, int y);
	void release();

	void MousePassiveMove(void);
	void MouseLButtonDown(int x, int y);
	void MouseLButtonUp(int x, int y);
	void MouseRButtonDown(int x, int y);
	void MouseRButtonUp(int x, int y);

	eMouseEventType GetMouseEvent(void) { return meEvent; }
	RECT GetRectFromActiveMove(void);
	bool GetMoveType(void) { return mbIsPassiveMove; }

	void SetMoveRange(set<int> sRange) { msMoveRange = sRange; }
	void SetAttackRange(set<int> sRange) { msAttackRange = sRange; }
	void SetAttackHitRange(set<int> sRange) { msAttackHitRange = sRange; }
	void SetSpellRange(set<int> sRange) { msSpellRange = sRange; }
	void SetSpellHitRange(set<int> sRange) { msSpellHitRange = sRange; }

	void ClearMoveRange(void) { msMoveRange.clear(); }
	void ClearAttackRange(void) { msAttackRange.clear(); }
	void ClearAttackHitRange(void) { msAttackHitRange.clear(); }
	void ClearSpellRange(void) { msSpellRange.clear(); }
	void ClearSpellHitRange(void) { msSpellHitRange.clear(); }
	void ClearAllRange(void) 
	{ 
		msMoveRange.clear(); 
		msAttackRange.clear();
		msAttackHitRange.clear();
		msSpellRange.clear();
		msSpellHitRange.clear();
	}

	void AddVecTile(vector<Tile*> vTile) { mvTile = vTile; }
	void AddVecButton(vector<Button*> vBTN) { mvButton = vBTN; }
	void AddButton(Button* btn) { mvButton.push_back(btn); }
	void CheckButton(int x, int y);
	void ResetValue();

	template <typename T>
	bool PointInRect(T t, POINT pt, int index);
	template <typename T>
	bool PointInRegion(T t, POINT pt, int index);

	MouseManager() {}
	~MouseManager() {}
};

