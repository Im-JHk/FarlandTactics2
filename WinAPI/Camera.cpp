#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
	mtSize = PointMake(WINSIZE_X, WINSIZE_Y);
	mtRelPos = PointMake(0, 0);
	mtAbsPos = PointMake(0, 0);
	mtAbsCenter = PointMake(WINSIZE_X / 2, WINSIZE_Y / 2);
	mtRect = RectMakeCenter(mtAbsCenter.x, mtAbsCenter.y, mtSize.x, mtSize.y);

	return S_OK;
}

void Camera::release(void)
{
}

void Camera::SetCenterRect(void)
{
}

void Camera::SetCenterRect(POINT center)
{
	mtRect = RectMakeCenter(center.x, center.y, mtSize.x, mtSize.y);
	mtAbsCenter = center;
	mtAbsPos = { center.x - WINSIZE_X / 2, center.y - WINSIZE_Y / 2 };
}

void Camera::OffsetXY(int x, int y)
{
	mtAbsPos.x += x;
	mtAbsPos.y += y;
	mtAbsCenter.x += x;
	mtAbsCenter.x += y;

	mtRect = RectMakeCenter(mtAbsCenter.x, mtAbsCenter.y, mtSize.x, mtSize.y);
}

void Camera::OffsetDrag(POINT start, POINT end)
{
	mtAbsPos.x += (end.x - start.x) * (-1);
	mtAbsPos.y += (end.y - start.y) * (-1);
	mtAbsCenter.x += (end.x - start.x) * (-1);
	mtAbsCenter.x += (end.y - start.y) * (-1);

	mtRect = RectMakeCenter(mtAbsCenter.x, mtAbsCenter.y, mtSize.x, mtSize.y);
}
