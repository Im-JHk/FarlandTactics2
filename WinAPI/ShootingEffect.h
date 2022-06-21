#pragma once
#include "GameNode.h"

struct tagEffect
{
	Image* img;
	RECT rc;
	int count;
	float x, y;
};

class MissileEffect : public GameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	MissileEffect();
	~MissileEffect();
};

class BeamEffect : public GameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	BeamEffect();
	~BeamEffect();
};


