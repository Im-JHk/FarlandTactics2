#include "Stdafx.h"
#include "SelectScene.h"
#include "Button.h"

HRESULT SelectScene::init(void)
{
	Button* button = new Button;
	button->init("map_tool", "Map Tool", "button", eButtonShapeType::RECTANGLE, PointMake(100, 200), PointMake(100, 50));
	button->RegistVoidFuncAsVoid("map_tool", std::bind(&SelectScene::ChangeSceneMapTool, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mtSelect1 = button;
	MOUSEMANAGER->AddButton(button);

	button = new Button;
	button->init("town", "Game Start", "button", eButtonShapeType::RECTANGLE, PointMake(100, 300), PointMake(100, 50));
	button->RegistVoidFuncAsVoid("town", std::bind(&SelectScene::ChangeSceneTown, this));
	button->SetEnable(true);
	button->SetVisible(true);
	mtSelect2 = button;
	MOUSEMANAGER->AddButton(button);

	EVENTMANAGER->SetPhase(eSelectPhase::BUTTON_SELECT);

	return S_OK;
}

void SelectScene::release(void)
{
	SAFE_DELETE(mtSelect1);
	SAFE_DELETE(mtSelect2);
}

void SelectScene::update(void)
{
}

void SelectScene::render(void)
{
	IMAGEMANAGER->render("select", getMemDC(), 0, 0);
	mtSelect1->render();
	mtSelect2->render();
}

void SelectScene::ChangeSceneMapTool()
{
	this->release();
	MOUSEMANAGER->release();
	SCENEMANAGER->changeScene("MapTool");
}

void SelectScene::ChangeSceneTown()
{
	this->release();
	MOUSEMANAGER->release();
	SCENEMANAGER->changeScene("Town");
}