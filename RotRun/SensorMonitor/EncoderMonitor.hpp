#ifndef ___ENCODER_MONITOR__CLASS
#define ___ENCODER_MONITOR__CLASS

#include <cstdint>
#include "SensorMonitor.hpp"
#include "Motor.hpp"

namespace debrisys {

class EncoderMonitor : public SensorMonitor {
private:
    const Motor& mMotorEncoder;
    int32_t mCount;

public:
    EncoderMonitor(const Motor& motorencoder)
        : mMotorEncoder(motorencoder)
    {
        ;
    }

    void sensing()
    {
        mCount = mMotorEncoder.getCount();
    }

    void readData() const
    {
        return mCount;
    }

    void init() const
    {
        mMotorEncoder.resetCount();
    }

};  // class EncoderMonitor

}   // namespace debrisys

#endif // ___ENCODER_MONITOR__CLASS
