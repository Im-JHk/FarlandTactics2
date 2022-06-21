#include "Stdafx.h"
#include "MouseManager.h"
#include "Button.h"
#include "Tile.h"

HRESULT MouseManager::init(void)
{
	meEvent = eMouseEventType::NONE;
	mtDownPoint = { 0, };
	mtUpPoint = { 0, };
	miDownIndex = -1;
	mfBeforeMoveTime = 0;
	mbIsPassiveMove = true;
	mbIsDown = false;
	mtCameraRect = CAMERAMANAGER->GetCameraRect();
	return S_OK;
}

void MouseManager::update(int x, int y)
{
	mtCameraRect = CAMERAMANAGER->GetCameraRect();
	if (mbIsDown) mfBeforeMoveTime += TIMEMANAGER->getElapsedTime();
	if (mfBeforeMoveTime > 1) {
		mbIsPassiveMove = false;
	}
	if (mbIsPassiveMove) {
		CheckButton(x, y);
	}
}

void MouseManager::release()
{
	mvButton.clear();
	mvTile.clear();
}

void MouseManager::MousePassiveMove()
{
	if (!mbIsPassiveMove) {
		mtDownPoint = { 0, };
		mtUpPoint = { 0, };
		mfBeforeMoveTime = 0;
		mbIsPassiveMove = true;
	}
}

void MouseManager::MouseLButtonDown(int x, int y)
{
	meEvent = eMouseEventType::DOWN;
	mtDownPoint = { x, y };
	mbIsDown = true;
}

void MouseManager::MouseLButtonUp(int x, int y)
{
	meEvent = eMouseEventType::UP;
	mtUpPoint = { x, y };
	mbIsDown = false;
	if(!mbIsPassiveMove) CAMERAMANAGER->OffsetDrag(mtDownPoint, mtUpPoint);
	MousePassiveMove();
}

void MouseManager::MouseRButtonDown(int x, int y)
{
	meEvent = eMouseEventType::DOWN;
	mtDownPoint = { x, y };
}

void MouseManager::MouseRButtonUp(int x, int y)
{
	meEvent = eMouseEventType::UP;
	mtUpPoint = { x, y };
	MousePassiveMove();
}

RECT MouseManager::GetRectFromActiveMove(void)
{
	RECT rc = RectMake(mtDownPoint.x, mtDownPoint.y, mtUpPoint.x, mtUpPoint.y);
	mtDownPoint = { 0, 0 };
	mtUpPoint = { 0, 0 };
	return rc;
}

void MouseManager::CheckButton(int x, int y)
{
	POINT pt = { x - mtCameraRect.left, y - mtCameraRect.top };
	eSelectableType type = EVENTMANAGER->GetSelectable();
	if (type == eSelectableType::BUTTON || type == eSelectableType::ALL) {
	}
	else if (type == eSelectableType::TILE) {
	}
	for (int i = 0; i < mvButton.size(); i++) {
		if (!(mvButton[i]->GetEnable())) continue;
		if (mvButton[i]->GetShape() == eButtonShapeType::RECTANGLE) {
			if (PointInRect(mvButton[i], pt, i)) break;
		}
		else {
			if (PointInRegion(mvButton[i], pt, i)) break;
		}
	}
	for (int i = 0; i < mvTile.size(); i++) {
		if (!(mvTile[i]->GetEnable())) continue;
		if (mvTile[i]->GetShape() == eButtonShapeType::RECTANGLE) {
			if (PointInRect(mvTile[i], pt, i)) break;
		}
		else {
			if (PointInRegion(mvTile[i], pt, i)) break;
		}
	}
}

template <typename T>
bool MouseManager::PointInRect(T t, POINT pt, int index)
{
	RECT rc = t->GetRect();
	rc.left -= mtCameraRect.left;
	rc.top -= mtCameraRect.top;
	rc.right -= mtCameraRect.left;
	rc.bottom -= mtCameraRect.top;

	if (PtInRect(&rc, pt)) {
		if (meEvent == eMouseEventType::DOWN) {
			miDownIndex = index;
			//t->ButtonDown();
			ResetValue();
		}
		else if (meEvent == eMouseEventType::UP) {
			//t->ButtonUp();
			if (miDownIndex == index) {
				if (EVENTMANAGER->GetPhase() == eSelectPhase::BUTTON_SELECT) {
					//t->ButtonClick();
				}
				t->ButtonClick();
				miDownIndex = -1;
			}
			ResetValue();
		}
		else if(miDownIndex == -1) {
			//meEvent = eMouseEventType::OVER;
			t->ButtonOver();
			ResetValue();
		}
		return true;
	}
	else {
		t->ButtonNone();
	}
	return false;
}

template <typename T>
bool MouseManager::PointInRegion(T t, POINT pt, int index)
{
	bool b = false;
	ISOMETRIC iso = MoveIsometric(t->GetIsometric(), mtCameraRect);

	HRGN hRgn = CreatePolygonRgn(iso.point, 4, ALTERNATE);
	if (PtInRegion(hRgn, _ptMouse.x, _ptMouse.y)) {
		if (meEvent == eMouseEventType::DOWN) {
			miDownIndex = index;
			t->ButtonDown();
			ResetValue();
		}
		else if (meEvent == eMouseEventType::UP) {
			t->ButtonUp();
			if (miDownIndex == index) {
				if (EVENTMANAGER->GetPhase() == eSelectPhase::UNIT_SELECT || EVENTMANAGER->GetPhase() == eSelectPhase::ALL) {
					if(mvTile[index]->GetType() == eObjectType::PLAYER) t->ButtonClick("unit");
				}
				else if (EVENTMANAGER->GetPhase() == eSelectPhase::MOVE_SELECT) {
					if (mvTile[index]->GetType() == eObjectType::TILE || mvTile[index]->GetType() == eObjectType::ITEM) {
						for (auto iter : msMoveRange) {
							if (iter == index) {
								t->ButtonClick("move");
								break;
							}
						}
					}
				}
				else if (EVENTMANAGER->GetPhase() == eSelectPhase::ATK_TYPE_SELECT) {
					t->ButtonClick("attack_type");
				}
				else if (EVENTMANAGER->GetPhase() == eSelectPhase::ATTACK_SELECT) {
					if (mvTile[index]->GetType() == eObjectType::ENEMY) {
						for (auto iter : msAttackRange) {
							if (iter == index) {
								t->ButtonClick("attack");
								break;
							}
						}
					}
				}
				else if (EVENTMANAGER->GetPhase() == eSelectPhase::SPELL_SELECT) {
					t->ButtonClick("spell");
				}
				else {
					t->ButtonClick("tile");
				}
				miDownIndex = -1;
			}
			ResetValue();
		}
		else {
			t->ButtonOver();
		}

		if (meEvent == eMouseEventType::R_DOWN) {
			miDownIndex = index;
			//t->ButtonDown();
			ResetValue();
		}
		else if (meEvent == eMouseEventType::R_UP) {
			if (miDownIndex == index) {
				if (mvTile[index]->GetType() == eObjectType::PLAYER) t->ButtonClick("r_unit");
				else if (mvTile[index]->GetType() == eObjectType::TILE) t->ButtonClick("r_tile");
				miDownIndex = -1;
			}
			ResetValue();
		}
		else if (miDownIndex == -1) {
			//meEvent = eMouseEventType::OVER;
			t->ButtonOver();
			//ResetValue();
		}
		b = true;
	}
	else {
		t->ButtonNone();
	}
	DeleteObject(hRgn);

	return b;
}

void MouseManager::ResetValue()
{
	meEvent = eMouseEventType::NONE;

}
