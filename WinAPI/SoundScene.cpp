#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{
	IMAGEMANAGER->addImage("BG1", "Resources/Images/BackGround/Eldenring.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("title", "Resources/Images/BackGround/title.bmp", 0, 0, WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("Elden", "Resources/Sounds/BGM/The_Final_Battle.mp3", true, true);

	SOUNDMANAGER->addSound("bg00", "Resources/Sounds/BGM/back/BGM00.mid", true, true);
	SOUNDMANAGER->addSound("bg01", "Resources/Sounds/BGM/bgm01.mid", true, true);
	SOUNDMANAGER->addSound("bg02", "Resources/Sounds/BGM/back/bgm02.mid", true, true);
	SOUNDMANAGER->addSound("bg08", "Resources/Sounds/BGM/back/bgm08.mid", true, true);
	SOUNDMANAGER->addSound("bg09", "Resources/Sounds/BGM/back/bgm09.mid", true, true);
	SOUNDMANAGER->addSound("bg10", "Resources/Sounds/BGM/back/bgm10.mid", true, true);
	SOUNDMANAGER->addSound("bg11", "Resources/Sounds/BGM/bgm11.mid", true, true);
	SOUNDMANAGER->addSound("bg12", "Resources/Sounds/BGM/bgm12.mid", true, true);
	SOUNDMANAGER->addSound("bg13", "Resources/Sounds/BGM/bgm13.mid", true, true);
	SOUNDMANAGER->addSound("bg14", "Resources/Sounds/BGM/bgm14.mid", true, true);
	SOUNDMANAGER->addSound("bg15", "Resources/Sounds/BGM/bgm15.mid", true, true);
	SOUNDMANAGER->addSound("bg16", "Resources/Sounds/BGM/bgm16.mid", true, true);
	SOUNDMANAGER->addSound("bg17", "Resources/Sounds/BGM/bgm17.mid", true, true);
	SOUNDMANAGER->addSound("bg18", "Resources/Sounds/BGM/bgm18.mid", true, true);
	SOUNDMANAGER->addSound("bg19", "Resources/Sounds/BGM/bgm19.mid", true, true);
	SOUNDMANAGER->addSound("bg20", "Resources/Sounds/BGM/bgm20.mid", true, true);
	SOUNDMANAGER->addSound("bg21", "Resources/Sounds/BGM/bgm21.mid", true, true);
	SOUNDMANAGER->addSound("bg22", "Resources/Sounds/BGM/bgm22.mid", true, true);
	SOUNDMANAGER->addSound("bg23", "Resources/Sounds/BGM/bgm23.mid", true, true);
	SOUNDMANAGER->addSound("bg24", "Resources/Sounds/BGM/bgm24.mid", true, true);
	SOUNDMANAGER->addSound("bg99", "Resources/Sounds/BGM/bgm99.mid", true, true);
	mlBGM.push_back("bg00");
	mlBGM.push_back("bg01");
	mlBGM.push_back("bg02");
	mlBGM.push_back("bg08");
	//mlBGM.push_back("bg09");
	mlBGM.push_back("bg10");
	mlBGM.push_back("bg11");
	mlBGM.push_back("bg12");
	mlBGM.push_back("bg13");
	mlBGM.push_back("bg14");
	mlBGM.push_back("bg15");
	mlBGM.push_back("bg16");
	mlBGM.push_back("bg17");
	mlBGM.push_back("bg18");
	mlBGM.push_back("bg19");
	mlBGM.push_back("bg20");
	mlBGM.push_back("bg21");
	mlBGM.push_back("bg22");
	mlBGM.push_back("bg23");
	//mlBGM.push_back("bg24");
	mlBGM.push_back("bg99");

	msCurrBGM = mlBGM.front();

	return S_OK;
}

void SoundScene::release(void)
{
}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		SOUNDMANAGER->play(msCurrBGM, 0.5f);
		cout << "name: " << msCurrBGM << endl;
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
				cout << "name: " << msCurrBGM << endl;
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
