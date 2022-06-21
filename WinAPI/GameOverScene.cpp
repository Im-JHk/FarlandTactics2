#include "Stdafx.h"
#include "GameOverScene.h"
#include "Button.h"

HRESULT GameOverScene::init(void)
{
	mfBgAlpha = 0;
	mbIsAlphaIncrese = true;

	Button* button = new Button;
	button->init("game_over", "", "", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X / 2, WINSIZE_Y / 2), PointMake(WINSIZE_X, WINSIZE_Y));
	button->RegistVoidFuncAsVoid("game_over", std::bind(&GameOverScene::ChangeNextScene, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mcButton = button;
	MOUSEMANAGER->AddButton(button);

	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);

	return S_OK;
}

void GameOverScene::release(void)
{
	SAFE_DELETE(mcButton);
}

void GameOverScene::update(void)
{
	if (mbIsAlphaIncrese) {
		mfBgAlpha += 3.f;
		if (mfBgAlpha >= 255) {
			mfBgAlpha = 255;
			mbIsAlphaIncrese = false;
		}
	}
}

void GameOverScene::render(void)
{
	IMAGEMANAGER->alphaRender("game_over", getMemDC(), 0, 0, mfBgAlpha);
}

void GameOverScene::ChangeNextScene()
{
	this->release();
	MOUSEMANAGER->release();
	EVENTMANAGER->SetIsOutSideOpen(false);
	SCENEMANAGER->changeScene("Start");
}