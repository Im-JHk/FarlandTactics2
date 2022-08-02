#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		setlocale(LC_ALL, "Korean");
		SetTimer(_hWnd, 1, 10, NULL);
		
		KEYMANAGER->init();
		
		RND->init();
		
		IMAGEMANAGER->init();
		
		TIMEMANAGER->init();
		
		TEXTDATAMANAGER->init();

		SCENEMANAGER->init();

		SOUNDMANAGER->init();

		JSONDATAMANAGER->init();

		CAMERAMANAGER->init();

		PLAYERMANAGER->init();

		EFFECTMANAGER->init();

		EVENTMANAGER->init();

		MOUSEMANAGER->init();

		SCRIPTMANAGER->init();
	}
	return S_OK;
}

void GameNode::release()
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();
		RND->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		
		FONTMANAGER->releaseSingleton();
		
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		JSONDATAMANAGER->release();
		JSONDATAMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		PLAYERMANAGER->release();
		PLAYERMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		EVENTMANAGER->releaseSingleton();

		MOUSEMANAGER->releaseSingleton();

		SCRIPTMANAGER->release();
		SCRIPTMANAGER->releaseSingleton();
	}
	ReleaseDC(_popUpWnd, _popDC);
	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch (iMessage)
	{
	case WM_CHAR:
		if (KEYMANAGER->GetBufferOn()) {
			KEYMANAGER->SetKeyBuffer(wParam);
		}
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONDOWN:
		MOUSEMANAGER->MouseLButtonDown(_ptMouse.x, _ptMouse.y);
		break;
	case WM_LBUTTONUP:
		MOUSEMANAGER->MouseLButtonUp(_ptMouse.x, _ptMouse.y);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT GameNode::PopUpProc(HWND hPop, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:

	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hPop, &ps);
		this->render();
		EndPaint(hPop, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		cout << "pop del" << endl;
		break;
	}
	return (DefWindowProc(hPop, iMessage, wParam, lParam));
}

LRESULT GameNode::BtnProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

BOOL GameNode::DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		cout << "dialog" << endl;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			break;
		}
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_CLOSE:
		DestroyWindow(hDlg);
	case WM_DESTROY:
		break;
	}
	return FALSE;
}
