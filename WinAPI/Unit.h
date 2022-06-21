#pragma once
#include "Object.h"

class Unit : public Object
{
//protected:
//	eState meCurrState;
//	POINT mtCurrFrame;
//	string msTypeName;
//
//	int miCurrHp;
//	int miCurrMp;
//	int miMaxHp;
//	int miMaxMp;
//	int miAttack;
//	int miMagic;
//	int miDeffence;
//	int miMGDeffence;
//
//	int miFinalDamage;
//
//	float mElapsedTime;
//	float mDeltaTime;
//	float mFrameUpdateTime;
//
//	bool mbIsShowOn;
//	bool mbIsCanMove;
//	bool mbIsCanAttack;
//	bool mbIsDamaged;
//public:
//	virtual HRESULT init(string name, eDirection dir, POINT pos, POINT rowcol, int index, bool isMovable = true);
//	virtual void release(void);
//	virtual void update(void);
//	virtual void render(void);
//public:
//	POINT CalcDeltaXY(eDirection dir);
//	void CalcDamage(int value, bool type);
//	bool Damaged(int value, bool type);
//
//	string GetName() { return mstrName; }
//	int GetPower() { return miAttack; }
//	int GetMGPower() { return miMagic; }
//	int GetDeffence() { return miDeffence; }
//	int GetMGDeffence() { return miMGDeffence; }
//
//	void SetState(eState state) { meCurrState = state; mtCurrFrame.x = 0; }
//	void SetFinalDamage(int damage) { miFinalDamage = damage; }
//	void SetShowOn(bool b) { mbIsShowOn = b; }
//	void SetIsDamaged(bool b) { mbIsDamaged = b; }
//
	Unit() {}
	virtual ~Unit() {}
};

