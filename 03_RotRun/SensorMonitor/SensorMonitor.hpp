#ifndef ___SENSOR_MONITOR__CLASS
#define ___SENSOR_MONITOR__CLASS

namespace debrisys {

class SensorMonitor {
protected:
    SensorMonitor()
    {
        ;
    }

public:
    virtual void sensing() = 0;
    virtual float readData() const = 0;
    virtual void init() const = 0;

};  // class SensorMonitor

}   // namespace debrisys

#endif // ___SENSOR_MONITOR__CLASS
