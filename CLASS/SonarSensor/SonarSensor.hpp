#ifndef ___SONAR_SENSOR_CLASS
#define ___SONAR_SENSOR_CLASS

/* g++でコンパイルするときCリンケージを教える */
#ifdef __cplusplus
extern "C" {
#endif

#include "spike/pup/ultrasonicsensor.h"

#ifdef __cplusplus
}
#endif

class SonarSensor {
public:
    /*----------------------------------------------------------------
    *  関数名  ：  コンストラクタ
    *  概要    ：  ポートの割り当て
    *  引数    ：  ポートID
    *  返り値  ：
    ------------------------------------------------------------------*/
    SonarSensor(pbio_port_id_t sonar_port);

    /*----------------------------------------------------------------
    *  関数名  ：  getDistance
    *  概要    ：  距離を測定する
    *  引数    ：  なし
    *  返り値  ：  距離（単位：mm）
    ------------------------------------------------------------------*/
    int32_t getDistance();

private:
    pup_device_t* devptr;     // デバイスポインタ

};

#endif // ___SONAR_SENSOR_CLASS