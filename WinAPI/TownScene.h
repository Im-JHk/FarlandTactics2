#pragma once
#include "GameNode.h"

class TownScene : public GameNode
{
private:
	Button* mtSelect1;
	Button* mtSelect2;

	float mfBgAlpha;
	bool mbIsAlphaIncrese;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void ChangeSceneGuild();
	void ChangeSceneBattle();

	TownScene() {}
	~TownScene() {}
};

