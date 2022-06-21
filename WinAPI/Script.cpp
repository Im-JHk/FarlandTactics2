#include "Stdafx.h"
#include "Script.h"

HRESULT Script::init(string name, string script)
{
	msName = name;
	msScript = script;

	return S_OK;
}

void Script::release(void)
{
}

void Script::update(void)
{
}

void Script::render(void)
{
}
