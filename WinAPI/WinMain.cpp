#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE _hInstance;
HWND _hWnd;
HWND _popUpWnd;
HWND _dlgWnd;
POINT _ptMouse = { 0, 0 };
//Graphics _graphic;
//Pen _bkPen;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK PopUpProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BtnProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	ULONG_PTR gpToken;
	GdiplusStartupInput gpSI;
	if (GdiplusStartup(&gpToken, &gpSI, NULL) != Ok) return 0;

	_mg = new MainGame();
	_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	wndClass.lpfnWndProc = (WNDPROC)PopUpProc;
	wndClass.lpszClassName = "PopUpWindow";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	DEVMODE dm;

	//ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmBitsPerPel = 32;		//32비트 트루컬러
	dm.dmPelsWidth = 1980;		//가로 해상도
	dm.dmPelsHeight = 1020;		//세로 해상도
	dm.dmDisplayFrequency = 60;	//재생빈도

	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

#else

	_hWnd = CreateWindow
	(
		WINNAME,
		WINNAME,
		WINSTYLE,
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);	

#endif

	ShowWindow(_hWnd, nCmdShow);
	if (FAILED(_mg->init()))
	{
		return 0;
	}

	MSG message;
	
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}
	}

	_mg->release();
	UnregisterClass("PopUpWindow", hInstance);
	UnregisterClass(WINNAME, hInstance);
	GdiplusShutdown(gpToken);
	return (int)message.wParam;
}

//! 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
	//HDC hdc;
	//PAINTSTRUCT ps;

	//switch (iMessage)
	//{
	//case WM_MOUSEMOVE:
	//	_ptMouse.x = LOWORD(lParam);
	//	_ptMouse.y = HIWORD(lParam);
	//	break;
	//case WM_RBUTTONUP:
	//	cout << "o" << endl;
	//	DialogBox(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
	//case WM_KEYDOWN:
	//	switch (wParam)
	//	{
	//	case VK_ESCAPE:
	//		PostMessage(hWnd, WM_DESTROY, 0, 0);
	//		break;
	//	}
	//	break;
	//case WM_DESTROY:
	//	PostQuitMessage(0);
	//	return 0;
	//}
	//return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK PopUpProc(HWND hPop, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//DialogBox(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, DlgProc);
	return _mg->PopUpProc(hPop, iMessage, wParam, lParam);
}

LRESULT CALLBACK BtnProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->BtnProc(hWnd, iMessage, wParam, lParam);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->DlgProc(hDlg, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}