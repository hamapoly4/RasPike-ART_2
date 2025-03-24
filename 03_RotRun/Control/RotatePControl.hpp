#ifndef ___ROTATE_P_CONTROL__CLASS
#define ___ROTATE_P_CONTROL__CLASS

#include <cstdint>
#include <cmath>
#include "Control.hpp"
#include "RotateAngleDetect.hpp"

namespace debrisys {

class RotatePControl : public Control {
private:
    RotateAngleDetect* mConAng;

    float mTargetAngle;
    float mAngle;
    static constexpr float mPGAIN = 0.15;
    float mPvalue;

    void calcP();

public:
    RotatePControl(RotateAngleDetect* con_ang, float tager_angle)
        : mConAng(con_ang), mTargetAngle(tager_angle)
    {
        ;
    }

    int8_t getTurn();

};  // class Control

}   // namespace debrisys

#endif // ___ROTATE_P_CONTROL__CLASS
