#pragma once
#include "SingletonBase.h"

//������ ���� ��� ���̺귯��
//PlaySound()�� ����ϱ� ����
#include <mmsystem.h>
//mciSendString()�� ����ϱ� ����
//mci: Media Control Interface (��ġ������)
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib") //mm= ��Ƽ �̵��

class TempSoundManager : public SingletonBase <TempSoundManager>
{
public:
	HRESULT init();
	void addMp3FileWithKey(string key, string fileName);
	void addWaveileWithKey(string key, string fileName);
	void playEffectSoundWave(char* fileName);
	void playSoundWithKey(string key);
	void stopMp3WithKey(string key);


	TempSoundManager() {}
	~TempSoundManager() {}
};

