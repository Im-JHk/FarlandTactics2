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
	// ���� �ý��� ����
	System_Create(&_system);

	// �ý��� �ʱ�ȭ
	_system->init(totalSoundChannel, FMOD_INIT_NORMAL, 0);

	// ä�� �� ��ŭ �޸𸮿� ��
	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel*[totalSoundChannel];

	// �޸� �ѹ� ����
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
	// ���� �ý��� ������Ʈ
	// �� ������ �ٲ�ų� ����� ���� ���带 ä�ο��� ���µ� �پ��� �۾��� �ڵ����� �Ѵ�
	_system->update();
}

void SoundManager::addSound(string keyName, string soundName, bool backGround, bool loop)
{
	if (loop)
	{
		if (backGround)
		{
			//���� �̸�, ���带 ���� ���� �ɼ�, �ǵ��(�����ڿ��� ���尡 ����Ǵ� ���� ������ �����Ұų�? (0 or NULL), 
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			//���� ����� �ʿ��� ũ������Ʈ���尡 �����°Ŵ�
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		//FMOD_DEFAULT: �ѹ� �÷���
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
			// ���� �÷���
			// _sound[count] -> ������, 
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);
			// �� 2�� �̻��� ���尡 ����Ǹ� 2��°���� ��ĥ�Ŵ�
		//	_system->playSound(FMOD_CHANNEL_FREE, _sound[(*iter)->second], false, &_channel[count]);

			// ���� ����
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