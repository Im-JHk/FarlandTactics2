#pragma once
//==============================================================
//# Utils # (간소화 시키고 싶은 로직, 혹은 수학적 기능들을 모아둔곳)
//==============================================================

/*
class Utils
{
public:
	Utils();
	~Utils();
};
*/

// 디그리 1도의 라디안 값
#define DEG_TO_RAD		0.017453f
#define PI				3.141592653f
#define PI_2			6.283185308f
//#define PI_2 (PI * 2) <- 위 PI_2와 같긴한데 부동 소수점 많은 계산에서는 연산보단 상수값이 나음

// 공학 + 수학의 구세주
#define FLOAT_EPSILON		0.001f	//2D에선 볼 기회 적음, 3D에선 많이 쓰임
// 실수를 정수형으로 변환
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)
// 두 실수가 같은지 비교
// ㄴ fabs는 소수점 차의 절대값 반환 / 자매품 (abs -> int)
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	// 두 점 사이의 거리를 구한다
	float getDistance(float startX, float startY, float endX, float endY);
	// Start부터 End까지의 각을 Radian으로 구한다
	float getAngle(float startX, float startY, float endX, float endY);
}