#pragma once
#include "Object.h"

class Effect : public Object
{
private:
	ImageBase* mcImage;

	eAnimationType meAniType;
	eEventType meEventType;
	eAttackType meAttackType;
	eObjectType meReceiverType;

	POINT mtCurrFrame;
	POINT miStartPoint;

	int mbAlpha;
	int miTargetIndex;

	float mfElapsedTime;
	float mfDeltaTime;
	float mfFrameUpdateTime;
	float mfStartTime;
	float mfDuration;
	float mfDelay;
	float mfRunTime;

	bool mbIsDown;
	bool mbIsStart;
	bool mbIsEnd;
private:
	map<string, VoidEventAsInt> mmCbVoidFuncInt;
	VoidEventAs4Int mCbVoidFunc4Int;
	VoidEventAs3Int mCbVoidFunc3Int;
	VoidEventAs2Int mCbVoidFunc2Int;
public:
	HRESULT init(string name, eEventType evType, eAttackType atkType, eObjectType rcvType, eAnimationType aniType, POINT center, int index, int targetIndex, float delay, int frameY);
	HRESULT init(string name, eEventType evType, eAttackType atkType, eObjectType rcvType, eAnimationType aniType, POINT center, int index, int value);
	void release(void);
	void update(void);
	void render(RECT cameraRect);

	void Animation(void);

	bool GetIsEnd(void) { return mbIsEnd; }
	void RegistVoidFuncAsInt(string key, VoidEventAsInt ev) { mmCbVoidFuncInt.insert({ key, ev }); }
	void RegistVoidFuncAs4Int(VoidEventAs4Int ev) { mCbVoidFunc4Int = ev; }
	void RegistVoidFuncAs3Int(VoidEventAs3Int ev) { mCbVoidFunc3Int = ev; }
	void RegistVoidFuncAs2Int(VoidEventAs2Int ev) { mCbVoidFunc2Int = ev; }

	Effect() {}
	~Effect() {}
};

