#pragma once
#include "GameNode.h"

class SoundScene : public GameNode
{
private:
	string msCurrBGM;
	list<string> mlBGM;
	vector<string> mvBGM;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};