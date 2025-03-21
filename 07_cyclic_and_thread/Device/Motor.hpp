#ifndef ___MOTOR__CLASS
#define ___MOTOR__CLASS

/* g++でコンパイルするときCリンケージを教える */
extern "C" {

#include "pbio/port.h"
#include "spike/pup/motor.h"

}


/* モータクラス */
class Motor {
public:
    /*----------------------------------------------------------------
    *  関数名  ：  コンストラクタ
    *  概要    ：  モータの初期化
    *  引数    ：  ポートID、回転方向（時計回りor反時計回り）
    *  返り値  ：
    ------------------------------------------------------------------*/
    Motor(pbio_port_id_t motor_port, pup_direction_t positive_direction);

    /*----------------------------------------------------------------
    *  関数名  ：  デストラクタ
    *  概要    ：  モータを止める
    *  引数    ：  なし
    *  返り値  ：
    ------------------------------------------------------------------*/
    ~Motor();

    /*----------------------------------------------------------------
    *  関数名  ：  resetCount
    *  概要    ：  エンコーダ値のリセット
    *  引数    ：  なし
    *  返り値  ：  なし
    ------------------------------------------------------------------*/
    void resetCount();

    /*----------------------------------------------------------------
    *  関数名  ：  getCount
    *  概要    ：  エンコーダ値の取得
    *  引数    ：  なし
    *  返り値  ：  エンコーダ値
    ------------------------------------------------------------------*/
    int32_t getCount();

    /*----------------------------------------------------------------
    *  関数名  ：  setPower
    *  概要    ：  パワー値の設定
    *  引数    ：  パワー値
    *  返り値  ：  なし
    ------------------------------------------------------------------*/
    void setPower(int power);

    /*----------------------------------------------------------------
    *  関数名  ：  stop
    *  概要    ：  モータを止める
    *  引数    ：  なし
    *  返り値  ：  なし
    ------------------------------------------------------------------*/
    void stop();

private:
    static const int8_t POWER_MAX = 100;    // パワー値の最大
    static const int8_t POWER_MIN = -100;   // パワー値の最小   

    pup_motor_t* devptr;    // デバイスポインタ
    int mPower;             // パワー値

};

#endif // ___MOTOR__CLASS
