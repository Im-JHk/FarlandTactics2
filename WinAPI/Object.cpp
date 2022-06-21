#include "Stdafx.h"
#include "Object.h"

HRESULT Object::init(string name, POINT pos, int index )
{
	mstrName = name;
	meDir = eDirection::LEFT;
	mtAbsPoint = pos;
	mtRowCol = { 0 };
	miOnTileIndex = index;
	mbIsMovable = false;

	return S_OK;
}

HRESULT Object::init(string name, eDirection dir, POINT pos, POINT rowcol, int index, bool isMovable)
{
	mstrName = name;
	meDir = dir;
	mtAbsPoint = pos;
	mtRowCol = rowcol;
	miOnTileIndex = index;
	mbIsMovable = isMovable;

	return S_OK;
}

void Object::release(void)
{
}

void Object::update(void)
{
}

void Object::render(void)
{
}

bool Object::SetOffsetY(POINT start, int value, bool &isDown)
{
	if (!isDown) {
		mtAbsPoint.y -= value;
		if (start.y - NumberUpMax > mtAbsPoint.y) {
			mtAbsPoint.y = start.y - NumberUpMax;
			isDown = true;
		}
	}
	else {
		mtAbsPoint.y += value;
		if (start.y < mtAbsPoint.y) {
			mtAbsPoint.y = start.y;
			return true;
		}
	}
	return false;
}

bool Object::SetOffset(POINT next, POINT value, int nextIndex)
{
	mtAbsPoint.x += value.x;
	mtAbsPoint.y += value.y;
	switch (meDir)
	{
	case eDirection::LEFT:
		if (mtAbsPoint.x < next.x || mtAbsPoint.y < next.y) {
			mtAbsPoint.x = next.x;
			mtAbsPoint.y = next.y;
			miOnTileIndex = nextIndex;
			return true;
		}
		break;
	case eDirection::RIGHT:
		if (mtAbsPoint.x > next.x || mtAbsPoint.y > next.y) {
			mtAbsPoint.x = next.x;
			mtAbsPoint.y = next.y;
			miOnTileIndex = nextIndex;
			return true;
		}
		break;
	case eDirection::UP:
		if (mtAbsPoint.x > next.x || mtAbsPoint.y < next.y) {
			mtAbsPoint.x = next.x;
			mtAbsPoint.y = next.y;
			miOnTileIndex = nextIndex;
			return true;
		}
		break;
	case eDirection::DOWN:
		if (mtAbsPoint.x < next.x || mtAbsPoint.y > next.y) {
			mtAbsPoint.x = next.x;
			mtAbsPoint.y = next.y;
			miOnTileIndex = nextIndex;
			return true;
		}
		break;
	}
	return false;
}

Object::Object()
{
}

Object::~Object()
{
}
