#include "Stdafx.h"
#include "Unit.h"

//HRESULT Unit::init(string name, eDirection dir, POINT pos, POINT rowcol, int index, bool isMovable)
//{
//	return E_NOTIMPL;
//}
//
//void Unit::release(void)
//{
//}
//
//void Unit::update(void)
//{
//}
//
//void Unit::render(void)
//{
//}
//
//POINT Unit::CalcDeltaXY(eDirection dir)
//{
//	switch (dir)
//	{
//	case eDirection::LEFT:
//		return PointMake(-2, -1);
//		break;
//	case eDirection::RIGHT:
//		return PointMake(2, 1);
//		break;
//	case eDirection::UP:
//		return PointMake(2, -1);
//		break;
//	case eDirection::DOWN:
//		return PointMake(-2, 1);
//		break;
//	}
//}
//
//void Unit::CalcDamage(int value, bool type)
//{
//	miFinalDamage = 0;
//	if (atkType == eAttackType::NORMAL) {
//		if (value - miDeffence < 1) miFinalDamage = 1;
//		else miFinalDamage = value - miDeffence;
//	}
//	else if (atkType == eAttackType::SPELL) {
//		if (value - miMGDeffence < 1) miFinalDamage = 1;
//		else miFinalDamage = value - miMGDeffence;
//	}
//}
//
//bool Unit::Damaged(int value, bool type)
//{
//	miCurrHp -= miFinalDamage;
//	cout << "damage: " << miFinalDamage << "/ hp: " << miCurrHp << endl;
//	if (miCurrHp <= 0) {
//		miCurrHp = 0;
//		return true;
//	}
//	return false;
//}
