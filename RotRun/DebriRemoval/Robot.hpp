#ifndef ___ROBOT__CLASS
#define ___ROBOT__CLASS

#include <cstdint>
#include "Step.hpp"
#include "SensorMonitor.hpp"

namespace debrisys {

class Robot {
private:
    Step* mStep;
    SensorMonitor* mRollV;
    SensorMonitor* mLeftCount;
    SensorMonitor* mRightCount;

    static const uint8_t mFinalSection = 9;

public:
    Robot(Step* step, SensorMonitor* rollv, SensorMonitor* leftcount, SensorMonitor* rightcount)
        : mStep(step), mRollV(rollv), mLeftCount(leftcount), mRightCount(rightcount)
    {
        ;
    }

    void conquer();

};  // class Robot

}   // namespace debrisys

#endif // ___ROBOT__CLASS
