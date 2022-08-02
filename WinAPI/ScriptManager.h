#pragma once
#include "SingletonBase.h"
#include "Script.h"

class ScriptManager : public SingletonBase <ScriptManager>
{
private:
	vector<Script*> mvScript;
	int miStage;
	int miCurrScriptCount;
	int miCurrTextCount;
	float mfTextTime;
	bool mbIsBoxUp;
	bool mbIsPlayText;
	bool mbIsConversationStart;
	bool mbIsConversationEnd;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	string GetCurrScript() { return mvScript[miCurrScriptCount]->GetScript(); }
	bool GetIsPlayText() { return mbIsPlayText; }
	bool GetIsConversationStart() { return mbIsConversationStart; }
	bool GetIsConversationEnd() { return mbIsConversationEnd; }
	bool GetIsExceedMax();

	void SetPlayText(bool b);
	void SetNextScript();
	void SetCountMax() { miCurrTextCount = strlen(mvScript[miCurrScriptCount]->GetScript().c_str()); }

	void LoadScript(int stage);
	void ShowScript(HDC hdc);
	void ClearScript();

	ScriptManager() {}
	~ScriptManager() {}
};