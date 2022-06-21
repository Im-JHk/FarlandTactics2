#include "Stdafx.h"
#include "EffectManager.h"
#include "Effect.h"

HRESULT EffectManager::init(void)
{
	meEventType = eEventType::NONE;
	mbIsEffectOn = false;
	return S_OK;
}

void EffectManager::release(void)
{
	for (mviEffect = mvEffect.begin(); mviEffect != mvEffect.end(); ++mviEffect) {
		(*mviEffect)->release();
		SAFE_DELETE((*mviEffect));
	}
}

void EffectManager::update(void)
{
	for (mviEffect = mvEffect.begin(); mviEffect != mvEffect.end(); ++mviEffect) {
		(*mviEffect)->update();
	}

	DeleteEffect();

	if (mbIsEffectOn) {
		if (GetIsEffectEnd()) {
			mCbVoidFunc2Int(static_cast<int>(meEventType), static_cast<int>(meReceiverType));
		}
	}
}

void EffectManager::render(RECT cameraRect)
{
	for (mviEffect = mvEffect.begin(); mviEffect != mvEffect.end(); ++mviEffect) {
		(*mviEffect)->render(cameraRect);
	}
}

void EffectManager::AddEffect(string name, eEventType evType, eAttackType atkType, eObjectType rcvType, 
	eAnimationType aniType, POINT center, int index, int targetIndex, float delay, int frameY)
{
	meEventType = evType;
	meAttackType = atkType;
	meReceiverType = rcvType;

	Effect* effect = new Effect;
	effect->init(name, evType, atkType, rcvType, aniType, center, index, targetIndex, delay, frameY);
	effect->RegistVoidFuncAs4Int(mCbVoidFunc4Int);
	mvEffect.push_back(effect);
	if(!mbIsEffectOn) mbIsEffectOn = true;
}

void EffectManager::AddEffect(string name, eEventType evType, eAttackType atkType, eObjectType rcvType, eAnimationType aniType, POINT center, int index, int value)
{
	meEventType = evType;
	meAttackType = atkType;
	meReceiverType = rcvType;

	Effect* effect = new Effect;
	effect->init(name, evType, atkType, rcvType, aniType, center, index, value);
	effect->RegistVoidFuncAs4Int(mCbVoidFunc4Int);
	mvEffect.push_back(effect);
	if (!mbIsEffectOn) mbIsEffectOn = true;
}

void EffectManager::DeleteEffect(void)
{
	for (mviEffect = mvEffect.begin(); mviEffect != mvEffect.end();) {
		if ((*mviEffect)->GetIsEnd()) {
			SAFE_DELETE((*mviEffect));
			mviEffect = mvEffect.erase(mviEffect);
		}
		else ++mviEffect;
	}
}

bool EffectManager::GetIsEffectEnd()
{
	if (mbIsEffectOn && mvEffect.empty()) {
		mbIsEffectOn = false;
		return true;
	}
	return false;
}

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}
