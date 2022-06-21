#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char * fileName, char * fontName, int fontSize, int fontWidth, char * printString, int length, COLORREF color)
{
}

void FontManager::drawText(HDC hdc, int destX, int destY, char * fontName, int fontSize, int fontWidth, char * printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)

	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOut(hdc, destX, destY, printString, length);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char * fontName, int fontSize, int fontWidth, LPCWSTR printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)

	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOutW(hdc, destX, destY, printString, length);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char * fontName, int fontSize, int fontWidth, LPCWSTR * printStringArr, int length, COLORREF color)
{
	int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);
}

void FontManager::drawText_C(HDC hdc, int destX, int destY, char * fontName, int fontSize, int fontWidth, const char * printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)

	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOut(hdc, destX, destY, printString, length);
	
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawTextFromString(HDC hdc, int destX, int destY, char * fontName, int fontSize, int fontWidth, string printString, int length, int rowLen, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)

	);

	USES_CONVERSION;

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	vector<wstring> vStr;
	wstring wstr = A2W(printString.c_str());
	wstring restStr = wstr.substr(0, length);
	while (restStr.length() > rowLen) {
		wstring cutStr = restStr.substr(0, rowLen);
		vStr.push_back(cutStr);
		restStr = restStr.substr(rowLen);
	}
	vStr.push_back(restStr);

	SetTextColor(hdc, color);
	for (int i = 0; i < vStr.size(); i++) TextOutW(hdc, destX, destY + fontSize * i, vStr[i].c_str(), wcslen(vStr[i].c_str()));

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}
