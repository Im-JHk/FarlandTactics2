#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256
class KeyManager:public SingletonBase <KeyManager>
{
private:
	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;
	
	vector<char> mvKeyBuffer;

	bool mbIsBufferOn;
public:
	HRESULT init(void);
	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }

	string GetKeyBuffer(void);
	bool GetBufferOn(void) { return mbIsBufferOn; }
	void SetBufferOn(bool b) { mbIsBufferOn = b; }
	void SetKeyBuffer(char ch);
	void SubKeyBuffer(void) { if (!mvKeyBuffer.empty()) mvKeyBuffer.back(); }

	KeyManager() {}
	~KeyManager() {}
};

