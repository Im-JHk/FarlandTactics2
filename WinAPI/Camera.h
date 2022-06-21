#pragma once

class Camera
{
private:
	POINT mtAbsPos;
	POINT mtAbsCenter;
	POINT mtRelPos;
	POINT mtSize;
	RECT mtRect;
public:
	HRESULT init(void);
	void release(void);

	RECT GetRect(void) { return mtRect; }
	POINT GetAbsPos(void) { return mtAbsPos; }
	POINT GetCenter(void) { return mtAbsCenter; }

	void SetCenterRect(void);
	void SetCenterRect(POINT center);

	void OffsetXY(int x, int y);
	void OffsetDrag(POINT start, POINT end);

	Camera() {}
	~Camera() {}
};

