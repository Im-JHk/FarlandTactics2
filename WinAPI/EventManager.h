#pragma once
#include "SingletonBase.h"

class EventManager : public SingletonBase <EventManager>
{
private:
	eSelectableType meSelectble;
	eSelectPhase mePhase;

	vector<pair<string, PAIR_F>> mlEvent;
	vector<pair<string, PAIR_F>>::iterator mliEvent;
	float mfDeltaTime;
	float mfDuration;

	bool mbIsOutsideOpen;
public:
	HRESULT init(void);
	void update(void);

	eSelectableType GetSelectable() { return meSelectble; }
	eSelectPhase GetPhase() { return mePhase; }
	bool GetIsOutSideOpen() { return mbIsOutsideOpen; }

	void SetSelectable(eSelectableType phase) { meSelectble = phase; }
	void SetPhase(eSelectPhase phase) { mePhase = phase; }
	void SetIsOutSideOpen(bool b) { mbIsOutsideOpen = b; }

	void AddEvent(string key, float runtime);

	void DeleteEvent();

	EventManager() {}
	~EventManager() {}
};

