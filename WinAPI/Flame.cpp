#include "Stdafx.h"
#include "Flame.h"

HRESULT Flame::init(const char* fileName, float* x, float* y)
{
	_image = IMAGEMANAGER->addFrameImage("Flame", "Resources/Images/Object/Flame.BMP", 0.0f, 0.0f, 432, 297, 9, 1, true, RGB(255, 0, 255));

	_x = x;
	_y = y;
	_rc = RectMakeCenter(*_x, *_y, _image->getFrameWidth(), _image->getFrameHeight());
	_flameTick = 7.0f;

	return S_OK;
}

void Flame::release(void)
{
}

void Flame::update(void)
{
	if (FLAME_COUNT + _flameTick <= GetTickCount()) {
		_flameTick = GetTickCount();
		_image->setFrameX(_image->getFrameX() + 1);

		if (_image->getFrameX() >= _image->getMaxFrameX()) {
			_image->setFrameX(0);
		}
	}

	_rc = RectMakeCenter(*_x, *_y + 220, _image->getFrameWidth(), _image->getFrameHeight());
}

void Flame::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY());
}

Flame::Flame()
{
}

Flame::~Flame()
{
}
