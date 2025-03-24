#ifndef ___ROTATE_ANGLE_DETECT__CLASS
#define ___ROTATE_ANGLE_DETECT__CLASS

#include "SensorMonitor.hpp"
#include "RotateAngleCorrect.hpp"

namespace debrisys {

class RotateAngleDetect {
private:
    const SensorMonitor* mRollV;
    const RotateAngleCorrect* mAngCorr;

    float mRotateAngle;
    float mRolla;
    float mRollv;
    static constexpr float mTIME = 0.01;
    static constexpr float mCOFF = 1.309324702;

    void integrate();
    void calcRotateAngle();

public:
    RotateAngleDetect(const SensorMonitor* rollv, const RotateAngleCorrect* angcorr)
        : mRollV(rollv), mAngCorr(angcorr), mRotateAngle(0)
    {
        ;
    }

    float detectRotateAngle();

};  // class RotateAngleDetect

}   // namespace debrisys

#endif // ___ROTATE_ANGLE_DETECT__CLASS
