#pragma once
#include "GameNode.h"

class GameOverScene : public GameNode
{
private:
	Button* mcButton;
	float mfBgAlpha;
	bool mbIsAlphaIncrese;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void ChangeNextScene();

	GameOverScene() {}
	~GameOverScene() {}
};

