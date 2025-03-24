#include "Motor.hpp"

/*======================コンストラクタ======================*/

Motor::Motor(pbio_port_id_t motor_port, pup_direction_t positive_direction)
{
    devptr = pup_motor_get_device(motor_port);
    pup_motor_setup(devptr, positive_direction, true);
    pup_motor_reset_count(devptr);
}

/*======================デストラクタ======================*/
Motor::~Motor()
{
    pup_motor_stop(devptr);
}

/*======================エンコーダ値のリセット======================*/

void Motor::resetCount()
{
    pup_motor_reset_count(devptr);
}

/*======================エンコーダ値の取得======================*/

int32_t Motor::getCount()
{
    return pup_motor_get_count(devptr);
}

/*======================パワー値の設定======================*/

void Motor::setPower(int power)
{
    mPower = (power > POWER_MAX) ? POWER_MAX : ((power < POWER_MIN) ? POWER_MIN : power);
    pup_motor_set_power(devptr, power);
}

/*======================モータを止める======================*/

void Motor::stop()
{
    pup_motor_stop(devptr);
}
