#include "Stdafx.h"
#include "EventManager.h"

HRESULT EventManager::init(void)
{
	meSelectble = eSelectableType::ALL;
	mePhase = eSelectPhase::ALL;
	mbIsOutsideOpen = false;

	return S_OK;
}

void EventManager::update(void)
{
	mfDeltaTime = TIMEMANAGER->getElapsedTime();
	DeleteEvent();
}

void EventManager::AddEvent(string key, float runtime)
{
	PAIR_F pairF = make_pair(TIMEMANAGER->getWorldTime(), runtime);
	mlEvent.push_back(make_pair(key, pairF));
}

void EventManager::DeleteEvent()
{
	for (mliEvent = mlEvent.begin(); mliEvent != mlEvent.end();) {
		if (mliEvent->second.first + mliEvent->second.second > TIMEMANAGER->getWorldTime()) {
			mliEvent = mlEvent.erase(mliEvent);
		}
		else ++mliEvent;
	}
}
