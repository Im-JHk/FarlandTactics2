#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr),
							   _channel(nullptr),
							   _sound(nullptr)
{
}

SoundManager::~SoundManager()
{
}


HRESULT SoundManager::init(void)
{
	// 사운드 시스템 생성
	System_Create(&_system);

	// 시스템 초기화
	_system->init(totalSoundChannel, FMOD_INIT_NORMAL, 0);

	// 채널 수 만큼 메모리에 할
	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel*[totalSoundChannel];

	// 메모리 한번 밀자
	memset(_sound, 0, sizeof(Sound*) * (totalSoundChannel));
	memset(_channel, 0, sizeof(Channel*) * (totalSoundChannel));

	return S_OK;
}

void SoundManager::release(void)
{
	if (_channel != nullptr || _sound != nullptr) {
		for (int i = 0; i < totalSoundChannel; i++) {
			if (_channel != nullptr) {
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != nullptr) {
				if (_sound != nullptr) _sound[i]->release();
			}
		}
	}

	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	if (_system != nullptr) {
		_system->release();
		_system->close();
	}
}

void SoundManager::update(void)
{
	// 사운드 시스템 업데이트
	// ㄴ 볼륨이 바뀌거나 재생이 끝난 사운드를 채널에서 빼는등 다양한 작업을 자동으로 한다
	_system->update();
}

void SoundManager::addSound(string keyName, string soundName, bool backGround, bool loop)
{
	if (loop)
	{
		if (backGround)
		{
			//파일 이름, 사운드를 열기 위한 옵션, 피드백(개발자에게 사운드가 재생되는 동안 정보를 제공할거냐? (0 or NULL), 
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			//동시 재생이 필요해 크리에이트사운드가 들어오는거다
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		//FMOD_DEFAULT: 한번 플레이
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void SoundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++) {
		if (keyName == iter->first) {
			// 사운드 플레이
			// _sound[count] -> 논리오류, 
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);
			// ㄴ 2개 이상의 사운드가 재생되면 2번째부터 놓칠거다
		//	_system->playSound(FMOD_CHANNEL_FREE, _sound[(*iter)->second], false, &_channel[count]);

			// 볼륨 설정
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void SoundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++) {
		if (keyName == iter->first) {
			_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++) {
		if (keyName == iter->first) {
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++) {
		if (keyName == iter->first) {
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;

	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++) {
		if (keyName == iter->first) {
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;

	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++) {
		if (keyName == iter->first) {
			_channel[count]->isPlaying(&isPause);
			break;
		}
	}
	return isPause;
}