#pragma once
#include "GameNode.h"

class GuildScene : public GameNode
{
private:
	Button* mcButton;

	int miTextBufferCount;

	float mfBgAlpha;
	float mfTextTime;
	bool mbIsAlphaIncrese;
	bool mbIsTextDirUp;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void ShowNextDialogue();
	void ChangeNextScene();

	GuildScene() {}
	~GuildScene() {}
};

