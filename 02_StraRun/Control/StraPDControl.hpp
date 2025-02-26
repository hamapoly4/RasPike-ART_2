#ifndef ___STRA_PD_CONTROL__CLASS
#define ___STRA_PD_CONTROL__CLASS

#include <cstdint>
#include "Control.hpp"
#include "SensorMonitor.hpp"

namespace debrisys {

class StraPDControl : public Control {
private:
    SensorMonitor* mLeftCount;
    SensorMonitor* mRightCount;

    float mOldDiff;
    float mLeftcount;
    float mRightcount;
    static constexpr float mPGAIN = 1.5;
    static constexpr float mDGAIN = 1.5;
    float mPvalue;
    float mDvalue;

    void calcP();
    void calcD();

public:
    StraPDControl(SensorMonitor* leftcount, SensorMonitor* rightcount)
        : mLeftCount(leftcount), mRightCount(rightcount), mOldDiff(0)
    {
        ;
    }

    int8_t getTurn();

};  // class StraControl

}   // namespace debrisys

#endif // ___STRA_PD_CONTROL__CLASS
