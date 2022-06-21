#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;


SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

// 죽은 친구
DWORD CALLBACK loadingThread(LPVOID prc)
{
	// 교체될 씬의 함수 실행
	SceneManager::_readyScene->init();

	// 현재 씬을 교체될 씬으로 변경
	SceneManager::_currentScene = SceneManager::_readyScene;

	// 로딩 씬 해제
	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = nullptr;
	SceneManager::_readyScene = nullptr;

	return 0;
}

HRESULT SceneManager::init(void)
{
	_currentScene = nullptr;
	_loadingScene = nullptr;
	_readyScene = nullptr;

	return S_OK;
}

void SceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	// 로딩 씬 -> 교체 대기 중인 씬 -> 현재 씬
	// 4개 이상 (스타트 씬, 게임 씬, 상점 씬, 보스 씬, 엔딩 씬)
	// 많지 않다

	// for (0) or while (0) or do ~ while
	// 데이터 만개 이상

	for (; miSceneList != _mSceneList.end();) {
		if (miSceneList->second != nullptr) {
			if (miSceneList->second == _currentScene) {
				miSceneList->second->release();
			}
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}
	_mSceneList.clear();
}

void SceneManager::update(void)
{
	// 현재 씬이 존재하면 현재 씬만 갱신
	if (_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	// 현재 씬이 존재하면 현재 씬만 렌더
	if (_currentScene) _currentScene->render();
}

//씬 추가
GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	// 씬이 없다면 리턴
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

GameNode * SceneManager::addLoadingScene(string loadingSceneName, GameNode * scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(loadingSceneName, scene));
	return scene;
}

GameNode * SceneManager::addReadyScene(string readySceneName, GameNode * scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(readySceneName, scene));
	return scene;
}

HRESULT SceneManager::changeScene(string sceneName)
{
	// 변경하려고 하는 씬을 찾는다
	mapSceneIter find = _mSceneList.find(sceneName);
	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init())) {
		_currentScene = find->second;
		return S_OK;
	}
	return E_NOTIMPL;
}