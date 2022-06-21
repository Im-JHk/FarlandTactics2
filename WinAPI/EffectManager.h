#pragma once
#include "SingletonBase.h"

class Effect;

class EffectManager : public SingletonBase <EffectManager>
{
private:
	vector<Effect*> mvEffect;
	vector<Effect*>::iterator mviEffect;
	set<int> msEffectRange;

	eEventType meEventType;
	eAttackType meAttackType;
	eObjectType meReceiverType;

	bool mbIsEffectOn;
private:
	map<string, VoidEventAsVoid> mmCbVoidFuncVoid;
	map<string, VoidEventAsInt> mmCbVoidFuncInt;
	VoidEventAs4Int mCbVoidFunc4Int;
	VoidEventAs3Int mCbVoidFunc3Int;
	VoidEventAs2Int mCbVoidFunc2Int;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(RECT cameraRect);

	void AddEffect(string name, eEventType evType, eAttackType atkType, eObjectType rcvType, eAnimationType aniType, POINT center, int index, int targetIndex, float delay, int frameY);
	void AddEffect(string name, eEventType evType, eAttackType atkType, eObjectType rcvType, eAnimationType aniType, POINT center, int index, int value);
	void DeleteEffect(void);

	eEventType GetEventType() { return meEventType; }
	bool GetIsEffectEnd();
	bool GetIsEmpty() { return mvEffect.empty(); }
	bool GetIsEffectOn() { return mbIsEffectOn; }

	void SetIsEffectOn(bool b) { mbIsEffectOn = b; }

	void ClearEffectRange() { msEffectRange.clear(); }

	void RegistVoidFuncAsVoid(string key, VoidEventAsVoid ev) { mmCbVoidFuncVoid.insert({ key, std::move(ev) }); }
	void RegistVoidFuncAsInt(string key, VoidEventAsInt ev) { mmCbVoidFuncInt.insert({ key, std::move(ev) }); }
	void RegistVoidFuncAs4Int(VoidEventAs4Int ev) { mCbVoidFunc4Int = std::move(ev); }
	void RegistVoidFuncAs3Int(VoidEventAs3Int ev) { mCbVoidFunc3Int = std::move(ev); }
	void RegistVoidFuncAs2Int(VoidEventAs2Int ev) { mCbVoidFunc2Int = std::move(ev); }


	EffectManager();
	~EffectManager();
};

