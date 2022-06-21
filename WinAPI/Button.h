#pragma once
#include "GameNode.h"

class Button : public GameNode
{
protected:
	ImageBase* mcImage;
	string msImageName;
	const char* msKeyName;
	const char* msText;

	eButtonShapeType meShape;
	eMouseEventType meEvent;

	POINT mtCenter;
	POINT mtSize;
	RECT mtRect;
	ISOMETRIC mtIsometric;

	int miFrameX;

	bool mbIsVisible;
	bool mbIsEnable;
protected:
	map<string, VoidEventAsVoid> mmCbVoidFuncVoid;
	map<string, VoidEventAsInt> mmCbVoidFuncInt;
public:
	virtual HRESULT init(void);
	virtual HRESULT init(const char* keyName, const char* text, string ImageName, eButtonShapeType shape, POINT pos, POINT size);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void ButtonNone();
	void ButtonOver();
	void ButtonDown();
	void ButtonUp();
	void ButtonClick();
	void ButtonClick(char* key);

	virtual int GetIndex() { return 0; };
	Button* GetButtonRef() { return this; }
	eButtonShapeType GetShape() { return meShape; }
	POINT GetCenter() { return mtCenter; }
	POINT GetSize() { return mtSize; }
	RECT GetRect() { return mtRect; }
	ISOMETRIC GetIsometric() { return mtIsometric; }
	const char* GetKeyName() { return msKeyName; }
	bool GetVisible() { return mbIsVisible; }
	bool GetEnable() { return mbIsEnable; }

	void SetVisible(bool b) { mbIsVisible = b; }
	void SetEnable(bool b) { mbIsEnable = b; }
	void SetIsometric(ISOMETRIC iso) { mtIsometric = iso; }

	void Offset(POINT pt);

	void RegistVoidFuncAsVoid(string key, VoidEventAsVoid ev) { mmCbVoidFuncVoid.insert({ key, std::move(ev) }); }
	void RegistVoidFuncAsInt(string key, VoidEventAsInt ev) { mmCbVoidFuncInt.insert({ key, std::move(ev) }); }

	Button() {}
	virtual ~Button() {}
};

