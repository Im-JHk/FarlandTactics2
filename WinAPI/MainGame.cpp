#include "Stdafx.h"
#include "MainGame.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "MapToolScene.h"
#include "TownScene.h"
#include "GuildScene.h"
#include "BattleScene.h"
#include "GameOverScene.h"
#include "EndingScene.h"
#include "SoundScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	SCENEMANAGER->addScene("Start", new StartScene);
	SCENEMANAGER->addScene("Select", new SelectScene);
	SCENEMANAGER->addScene("MapTool", new MapToolScene);
	SCENEMANAGER->addScene("Town", new TownScene);
	SCENEMANAGER->addScene("Guild", new GuildScene);
	SCENEMANAGER->addScene("Battle", new BattleScene);
	SCENEMANAGER->addScene("GameOver", new GameOverScene);
	SCENEMANAGER->addScene("Ending", new EndingScene);

	SCENEMANAGER->addScene("Sound", new SoundScene);

	SCENEMANAGER->changeScene("Start");

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();
	SCENEMANAGER->update();
	CAMERAMANAGER->update();
	MOUSEMANAGER->update(_ptMouse.x, _ptMouse.y);
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	this->getBackBuffer()->render(getHDC());
}

