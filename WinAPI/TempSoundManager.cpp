#include "Stdafx.h"
#include "TempSoundManager.h"

HRESULT TempSoundManager::init()
{
	return S_OK;
}

void TempSoundManager::addMp3FileWithKey(string key, string fileName)
{
	string first = "open \ ";
	string end = "\ type mpegvideo alias ";
	string finalQuery = first + fileName + end + key;

	const char* str = finalQuery.c_str();
	//cout << finalQuery << endl;

	//	mciSendString(): 현재 장치에 명령어를 전송하여 필요한 장치를 구동시키는 함수
	//	문자열 명령어, 반환값 문자열, 반환될 길이, 핸들 콜백
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::addWaveileWithKey(string key, string fileName)
{
	string first = "open \"";
	string end = "\ type waveaudio alias ";
	string finalQuery = first + fileName + end + key;

	const char* str = finalQuery.c_str();

	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
	//파일이름.wavk , 핸들(NULL->파일명을 사용한다)
	//SND_ASYNC: 재생하면서 다음 코드 실행(비동기적으로 작동하라는 플래그)
	PlaySound(fileName, NULL, SND_ASYNC);
}

void TempSoundManager::playSoundWithKey(string key)
{
	string first = "play ";
	string finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}	

void TempSoundManager::stopMp3WithKey(string key)
{
	string first = "stop ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}
