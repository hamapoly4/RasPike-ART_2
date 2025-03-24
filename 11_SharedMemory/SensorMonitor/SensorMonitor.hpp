#ifndef ___SENSOR_MONITOR__CLASS
#define ___SENSOR_MONITOR__CLASS

namespace debrisys {

class SensorMonitor {
protected:
    SensorMonitor() // コンストラクタ
    {
        ;
    }

public:
    virtual void  sensing()         = 0;    // センシングする
    virtual float readData() const  = 0;    // データを読み取る
    virtual void  init()     const  = 0;    // 初期化する

};  // class SensorMonitor

}   // namespace debrisys

#endif // ___SENSOR_MONITOR__CLASS
