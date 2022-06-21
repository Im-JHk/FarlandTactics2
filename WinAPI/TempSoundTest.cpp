#include "Stdafx.h"
#include "TempSoundTest.h"

HRESULT TempSoundTest::init(void)
{
	TEMPSOUNDMANAGER->addMp3FileWithKey("찬란", "Resources/Sounds/Final.mp3");
	//TEMPSOUNDMANAGER->addMp3FileWithKey("문체부", "Resources/Sounds/Main.mp3");

	return S_OK;
}

void TempSoundTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		TEMPSOUNDMANAGER->playSoundWithKey("찬란");
		//TEMPSOUNDMANAGER->playSoundWithKey("문체부");
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		//TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sounds/test.wav");
	}
}
