#include <stdio.h>
#include "RollAngle.hpp"

RollAngle::RollAngle()
	: rollangle(0)
{
	;
}

int RollAngle::getRollAngle(float vel, int8_t msec)
{
	sec = static_cast<float>(msec * 0.001);
	rollangle += (vel * sec + offset) * coff;
	return static_cast<int>(rollangle);
}

void RollAngle::resetRollAngle()
{
	rollangle = 0;
}
