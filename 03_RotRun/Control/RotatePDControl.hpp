#ifndef ___ROTATE_PD_CONTROL__CLASS
#define ___ROTATE_PD_CONTROL__CLASS

#include <cstdint>
#include "Control.hpp"
#include "SensorMonitor.hpp"

namespace debrisys {

class RotatePDControl : public Control {
private:
    SensorMonitor* mLeftCount;
    SensorMonitor* mRightCount;

    float mOldDiff;
    static constexpr float mPGAIN = 1.5;
    static constexpr float mDGAIN = 1.5;
    float mPvalue;
    float mDvalue;

    void calcP();
    void calcD();

public:
    RotatePDControl(SensorMonitor* leftcount, SensorMonitor* rightcount)
        : mLeftCount(leftcount), mRightCount(rightcount), mOldDiff(0)
    {
        ;
    }

    int8_t getTurn();

};  // class RotatePDControl

}   // namespace debrisys

#endif // ___ROTATE_PD_CONTROL__CLASS
