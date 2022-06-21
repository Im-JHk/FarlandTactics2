#include "Stdafx.h"
#include "StartScene.h"
#include "Button.h"

HRESULT StartScene::init(void)
{
	mfBgAlpha = 0;
	mbIsAlphaIncrese = true;

	Button* button = new Button;
	button->init("start_scene", "", "", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X / 2, WINSIZE_Y /2), PointMake(WINSIZE_X, WINSIZE_Y));
	button->RegistVoidFuncAsVoid("start_scene", std::bind(&StartScene::ChangeNextScene, this));
	button->SetEnable(true);
	button->SetVisible(false);
	mcButton = button;
	MOUSEMANAGER->AddButton(button);

	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);

	return S_OK;
}

void StartScene::release(void)
{
	SAFE_DELETE(mcButton);
}

void StartScene::update(void)
{
	if (mbIsAlphaIncrese) {
		mfBgAlpha += 3.f;
		if (mfBgAlpha >= 255) {
			mfBgAlpha = 255;
			mbIsAlphaIncrese = false;
		}
	}
}

void StartScene::render(void)
{
	IMAGEMANAGER->alphaRender("title", getMemDC(), 0, 0, mfBgAlpha);
}

void StartScene::ChangeNextScene()
{
	this->release();
	MOUSEMANAGER->release();
	SCENEMANAGER->changeScene("Select");
}
