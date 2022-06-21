#pragma once
#include "SingletonBase.h"
#include "Camera.h"

class Object;

class CameraManager : public SingletonBase <CameraManager>
{
private:
	Camera* mcCamera;
	Camera* mcCurrentCamera;

	Object* mcFocusRef;

	POINT mtDragStart;
	POINT mtFocusPoint;
	bool mbIsDragOn;
	bool mbIsFocusOn;
	bool mbIsCameraMoveOn;
public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void ChangeCamera(Camera* camera);
	POINT ReviseRelativePosition(POINT ptF);
	ISOMETRIC ReviseRelativePosition(ISOMETRIC iso);

	RECT GetCameraRect(void) { return mcCurrentCamera->GetRect(); }
	POINT GetCameraPos(void) { return mcCurrentCamera->GetAbsPos(); }
	POINT GetCameraCenter(void) { return mcCurrentCamera->GetCenter(); }
	POINT GetDragStart(void) { return mtDragStart; }
	POINT GetFocusPoint(void) { return mtFocusPoint; }
	bool GetDragOn(void) { return mbIsDragOn; }
	bool GetFocusOn(void) { return mbIsFocusOn; }
	bool GetMoveOn(void) { return mbIsCameraMoveOn; }

	void SetDragStart(int x, int y) { mtDragStart = PointMake(x, y); }
	void SetDragOn(bool b) { mbIsDragOn = b; }
	void SetFocusOff() { mcFocusRef = nullptr; mbIsFocusOn = false; }
	void SetFocus(Object* obj, bool b) { mcFocusRef = obj; mbIsFocusOn = b; }
	void SetFocusRef(Object* obj) { mcFocusRef = obj; }
	void SetFocusPoint(POINT pos) { mtFocusPoint = pos; }
	void SetFocusOn(bool b) { mbIsFocusOn = b; }
	void SetMoveOn(bool b) { mbIsCameraMoveOn = b; }

	void OffsetXY(int x, int y);
	void OffsetDrag(POINT ptF);
	void OffsetDrag(POINT start, POINT end);

	CameraManager();
	~CameraManager();
};

