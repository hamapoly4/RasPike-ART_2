#ifndef ___INIT_MOTOR__CLASS
#define ___INIT_MOTOR__CLASS

#include "SensorMonitor.hpp"
#include "Motor.hpp"

namespace debrisys {

class InitMotor {
private:
    SensorMonitor* mLeftCount;
    SensorMonitor* mRightCount;
    Motor& mLeftMotor;
    Motor& mRightMotor;

    bool mFinFlag;
    bool mStopFlag;

public:
    InitMotor(SensorMonitor* leftcount, SensorMonitor* rightcount,
                                    Motor& leftmotor, Motor& rightmotor)
        : mLeftCount(leftcount), mRightCount(rightcount), mLeftMotor(leftmotor),
                                    mRightMotor(rightmotor), mFinFlag(false), mStopFlag(true)
    {
        ;
    }

    void init();

    bool checkFinFlag() const
    {
        return mFinFlag;
    }

};  // class InitMotor

}   // namespace debrisys

#endif // ___INIT_MOTOR__CLASS
