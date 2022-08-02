#pragma once
#include <SDKDDKver.h>

#include <Windows.h>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "lib/FMOD/fmodex_vc.lib")
#pragma comment(lib, "Jsoncpp/lib_json/json_vc71_libmtd.lib")

#include <Gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#include "inc/FMOD/fmod.hpp"
#include "Jsoncpp/include/json/json.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#include <assert.h>
#include <atlconv.h>

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
#define EFFECTMANAGER EffectManager::getSingleton()
#define EVENTMANAGER EventManager::getSingleton()
#define MOUSEMANAGER MouseManager::getSingleton()
#define SCRIPTMANAGER ScriptManager::getSingleton()

#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))


#ifdef FULLSCREEN
#define WINSTART_X	 1920
#define WINSTART_Y	 0
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

#define CENTER_X	WINSIZE_X / 2
#define CENTER_Y	WINSIZE_Y / 2

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern HWND			_popUpWnd;
extern HWND			_dlgWnd;
extern POINT		_ptMouse;