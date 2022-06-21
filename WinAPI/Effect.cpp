#include "Stdafx.h"
#include "Effect.h"

HRESULT Effect::init(string name, eEventType evType, eAttackType atkType, eObjectType rcvType, eAnimationType aniType, POINT center, int index, int targetIndex, float delay, int frameY)
{
	Object::init(name, center, index);

	meEventType = evType;
	meAttackType = atkType;
	meReceiverType = rcvType;
	meAniType = aniType;

	mcImage = IMAGEMANAGER->findImage(name);
	mtCurrFrame = { 0, frameY };
	miStartPoint = center;

	mbAlpha = 255;
	miTargetIndex = targetIndex;

	mfElapsedTime = 0;
	mfFrameUpdateTime = 1.f / 20.f;
	mfDeltaTime = TIMEMANAGER->getElapsedTime();

	mfStartTime = TIMEMANAGER->getWorldTime();
	mfDuration = 0;
	mfDelay = delay;

	mbIsDown = false;
	mbIsStart = false;
	mbIsEnd = false;

	return S_OK;
}

HRESULT Effect::init(string name, eEventType evType, eAttackType atkType, eObjectType rcvType, eAnimationType aniType, POINT center, int index, int value)
{
	Object::init(name, center, index);

	meEventType = evType;
	meAttackType = atkType;
	meReceiverType = rcvType;
	meAniType = aniType;

	mcImage = IMAGEMANAGER->findImage(name);
	mtCurrFrame = { 0, value };
	miStartPoint = center;

	mbAlpha = 255;

	mfElapsedTime = 0;
	mfFrameUpdateTime = 1.f / 20.f;
	mfDeltaTime = TIMEMANAGER->getElapsedTime();

	mfStartTime = TIMEMANAGER->getWorldTime();
	mfDuration = 0;
	mfDelay = 0;

	mbIsDown = false;
	mbIsStart = false;
	mbIsEnd = false;

	return S_OK;
}

void Effect::release(void)
{
}

void Effect::update(void)
{
	mfDuration = TIMEMANAGER->getWorldTime() - mfStartTime;
	mfDeltaTime = TIMEMANAGER->getElapsedTime();

	if (mbIsStart && !mbIsEnd) {
		if (mstrName == "number_red") {
			if (Object::SetOffsetY(miStartPoint, 2, mbIsDown)) {
				mbIsEnd = true;
			}
		}
		else if (mstrName == "rogue1_death") {
			if (mbAlpha > 0) {
				mbAlpha -= 1;
				if (mbAlpha <= 0) {
					mbAlpha = 0;
					mbIsEnd = true;
				}
			}
		}
		Animation();
	}
	else if (mfDelay < mfDuration) {
		mbIsStart = true;
		if(meAttackType == eAttackType::NORMAL)	mCbVoidFunc4Int(static_cast<int>(meEventType), static_cast<int>(meAttackType), static_cast<int>(meReceiverType), miTargetIndex);
		else if (meAttackType == eAttackType::SPELL)	mCbVoidFunc4Int(static_cast<int>(meEventType), static_cast<int>(meAttackType), static_cast<int>(meReceiverType), GetIndex());
	}
}

void Effect::render(RECT cameraRect)
{
	if (mbIsStart && !mbIsEnd) {
		if (mstrName == "number_red") {
			mcImage->frameRender(getMemDC(), mtAbsPoint.x - mcImage->getFrameWidth() * 0.5f - cameraRect.left, mtAbsPoint.y - mcImage->getFrameHeight() + TileHeight * 0.5f - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y);
		}
		else if (mstrName == "rogue1_death") {
			mcImage->frameAlphaRender(getMemDC(), mtAbsPoint.x - mcImage->getFrameWidth() * 0.5f - cameraRect.left, mtAbsPoint.y - mcImage->getFrameHeight() + TileHeight * 0.5f - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y, mbAlpha);
		}
		else mcImage->frameRender(getMemDC(), mtAbsPoint.x - mcImage->getFrameWidth() * 0.5f - cameraRect.left, mtAbsPoint.y - mcImage->getFrameHeight() + TileHeight * 0.5f - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y);
	}
}

void Effect::Animation(void)
{
	mfElapsedTime += mfDeltaTime;
	if (mfElapsedTime >= mfFrameUpdateTime) {
		mfElapsedTime = 0;
		mtCurrFrame.x += 1;
		if (mtCurrFrame.x > mcImage->getMaxFrameX()) {
			switch (meAniType)
			{
			case eAnimationType::ONE:
				mtCurrFrame.x = mcImage->getMaxFrameX();
				mbIsEnd = true;
				break;
			case eAnimationType::ALL_LOOP:
				mtCurrFrame.x = 0;
				break;
			}
		}
	}
}
