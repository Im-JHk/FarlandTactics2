#pragma once
#include "SingletonBase.h"
class FontManager : public SingletonBase <FontManager>
{
public:
	void drawText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSize, 
		int fontWidth, char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		char* printString, int length, COLORREF color);

	// LPCWSTR(W) -> wide char -> UniCode
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR* printStringArr, int length, COLORREF color);

	void drawText_C(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		const char* printString, int length, COLORREF color);

	void drawTextFromString(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		string printString, int length, int rowLen, COLORREF color);

	FontManager() {}
	~FontManager() {}
};

