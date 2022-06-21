#include "Stdafx.h"
#include "TownScene.h"
#include "Button.h"

HRESULT TownScene::init(void)
{
	mfBgAlpha = 0;
	mbIsAlphaIncrese = true;

	Button* button = new Button;
	button->init("guild", 0, "guild_button", eButtonShapeType::RECTANGLE, PointMake(323, 196), PointMake(54, 32));
	button->RegistVoidFuncAsVoid("guild", std::bind(&TownScene::ChangeSceneGuild, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mtSelect1 = button;
	MOUSEMANAGER->AddButton(button);

	button = new Button;
	button->init("outside", 0, "outside_button", eButtonShapeType::RECTANGLE, PointMake(569, 56), PointMake(74, 32));
	button->RegistVoidFuncAsVoid("outside", std::bind(&TownScene::ChangeSceneBattle, this));
	if (EVENTMANAGER->GetIsOutSideOpen()) {
		button->SetEnable(true);
		button->SetVisible(true);
	}
	else {
		button->SetEnable(false);
		button->SetVisible(false);
	}
	mtSelect2 = button;
	MOUSEMANAGER->AddButton(button);

	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);

	return S_OK;
}

void TownScene::release(void)
{
	SAFE_DELETE(mtSelect1);
	SAFE_DELETE(mtSelect2);
}

void TownScene::update(void)
{
	if (mbIsAlphaIncrese) {
		mfBgAlpha += 3.f;
		if (mfBgAlpha >= 255) {
			mfBgAlpha = 255;
			mbIsAlphaIncrese = false;
		}
	}
}

void TownScene::render(void)
{
	IMAGEMANAGER->alphaRender("town", getMemDC(), 0, 0, mfBgAlpha);
	mtSelect1->render();
	mtSelect2->render();

	if (KEYMANAGER->isOnceKeyDown(VK_F3)) {
		Rectangle(getMemDC(), mtSelect1->GetRect().left, mtSelect1->GetRect().top, mtSelect1->GetRect().right, mtSelect1->GetRect().bottom);
		Rectangle(getMemDC(), mtSelect2->GetRect().left, mtSelect2->GetRect().top, mtSelect2->GetRect().right, mtSelect2->GetRect().bottom);
	}
}

void TownScene::ChangeSceneGuild()
{
	this->release();
	MOUSEMANAGER->release();
	SCENEMANAGER->changeScene("Guild");
}

void TownScene::ChangeSceneBattle()
{
	this->release();
	MOUSEMANAGER->release();
	SCENEMANAGER->changeScene("Battle");
}
