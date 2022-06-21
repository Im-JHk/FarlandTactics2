#pragma once
#include <SDKDDKver.h>

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외
//#define WIN32_LEAN_AND_MEAN 

//! Windows 헤더 파일
#include <Windows.h>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "lib/FMOD/fmodex_vc.lib")
#pragma comment(lib, "Jsoncpp/lib_json/json_vc71_libmtd.lib")
//#pragma comment(lib, "Jsoncpp/lib/jsoncpp.lib")

#include <Gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

//! 외부 헤더 파일
#include "inc/FMOD/fmod.hpp"
#include "Jsoncpp/include/json/json.h"
//#include "Jsoncpp/inc/json.h"

//! C 런타임 헤더 파일
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#include <assert.h>
#include <atlconv.h>

//! C++ 런타임 헤더 파일
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <list>
#include <map>
#include <cassert>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

//===================================
// # 내가 만든 헤더파일을 이곳에 추가 #
//===================================
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "TimeManager.h"
#include "Utils.h"
#include "TextDataManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "JsonSaveLoader.h"

#include "DefinedDataType.h"
#include "CameraManager.h"
#include "PlayerManager.h"
#include "EffectManager.h"
#include "EventManager.h"
#include "MouseManager.h"
#include "ScriptManager.h"

using namespace MY_UTIL;


//========================
// # 싱글톤을 이곳에 추가 #
//========================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define JSONDATAMANAGER JsonSaveLoader::getSingleton()

#define CAMERAMANAGER CameraManager::getSingleton()
#define PLAYERMANAGER PlayerManager::getSingleton()
//#define ENEMYMANAGER EnemyManager::getSingleton()
#define EFFECTMANAGER EffectManager::getSingleton()
#define EVENTMANAGER EventManager::getSingleton()
#define MOUSEMANAGER MouseManager::getSingleton()
#define SCRIPTMANAGER ScriptManager::getSingleton()

//============================
// # 매크로 # (윈도우창 초기화)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X	 1920
#define WINSTART_Y	 0
//GetSystemMetrics() : 인자로 전달되는 시스템 설정 정보 반환
//	ㄴSM_CXSCREEN: 현재 화면 해상도 X축 반환
//	ㄴSM_CYSCREEN: 현재 화면 해상도 Y축 반환
#define WINSIZE_X	 GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y	 GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	 WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WINSTART_X	 400
#define WINSTART_Y	 200
#define WINSIZE_X	 640
#define WINSIZE_Y	 480
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU
#endif

//=========================
// # 매크로 # (기능 및 효율)
//=========================
#define CENTER_X	WINSIZE_X / 2
#define CENTER_Y	WINSIZE_Y / 2


//===============================================
// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}


//=============
// # 전역변수 #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern HWND			_popUpWnd;
extern HWND			_dlgWnd;
extern POINT		_ptMouse;