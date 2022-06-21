#pragma once
class Script
{
private:
	string msName;
	string msScript;
public:
	HRESULT init(string name, string script);
	void release(void);
	void update(void);
	void render(void);

	string GetName() { return msName; }
	string GetScript() { return msScript; }

	Script() {}
	~Script() {}
};

