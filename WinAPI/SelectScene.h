#pragma once
#include "GameNode.h"

class SelectScene : public GameNode
{
private:
	Button* mtSelect1;
	Button* mtSelect2;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void ChangeSceneMapTool();
	void ChangeSceneTown();

	SelectScene() {}
	~SelectScene() {}
};