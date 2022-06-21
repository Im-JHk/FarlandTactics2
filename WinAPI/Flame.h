#pragma once
#include "GameNode.h"

#define FLAME_COUNT 4.0f

class Flame : public GameNode
{
private:
	Image* _image;
	RECT _rc;

	float* _x;
	float* _y;
	float _flameTick;
public:
	HRESULT init(const char* fileName, float* x, float* y);
	void release(void);
	void update(void);
	void render(void);

public:

	Flame();
	~Flame();
};

