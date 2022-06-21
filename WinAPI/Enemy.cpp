#include "Stdafx.h"
#include "Enemy.h"
#include "Tile.h"

HRESULT Enemy::init(string name, eDirection dir, eState state, POINT pos, POINT rowcol, POINT currHpMp, POINT maxHpMp, POINT atk, POINT def, int index, bool isDie)
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
	mFrameUpdateTime = 1.f / 5.f;
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

HRESULT Enemy::init(string name, eDirection dir, POINT pos, POINT rowcol, int index, bool isMovable)
{
	Object::init(name, dir, pos, rowcol, index, isMovable);
	meCurrState = eState::IDLE;
	mtCurrFrame = { 0,0 };
	//msTypeName = 
	miMaxHp = miCurrHp = 50;
	miMaxMp = miCurrMp = 20;
	miAttack = 30;
	miMagic = 20;
	miDeffence = 20;
	miMGDeffence = 10;
	miFinalDamage = 0;

	mElapsedTime = 0;
	mFrameUpdateTime = 1.f / 8.f;
	mDeltaTime = TIMEMANAGER->getElapsedTime();

	mbIsShowOn = false;
	mbIsCanMove = true;
	mbIsCanAttack = true;
	mbIsDamaged = false;
	mbIsDie = false;

	return S_OK;
}

void Enemy::release(void)
{
}

void Enemy::update(void)
{
	mDeltaTime = TIMEMANAGER->getElapsedTime();
	Animation();
}

void Enemy::render(RECT cameraRect)
{
	switch (meCurrState)
	{
	case eState::IDLE:
		IMAGEMANAGER->frameRender("rogue1_idle", getMemDC(), mtAbsPoint.x - 50 - cameraRect.left, mtAbsPoint.y - 80 - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y);
		break;
	case eState::MOVE:
		IMAGEMANAGER->frameRender("rogue1_move", getMemDC(), mtAbsPoint.x - 50 - cameraRect.left, mtAbsPoint.y - 80 - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y);
		break;
	case eState::DAMAGE:
		IMAGEMANAGER->frameRender("rogue1_damage", getMemDC(), mtAbsPoint.x - 50 - cameraRect.left, mtAbsPoint.y - 80 - cameraRect.top, mtCurrFrame.x, mtCurrFrame.y);
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

bool Enemy::Move(Tile * prevTile, Tile * nextTile, eDirection dir)
{
	meDir = dir;
	if (SetOffset(nextTile->GetCenter(), CalcDeltaXY(dir), nextTile->GetIndex())) {
		return true;
	}
	return false;
}

void Enemy::Animation(void)
{
	mElapsedTime += mDeltaTime;
	if (mElapsedTime >= mFrameUpdateTime) {
		mElapsedTime = 0;
		mtCurrFrame.x += 1;
		switch (meCurrState)
		{
		case eState::IDLE:
			if (mtCurrFrame.x > IMAGEMANAGER->findImage("rogue1_idle")->getMaxFrameX()) mtCurrFrame.x = 0;
			break;
		case eState::MOVE:
			if (mtCurrFrame.x > IMAGEMANAGER->findImage("rogue1_move")->getMaxFrameX()) mtCurrFrame.x = 0;
			break;
		case eState::ATTACK:
			if (mtCurrFrame.x > IMAGEMANAGER->findImage("rogue1_attack")->getMaxFrameX()) mtCurrFrame.x = 0;
			break;
		case eState::SPELL:
			if (mtCurrFrame.x > IMAGEMANAGER->findImage("rogue1_spell")->getMaxFrameX()) mtCurrFrame.x = 0;
			break;
		case eState::DAMAGE:
			mtCurrFrame.x = 0;
			break;
		case eState::DEATH:
			//if (mtCurrFrame.x > IMAGEMANAGER->findImage("rogue1_death")->getMaxFrameX()) mtCurrFrame.x = 0;
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

POINT Enemy::CalcDeltaXY(eDirection dir)
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

void Enemy::CalcDamage(eAttackType atkType, int value)
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

int Enemy::Damaged(void)
{
	int prevHp = miCurrHp;
	miCurrHp -= miFinalDamage;
	if (miCurrHp < 0) {
		miCurrHp = 0;
		mbIsDie = true;
	}
	cout << "hp: " << miCurrHp << endl;
	if (prevHp > miFinalDamage) return miFinalDamage;
	else return prevHp;
}

void Enemy::ShowInfomation()
{
	mbIsShowOn = true;
	mvInfoBox.push_back(make_pair("xy", PointMake(WINSIZE_X - 330, WINSIZE_Y - 138)));
	mvInfoBox.push_back(make_pair("image", PointMake(WINSIZE_X - 320, WINSIZE_Y - 128)));
	mvInfoBox.push_back(make_pair("name", PointMake(WINSIZE_X - 260, WINSIZE_Y - 128)));
	mvInfoBox.push_back(make_pair("hpbar", PointMake(WINSIZE_X - 180, WINSIZE_Y - 100)));
	mvInfoBox.push_back(make_pair("mpbar", PointMake(WINSIZE_X - 180, WINSIZE_Y - 60)));
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
