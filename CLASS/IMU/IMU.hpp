#ifndef ___IMU_CLASS
#define ___IMU_CLASS

#ifdef __cplusplus
extern "C" {
#endif

#include "spike/hub/imu.h"

#ifdef __cplusplus
}
#endif

class IMU {
public:
    /*----------------------------------------------------------------
    *  関数名  ：  コンストラクタ
    *  概要    ：  IMUドライバを初期化する
    *  引数    ：  なし
    *  返り値  ：
    ------------------------------------------------------------------*/
    IMU();

    /*----------------------------------------------------------------
    *  関数名  ：  getAcceleration
    *  概要    ：  加速度を取得する
    *  引数    ：  x/y/z軸の加速度を格納するためのfloat配列[mm/s^2]
    *  返り値  ：  なし
    ------------------------------------------------------------------*/
    void getAcceleration(float accel[3]);

    /*----------------------------------------------------------------
    *  関数名  ：  getAngularVelocity
    *  概要    ：  角速度を取得する
    *  引数    ：  x/y/z軸の角速度を格納するためのfloat配列[°/s]
    *  返り値  ：  なし
    ------------------------------------------------------------------*/
    void getAngularVelocity(float angv[3]);

};

#endif // ___IMU_CLASS
