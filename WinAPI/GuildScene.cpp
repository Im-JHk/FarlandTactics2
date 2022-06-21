#include "Stdafx.h"
#include "GuildScene.h"
#include "Button.h"

HRESULT GuildScene::init(void)
{
	mfBgAlpha = 0;
	miTextBufferCount = 0;
	mfTextTime = 0;
	mbIsAlphaIncrese = true;
	mbIsTextDirUp = true;

	Button* button = new Button;
	button->init("guild", "", "", eButtonShapeType::RECTANGLE, PointMake(WINSIZE_X / 2, WINSIZE_Y / 2), PointMake(WINSIZE_X, WINSIZE_Y));
	button->RegistVoidFuncAsVoid("guild", std::bind(&GuildScene::ShowNextDialogue, this));
	button->SetEnable(true);
	button->SetVisible(false);
	mcButton = button;
	MOUSEMANAGER->AddButton(button);

	SCRIPTMANAGER->init();
	SCRIPTMANAGER->LoadScript(1);

	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);

	return S_OK;
}

void GuildScene::release(void)
{
	SAFE_DELETE(mcButton);
}

void GuildScene::update(void)
{
	if (mbIsAlphaIncrese) {
		mfBgAlpha += 3.f;
		if (mfBgAlpha >= 255) {
			mfBgAlpha = 255;
			mbIsAlphaIncrese = false;
		}
	}
	else {
		if (!SCRIPTMANAGER->GetIsConversationStart()) {
			SCRIPTMANAGER->SetPlayText(true);
		}
		SCRIPTMANAGER->update();
	}
}

void GuildScene::render(void)
{
	IMAGEMANAGER->alphaRender("guild", getMemDC(), 0, 0, mfBgAlpha);
	
	if (!mbIsAlphaIncrese) {
		SCRIPTMANAGER->render(getMemDC());
	}
}

void GuildScene::ShowNextDialogue()
{
	if (SCRIPTMANAGER->GetIsConversationStart()) {
		if (!SCRIPTMANAGER->GetIsPlayText()) {
			if (SCRIPTMANAGER->GetIsConversationEnd()) {
				ChangeNextScene();
			}
			else if(!SCRIPTMANAGER->GetIsExceedMax()) {
				SCRIPTMANAGER->SetNextScript();
			}
		}
		else SCRIPTMANAGER->SetCountMax();
	}
}

void GuildScene::ChangeNextScene()
{
	this->release();
	MOUSEMANAGER->release();
	SCRIPTMANAGER->release();
	EVENTMANAGER->SetIsOutSideOpen(true);
	SCENEMANAGER->changeScene("Town");
}
