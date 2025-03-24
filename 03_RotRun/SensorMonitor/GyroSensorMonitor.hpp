#ifndef ___GYROSENSOR_MONITOR__CLASS
#define ___GYROSENSOR_MONITOR__CLASS

#include "SensorMonitor.hpp"
#include "GyroSensor.hpp"

namespace debrisys {

class GyroSensorMonitor : public SensorMonitor {
private:
    GyroSensor& mAngV;
    float mAngv[3];

public:
    GyroSensorMonitor(GyroSensor& angv)
        : mAngV(angv)
    {
        ;
    }

    void sensing()
    {
        mAngV.getAngularVelocity(mAngv);
    }

    float readData() const
    {
        return mAngv[0];
    }

    void init() const
    {
        ;
    }

};  // class GyroSensorMonitor

}   // namespace debrisys

#endif // ___GYROSENSOR_MONITOR__CLASS
