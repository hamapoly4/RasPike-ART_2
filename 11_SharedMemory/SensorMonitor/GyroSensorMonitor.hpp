#ifndef ___GYROSENSOR_MONITOR__CLASS
#define ___GYROSENSOR_MONITOR__CLASS

#include "SensorMonitor.hpp"
#include "GyroSensor.hpp"

namespace debrisys {

class GyroSensorMonitor : public SensorMonitor {
private:
    /* インスタンス */
    GyroSensor& mAngV;      // 3軸角速度

    /* 属性 */
    float mAngv[3];   // 3軸角速度

public:
    /* コンストラクタ */
    GyroSensorMonitor(GyroSensor& angv)
        : mAngV(angv)
    {
        ;
    }

    /* センシングする */
    void sensing()
    {
        mAngV.getAngularVelocity(mAngv);    // 3軸角速度を取得
    }

    /* データを読み取る */
    float readData() const
    {
        return mAngv[0];    // ロール角を返却
    }

    /* 初期化する */
    void init() const
    {
        ;   // 何も処理しない
    }

};  // class GyroSensorMonitor

}   // namespace debrisys

#endif // ___GYROSENSOR_MONITOR__CLASS
