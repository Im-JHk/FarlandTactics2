#pragma once
#include "Object.h"

class Enemy : public Object
{
private:
	vector<pair<string, POINT>> mvInfoBox;

	eState meCurrState;
	POINT mtCurrFrame;
	string msTypeName;

	int miCurrHp;
	int miCurrMp;
	int miMaxHp;
	int miMaxMp;
	int miAttack;
	int miMagic;
	int miDeffence;
	int miMGDeffence;

	int miFinalDamage;

	float mElapsedTime;
	float mDeltaTime;
	float mFrameUpdateTime;

	bool mbIsShowOn;
	bool mbIsCanMove;
	bool mbIsCanAttack;
	bool mbIsDamaged;

	bool mbIsDie;
public:
	virtual HRESULT init(string name, eDirection dir, eState state, POINT pos, POINT rowcol, POINT currHpMp, POINT maxHpMp, POINT atk, POINT def, int index, bool isDie);
	virtual HRESULT init(string name, eDirection dir, POINT pos, POINT rowcol, int index, bool isMovable = true);
	virtual void release(void);
	virtual void update(void);
	virtual void render(RECT cameraRect);
public:
	void ShowInfomation();
	void Animation(void);
	bool Move(Tile* prevTile, Tile* nextTile, eDirection dir);

	POINT CalcDeltaXY(eDirection dir);
	void CalcDamage(eAttackType atkType, int value);
	int Damaged(void);

	eState GetState() { return meCurrState; }
	string GetName() { return mstrName; }
	int GetMaxHp() { return miMaxHp; }
	int GetCurrentHp() { return miCurrHp; }
	int GetMaxMp() { return miMaxMp; }
	int GetCurrentMp() { return miCurrMp; }
	int GetPower() { return miAttack; }
	int GetMGPower() { return miMagic; }
	int GetDeffence() { return miDeffence; }
	int GetMGDeffence() { return miMGDeffence; }
	int GetFinalDamage() { return miFinalDamage; }
	bool GetCanMove() { return mbIsCanMove; }
	bool GetCanAttack() { return mbIsCanAttack; }
	bool GetIsDamaged() { return mbIsDamaged; }
	bool GetIsDie() { return mbIsDie; }

	void SetDirection(eDirection dir) { meDir = dir; }
	void SetState(eState state) { meCurrState = state; mtCurrFrame.x = 0; }
	void SetFinalDamage(int damage) { miFinalDamage = damage; }
	void SetShowOn(bool b) { mbIsShowOn = b; }
	void SetCanMove(bool b) { mbIsCanMove = b; }
	void SetCanAttack(bool b) { mbIsCanAttack = b; }
	void SetIsDamaged(bool b) { mbIsDamaged = b; }

	Enemy();
	~Enemy();
};

