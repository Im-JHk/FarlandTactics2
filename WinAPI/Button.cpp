#include "Stdafx.h"
#include "Button.h"

HRESULT Button::init(void)
{
	return S_OK;
}

HRESULT Button::init(const char* keyName, const char* text, string ImageName, eButtonShapeType shape, POINT center, POINT size)
{
	meEvent = eMouseEventType::NONE;
	mbIsVisible = false;
	mbIsEnable = false;

	msImageName = ImageName;
	if (ImageName != "") mcImage = IMAGEMANAGER->findImage(ImageName);

	msKeyName = keyName;
	msText = text;
	meShape = shape;
	mtCenter = center;
	mtSize = size;
	if (meShape == eButtonShapeType::RECTANGLE) mtRect = RectMakeCenter(center.x, center.y, size.x, size.y);
	else mtIsometric = MakeIsometric(center, size);
	miFrameX = 0;

	return S_OK;
}

void Button::release(void)
{
}

void Button::update(void)
{
}

void Button::render(void)
{
	if (mbIsVisible) {
		if (meShape == eButtonShapeType::RECTANGLE) {

			mcImage->frameRender(getMemDC(), mtRect.left, mtRect.top, miFrameX, 0);
			if (msImageName == "button") {
				FONTMANAGER->drawText_C(getMemDC(), mtCenter.x - ButtonTextGap * strlen(msText), mtCenter.y - ButtonSize * 0.5, "Kostar", ButtonSize, 700, msText, strlen(msText), RGB(25, 25, 25));
			}
			else if (msImageName == "button_small") {
				FONTMANAGER->drawText_C(getMemDC(), mtCenter.x - ButtonSmallTextGap * strlen(msText), mtCenter.y - ButtonSmallSize * 0.5, "Kostar", ButtonSmallSize, 700, msText, strlen(msText), RGB(25, 25, 25));
			}
			else if (msImageName != "") mcImage->render(getMemDC(), mtRect.left, mtRect.top);
		}
		else DrawIsometric(getMemDC(), mtIsometric);
	}
}

void Button::ButtonNone()
{
	meEvent = eMouseEventType::NONE;
	miFrameX = 0;
}

void Button::ButtonOver()
{
	meEvent = eMouseEventType::OVER;
	miFrameX = 1;
	auto iter = mmCbVoidFuncInt.find("over");
	if (iter != mmCbVoidFuncInt.end()) iter->second(GetIndex());
}

void Button::ButtonDown()
{
	meEvent = eMouseEventType::DOWN;
	miFrameX = 2;
}

void Button::ButtonUp()
{
	meEvent = eMouseEventType::UP;
	miFrameX = 0;
}

void Button::ButtonClick()
{
	meEvent = eMouseEventType::CLICK;
	miFrameX = 0;
	auto iter = mmCbVoidFuncVoid.find(msKeyName);
	if (iter != mmCbVoidFuncVoid.end()) iter->second();
}

void Button::ButtonClick(char* key)
{
	meEvent = eMouseEventType::CLICK;
	miFrameX = 0;
	auto iter1 = mmCbVoidFuncVoid.find(key);
	if (iter1 != mmCbVoidFuncVoid.end()) {
		iter1->second();
	}
	auto iter2 = mmCbVoidFuncInt.find(key);
	if (iter2 != mmCbVoidFuncInt.end()) {
		iter2->second(GetIndex());
	}
}

void Button::Offset(POINT pt)
{
	mtCenter = pt;
	if (meShape == eButtonShapeType::RECTANGLE) mtRect = RectMakeCenter(mtCenter.x, mtCenter.y, mtSize.x, mtSize.y);
	else mtIsometric = MakeIsometric(mtCenter, mtSize);
}
