#ifndef ___MOTOR_CLASS
#define ___MOTOR_CLASS

/* g++でコンパイルするときCリンケージを教える */
#ifdef __cplusplus
extern "C" {
#endif

#include "pbio/port.h"
#include "spike/pup/motor.h"

#ifdef __cplusplus
}
#endif


/* モータクラス */
class Motor {
public:
    /*-------------------------------------------------------------------------------
    *  関数名  ：  コンストラクタ
    *  概要    ：  モータの初期化
    *  引数    ：  ポートID、回転方向（時計回りor反時計回り）、エンコーダ値のリセットの有無
    *  返り値  ：
    ---------------------------------------------------------------------------------*/
    Motor(pbio_port_id_t motor_port, pup_direction_t 
			positive_direction, bool reset_count);

    /* エンコーダ値のリセット */
    void resetCount();

    /* エンコーダ値の取得 */
    int32_t getCount();

    /* 回転速度の取得 */
    int32_t getSpeed();

    /* 回転速度の設定 */
    void setSpeed(int speed);

    /* パワー値の取得 */
    int32_t getPower();

    /* パワー値の設定 */
    void setPower(int power);

    /* モータを止める */
    void stop();

    /* ブレーキをかけてモータを止める */
    void brake();

    /* モータを止めて角度を維持する */
    void hold();

    /* モータがストールしているか調べる */
    bool isStalled();

    /* モータのデューティー値を下げる */
    int32_t setDutyLimit(int duty_limit);

    /* モータのデューティー値を元に戻す */
    void restoreDutyLimit(int old_value);

private:
    static const int8_t POWER_MAX = 100;    // パワー値の最大
    static const int8_t POWER_MIN = -100;   // パワー値の最小   
    static const int8_t DUTY_MAX = 100      // デューティー値の最大
    static const int8_t DUTY_MIN = 0;       // デューティー値の最小

    pup_motor_t* devptr;    // デバイスポインタ
    int mPower;             // パワー値

};

#endif // ___MOTOR_CLASS
