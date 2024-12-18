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
private:
    pup_motor_t* devptr;    // デバイスポインタ

public:
    Motor(pbio_port_id_t motor_port, pup_direction_t 
			positive_direction, bool reset_count);    // コンストラクタ
    void    resetCount();
    int32_t getCount();
    int32_t getSpeed();
    void    setSpeed(int speed);
    int32_t getPower();
    void    setPower(int power);
    void    stop();
    void    brake();
    void    hold();
    bool    isStalled();
    int32_t setDutyLimit(int duty_limit);
    void    restoreDutyLimit(int old_value);

};

#endif // ___MOTOR_CLASS
