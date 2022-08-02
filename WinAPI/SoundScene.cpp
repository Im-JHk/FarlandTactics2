#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{
	return S_OK;
}

void SoundScene::release(void)
{
}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		SOUNDMANAGER->play(msCurrBGM, 0.5f);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		SOUNDMANAGER->stop(msCurrBGM);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		SOUNDMANAGER->pause(msCurrBGM);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		SOUNDMANAGER->resume(msCurrBGM);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
		for (auto iter = mlBGM.begin(); iter != mlBGM.end();) {
			SOUNDMANAGER->stop(msCurrBGM);
			if (msCurrBGM == (*iter)) {
				msCurrBGM = *(++iter);
				SOUNDMANAGER->play(msCurrBGM, 0.2f);
				break;
			}
			else ++iter;
		}
	}

	SOUNDMANAGER->update();
}

void SoundScene::render(void)
{
	IMAGEMANAGER->render("BG1", getMemDC());
}
