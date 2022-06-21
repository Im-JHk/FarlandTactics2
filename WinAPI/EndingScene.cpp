#include "Stdafx.h"
#include "EndingScene.h"
#include "Button.h"

HRESULT EndingScene::init(void)
{
	mfBgAlpha = mfTitleAlpha = 0;
	mbIsBGAlphaIncrese = true;
	mbIsTitleAlphaIncrese = false;

	Button* button = new Button;
	button->init("ending", "", "", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X / 2, WINSIZE_Y / 2), PointMake(WINSIZE_X, WINSIZE_Y));
	button->RegistVoidFuncAsVoid("ending", std::bind(&EndingScene::ChangeNextScene, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mcButton = button;
	MOUSEMANAGER->AddButton(button);

	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);

	return S_OK;
}

void EndingScene::release(void)
{
	SAFE_DELETE(mcButton);
}

void EndingScene::update(void)
{
	if (mbIsBGAlphaIncrese) {
		mfBgAlpha += 1.f;
		if (mfBgAlpha >= 255) {
			mfBgAlpha = 255;
			mbIsBGAlphaIncrese = false;
			mbIsTitleAlphaIncrese = true;
		}
	}
	else if (mbIsTitleAlphaIncrese) {
		mfTitleAlpha += 5.f;
		if (mfTitleAlpha >= 255) {
			mfTitleAlpha = 255;
			mbIsTitleAlphaIncrese = false;
		}
	}
}

void EndingScene::render(void)
{
	IMAGEMANAGER->alphaRender("ending", getMemDC(), 0, WINSIZE_Y / 8, mfBgAlpha);
	IMAGEMANAGER->alphaRender("thank_you", getMemDC(), 0, WINSIZE_Y / 4, mfTitleAlpha);
}

void EndingScene::ChangeNextScene()
{
	this->release();
	MOUSEMANAGER->release();
	SCENEMANAGER->changeScene("Start");
}