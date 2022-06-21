#pragma once
#include "GameNode.h"

class EndingScene : public GameNode
{
private:
	Button* mcButton;

	float mfBgAlpha;
	float mfTitleAlpha;
	bool mbIsBGAlphaIncrese;
	bool mbIsTitleAlphaIncrese;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void ChangeNextScene();

	EndingScene() {}
	~EndingScene() {}
};

