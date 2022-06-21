#include "Stdafx.h"
#include "Player.h"
#include "Tile.h"

HRESULT Player::init(string name, eDirection dir, eState state, POINT pos, POINT rowcol, POINT currHpMp, POINT maxHpMp, POINT atk, POINT def, int index, bool isDie)
{
	Object::init(name, dir, pos, rowcol, index, true);
	meCurrState = state;
	mtCurrFrame = { 0,0 };
	miMaxHp = maxHpMp.x;
	miMaxMp = maxHpMp.y;
	miCurrHp = currHpMp.x;
	miCurrMp = currHpMp.y;
	miAttack = atk.x;
	miMagic = atk.y;
	miDeffence = def.x;
	miMGDeffence = def.y;
	miFinalDamage = 0;

	mElapsedTime = 0;
	mFrameUpdateTime = 1.f / 8.f;
	mDeltaTime = TIMEMANAGER->getElapsedTime();

	mbIsShowOn = false;
	if (isDie) {
		mbIsCanMove = false;
		mbIsCanAttack = false;
	}
	else {
		mbIsCanMove = true;
		mbIsCanAttack = true;
	}
	mbIsDamaged = false;
	mbIsDie = isDie;

	return S_OK;
}

HRESULT Player::init(string name, eDirection dir, POINT pos, POINT rowcol, int index, bool isMovable)
{
	Object::init(name, dir, pos, rowcol, index, isMovable);
	meCurrState = eState::IDLE;
	mtCurrFrame = { 0,0 };
	miMaxHp = miCurrHp = 70;
	miMaxMp = miCurrMp = 50;
	miAttack = 30;
	miMagic = 45;
	miDeffence = 25;
	miMGDeffence = 20;
	miFinalDamage = 0;

	mElapsedTime = 0;
	mFrameUpdateTime = 1.f / 5.f;
	mDeltaTime = TIMEMANAGER->getElapsedTime();

	mbIsShowOn = false;
	mbIsCanMove = true;
	mbIsCanAttack = true;
	mbIsDamaged = false;
	mbIsDie = false;

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	mDeltaTime = TIMEMANAGER->getElapsedTime();
	Animation();
}

void Player::render(RECT cameraRect)
{
	switch (meCurrState)
	{
	case eState::IDLE:
		IMAGEMANAGER->frameRender(GetName() + "_idle", getMemDC(), mtAbsPoint.x - 50 - cameraRect.left, mtAbsPoint.y - 80 - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y);
		break;
	case eState::MOVE:
		IMAGEMANAGER->frameRender(GetName() + "_move", getMemDC(), mtAbsPoint.x - 50 - cameraRect.left, mtAbsPoint.y - 80 - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y);
		break;
	case eState::SPELL:
		IMAGEMANAGER->frameRender(GetName() + "_spell", getMemDC(), mtAbsPoint.x - 50 - cameraRect.left, mtAbsPoint.y - 80 - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y);
		break;
	case eState::DAMAGE:
		IMAGEMANAGER->frameRender(GetName() + "_damage", getMemDC(), mtAbsPoint.x - 50 - cameraRect.left, mtAbsPoint.y - 80 - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y);
		break;
	case eState::DEATH:
		IMAGEMANAGER->frameRender(GetName() + "_death", getMemDC(), mtAbsPoint.x - 50 - cameraRect.left, mtAbsPoint.y - 80 - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y);
		break;
	}

	if (mbIsShowOn) {
		for (auto iter : mvInfoBox) {
			if (iter.first == "xy") IMAGEMANAGER->render("info_box", getMemDC(), iter.second.x, iter.second.y);
			else if (iter.first == "image") IMAGEMANAGER->frameRender(mstrName + "_idle", getMemDC(), iter.second.x, iter.second.y, 0, 3);
			else if (iter.first == "hpbar") {
				IMAGEMANAGER->render("wall", getMemDC(), iter.second.x, iter.second.y, 0, 194, miMaxHp / 2, MaxHpMpHeight);
				IMAGEMANAGER->render("wall", getMemDC(), iter.second.x, iter.second.y, 0, 178, miCurrHp / 2, MaxHpMpHeight);
			}
			else if (iter.first == "mpbar") {
				IMAGEMANAGER->render("wall", getMemDC(), iter.second.x, iter.second.y, 160, 178, miMaxMp / 2, MaxHpMpHeight);
				IMAGEMANAGER->render("wall", getMemDC(), iter.second.x, iter.second.y, 160, 162, miCurrMp / 2, MaxHpMpHeight);
			}
		}
	}
}

bool Player::Move(Tile* prevTile, Tile* nextTile, eDirection dir)
{
	meDir = dir;
	if (SetOffset(nextTile->GetCenter(), CalcDeltaXY(dir), nextTile->GetIndex())) {
		return true;
	}
	return false;
}

void Player::Animation(void)
{
	mElapsedTime += mDeltaTime;

	if (mElapsedTime >= mFrameUpdateTime) {
		mElapsedTime = 0;
		mtCurrFrame.x += 1;
		switch (meCurrState)
		{
		case eState::IDLE:
			if (mtCurrFrame.x > IMAGEMANAGER->findImage(GetName() + "_idle")->getMaxFrameX()) mtCurrFrame.x = 0;
			break;
		case eState::MOVE:
			if (mtCurrFrame.x > IMAGEMANAGER->findImage(GetName() + "_move")->getMaxFrameX()) mtCurrFrame.x = 0;
			break;
		case eState::ATTACK:
			if (mtCurrFrame.x > IMAGEMANAGER->findImage(GetName() + "_attack")->getMaxFrameX()) mtCurrFrame.x = 0;
			break;
		case eState::DAMAGE:
			mtCurrFrame.x -= 1;
			if (mtCurrFrame.x > IMAGEMANAGER->findImage(GetName() + "_damage")->getMaxFrameX()) mtCurrFrame.x = 0;
			break;
		case eState::DEATH:
			if (mtCurrFrame.x > IMAGEMANAGER->findImage(GetName() + "_death")->getMaxFrameX()) mtCurrFrame.x = 0;
			break;
		}
		
		switch (meDir)
		{
		case eDirection::LEFT:
			mtCurrFrame.y = 0;
			break;
		case eDirection::RIGHT:
			mtCurrFrame.y = 1;
			break;
		case eDirection::UP:
			mtCurrFrame.y = 2;
			break;
		case eDirection::DOWN:
			mtCurrFrame.y = 3;
			break;
		}
	}
}

POINT Player::CalcDeltaXY(eDirection dir)
{
	switch (dir)
	{
	case eDirection::LEFT:
		return PointMake(-2, -1);
		break;
	case eDirection::RIGHT:
		return PointMake(2, 1);
		break;
	case eDirection::UP:
		return PointMake(2, -1);
		break;
	case eDirection::DOWN:
		return PointMake(-2, 1);
		break;
	}
}

void Player::CalcDamage(eAttackType atkType, int value)
{
	miFinalDamage = 0;
	if (atkType == eAttackType::NORMAL) {
		if (value - miDeffence < 1) miFinalDamage = 1;
		else miFinalDamage = value - miDeffence;
	}
	else if (atkType == eAttackType::SPELL) {
		if (value - miMGDeffence < 1) miFinalDamage = 1;
		else miFinalDamage = value - miMGDeffence;
	}
}

int Player::Damaged(void)
{
	int prevHp = miCurrHp;
	miCurrHp -= miFinalDamage;
	if (miCurrHp < 0) {
		miCurrHp = 0;
		mbIsDie = true;
		meCurrState = eState::DEATH;
	}
	cout << "hp: " << miCurrHp << endl;
	if (prevHp > miFinalDamage) return miFinalDamage;
	else return prevHp;
}

void Player::ShowInfomation()
{
	mbIsShowOn = true;
	mvInfoBox.push_back(make_pair("xy", PointMake(10, WINSIZE_Y - 138)));
	mvInfoBox.push_back(make_pair("image", PointMake(20, WINSIZE_Y - 128)));
	mvInfoBox.push_back(make_pair("name", PointMake(70, WINSIZE_Y - 128)));
	mvInfoBox.push_back(make_pair("hpbar", PointMake(150, WINSIZE_Y - 100)));
	mvInfoBox.push_back(make_pair("mpbar", PointMake(150, WINSIZE_Y - 60)));
}

Player::Player()
{
}

Player::~Player()
{
}
