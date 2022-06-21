#include "Stdafx.h"
#include "CameraManager.h"
#include "Object.h"

HRESULT CameraManager::init(void)
{
	mcCamera = new Camera;
	mcCamera->init();
	mcCurrentCamera = mcCamera;
	
	mbIsDragOn = false;
	mbIsFocusOn = false;
	mbIsCameraMoveOn = false;

	return S_OK;
}

void CameraManager::release(void)
{
	SAFE_DELETE(mcCamera);
}

void CameraManager::update(void)
{
	if (mbIsFocusOn) {
		mcCurrentCamera->SetCenterRect(mcFocusRef->GetCenter());
	}
}

void CameraManager::ChangeCamera(Camera *camera)
{
	if (camera) {
		mcCurrentCamera = camera;
	}
}

POINT CameraManager::ReviseRelativePosition(POINT ptF)
{
	POINT tmp = mcCurrentCamera->GetAbsPos();
	return PointMake(ptF.x - tmp.x, ptF.y - tmp.y);
}

ISOMETRIC CameraManager::ReviseRelativePosition(ISOMETRIC iso)
{
	RECT tmp = mcCurrentCamera->GetRect();
	return MoveIsometric(iso, tmp);
}

void CameraManager::OffsetXY(int x, int y)
{
	if (!mbIsFocusOn) {
		mcCurrentCamera->OffsetXY(x, y);
	}
}

void CameraManager::OffsetDrag(POINT start, POINT end)
{
	mcCurrentCamera->OffsetDrag(start, end);
}

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}
