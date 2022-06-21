#include "Stdafx.h"
#include "ScriptManager.h"

HRESULT ScriptManager::init(void)
{
	miStage = 0;
	miCurrScriptCount = 0;
	miCurrTextCount = 0;
	mfTextTime = 0;
	mbIsPlayText = false;
	mbIsBoxUp = true;
	mbIsConversationStart = false;
	mbIsConversationEnd = false;

	return S_OK;
}

void ScriptManager::release(void)
{
	for (int i = 0; i < mvScript.size(); i++) {
		SAFE_DELETE(mvScript[i]);
	}
	ClearScript();
}

void ScriptManager::update(void)
{
	if (mbIsPlayText) {
		if (mfTextTime + 0.1f < TIMEMANAGER->getWorldTime()) {
			miCurrTextCount += 1;
			if (strlen(mvScript[miCurrScriptCount]->GetScript().c_str()) <= miCurrTextCount) {
				miCurrTextCount = strlen(mvScript[miCurrScriptCount]->GetScript().c_str());
				mbIsPlayText = false;
			}
			mfTextTime = TIMEMANAGER->getWorldTime();
		}
	}
	else if (mbIsConversationStart) {
		if (miCurrScriptCount >= mvScript.size() - 1) {
			mbIsConversationEnd = true;
		}
	}
}

void ScriptManager::render(HDC hdc)
{
	ShowScript(hdc);
}

bool ScriptManager::GetIsExceedMax()
{
	if (miCurrScriptCount >= mvScript.size() - 1) return true;
	return false;
}

void ScriptManager::SetNextScript()
{
	miCurrScriptCount++;
	miCurrTextCount = 0;
	mbIsPlayText = true;
	mbIsBoxUp ? mbIsBoxUp = false : mbIsBoxUp = true;
}

void ScriptManager::SetPlayText(bool b)
{
	mfTextTime = TIMEMANAGER->getWorldTime();
	mbIsPlayText = b;
	mbIsConversationStart = true;
}

void ScriptManager::LoadScript(int stage)
{
	char cStr[256];
	string str = "script_stage_1";
	str += ".json";
	strcpy_s(cStr, str.c_str());

	Json::Value root = JSONDATAMANAGER->loadJsonFile(cStr);
	
	miStage = root["stage"].isInt();
	if (root["script_array"].isArray()) {
		for (auto iter = root["script_array"].begin(); iter != root["script_array"].end(); ++iter) {
			Script* script = new Script;
			script->init((*iter)["name"].asString(), (*iter)["script"].asString());
			mvScript.push_back(script);
		}
	}
	miCurrScriptCount = 0;
	miCurrTextCount = 0;
}

void ScriptManager::ShowScript(HDC hdc)
{
	if (mbIsBoxUp) {
		IMAGEMANAGER->render("msg_box", hdc, 20, 30);
		IMAGEMANAGER->render(mvScript[miCurrScriptCount]->GetName() + "_up", hdc, 40, 0);
		FONTMANAGER->drawTextFromString(hdc, 300, 50, "Kostar", 15, 700, mvScript[miCurrScriptCount]->GetScript(), miCurrTextCount, 24, RGB(255, 255, 255));
	}
	else {
		IMAGEMANAGER->render("msg_box", hdc, 20, WINSIZE_Y - 180);
		IMAGEMANAGER->render(mvScript[miCurrScriptCount]->GetName() + "_down", hdc, WINSIZE_X - 280, WINSIZE_Y - 192);
		FONTMANAGER->drawTextFromString(hdc, 50, WINSIZE_Y - 150, "Kostar", 15, 700, mvScript[miCurrScriptCount]->GetScript(), miCurrTextCount, 24, RGB(255, 255, 255));
	}
}

void ScriptManager::ClearScript()
{
	mvScript.clear();
}
