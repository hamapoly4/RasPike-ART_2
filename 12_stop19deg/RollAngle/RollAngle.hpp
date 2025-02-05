#ifndef ___ROLL_ANGLE_CLASS
#define	___ROLL_ANGLE_CLASS

#ifdef __cplusplus
extern "C" {
#endif

#include "ev3api.h"

#ifdef __cplusplus
}
#endif

class RollAngle {
public:
	RollAngle();
	int getRollAngle(float vel, int8_t msec);
	void resetRollAngle();
	
private:
	static constexpr double offset = 0.00076732;
	static constexpr double coff = 1.309324702;
	float sec;
	
	float rollangle;
};

#endif // ___ROLL_ANGLE_CLASS
