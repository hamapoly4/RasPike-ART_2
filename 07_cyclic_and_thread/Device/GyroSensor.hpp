#ifndef ___GYROSENSOR__CLASS
#define ___GYROSENSOR__CLASS

extern "C" {

#include "spike/hub/imu.h"

}

/* ジャイロセンサ */
class GyroSensor {
public:
    /*----------------------------------------------------------------
    *  関数名  ：  コンストラクタ
    *  概要    ：  IMUドライバを初期化する
    *  引数    ：  なし
    *  返り値  ：
    ------------------------------------------------------------------*/
    GyroSensor();

    /*----------------------------------------------------------------
    *  関数名  ：  getAngularVelocity
    *  概要    ：  角速度を取得する
    *  引数    ：  x/y/z軸の角速度を格納するためのfloat配列[°/s]
    *  返り値  ：  なし
    ------------------------------------------------------------------*/
    void getAngularVelocity(float angv[3]);

};

#endif // ___GYROSENSOR__CLASS
