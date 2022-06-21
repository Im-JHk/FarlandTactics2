#pragma once
//==============================================================
//# Utils # (����ȭ ��Ű�� ���� ����, Ȥ�� ������ ��ɵ��� ��Ƶа�)
//==============================================================

/*
class Utils
{
public:
	Utils();
	~Utils();
};
*/

// ��׸� 1���� ���� ��
#define DEG_TO_RAD		0.017453f
#define PI				3.141592653f
#define PI_2			6.283185308f
//#define PI_2 (PI * 2) <- �� PI_2�� �����ѵ� �ε� �Ҽ��� ���� ��꿡���� ���꺸�� ������� ����

// ���� + ������ ������
#define FLOAT_EPSILON		0.001f	//2D���� �� ��ȸ ����, 3D���� ���� ����
// �Ǽ��� ���������� ��ȯ
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)
// �� �Ǽ��� ������ ��
// �� fabs�� �Ҽ��� ���� ���밪 ��ȯ / �ڸ�ǰ (abs -> int)
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	// �� �� ������ �Ÿ��� ���Ѵ�
	float getDistance(float startX, float startY, float endX, float endY);
	// Start���� End������ ���� Radian���� ���Ѵ�
	float getAngle(float startX, float startY, float endX, float endY);
}