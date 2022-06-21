#include "Stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::init(void)
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		this->setKeyDown(i, false);
		this->setKeyUp(i, false);
	}
	mbIsBufferOn = false;
	return S_OK;
}

bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);
	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}
	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)return true;
	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)return true;
	return false;
}

string KeyManager::GetKeyBuffer()
{
	string str = "";
	int count = 0;
	for (auto iter : mvKeyBuffer) {
		str += iter;
	}
	return str;
}

void KeyManager::SetKeyBuffer(char ch)
{
	if (ch >= 48 && ch <= 57) mvKeyBuffer.push_back(ch);
	else if (ch == 8 && !mvKeyBuffer.empty()) mvKeyBuffer.back();
}
