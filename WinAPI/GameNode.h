#pragma once
#include "ImageBase.h"

static ImageBase* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

static BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

class GameNode
{
private:
	HDC _hdc;
	HDC _popDC;
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	ImageBase* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC(){ return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }
	HDC getPopDC() { return _popDC; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	LRESULT PopUpProc(HWND hPop, UINT iMessage, WPARAM wParam, LPARAM lParam);
	LRESULT BtnProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	static BOOL DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);


	GameNode() {}
	virtual ~GameNode() {}
};

