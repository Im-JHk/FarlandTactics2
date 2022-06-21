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
		//로케일 설정
		setlocale(LC_ALL, "Korean");

		//타이머 초기화
		SetTimer(_hWnd, 1, 10, NULL);

		//키매니저 초기화
		KEYMANAGER->init();

		//랜덤펑션 초기화
		RND->init();

		//이미지매니저 초기화
		IMAGEMANAGER->init();
		//ReleaseDC(_hWnd, _hdc);

		//임시 사운드
		TEMPSOUNDMANAGER->init();

		TIMEMANAGER->init();

		//텍스트 데이터 매니저 초기화
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
		//타이머 해제
		KillTimer(_hWnd, 1);
		//키매니저 싱글톤 해제
		KEYMANAGER->releaseSingleton();
		//랜덤펑션 싱글톤 해제
		RND->releaseSingleton();

		//이미지매니저 해제, 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		
		//폰트매니저 싱글톤 해제
		FONTMANAGER->releaseSingleton();

		//템프사운드매니저 싱글톤 해제
		TEMPSOUNDMANAGER->releaseSingleton();
		
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		//텍스트 데이터 매니저 해제, 싱글톤 해제
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

		//백버퍼 이미지 해제
		//SAFE_DELETE(_backBuffer);
	}
	//DC 해제
	//SAFE_DELETE(_graphic);
	//SAFE_DELETE(_bkPen);
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
