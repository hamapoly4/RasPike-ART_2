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

/*======================回転速度の取得======================*/

int32_t Motor::getSpeed()
{
    return pup_motor_get_speed(devptr);
}

/*======================回転速度の設定======================*/

void Motor::setSpeed(int speed)
{
    pup_motor_set_speed(devptr, speed);
}

/*======================パワー値の取得======================*/

int32_t Motor::getPower()
{
    return pup_motor_get_power(devptr);
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

/*======================ブレーキをかけてモータを止める======================*/

void Motor::brake()
{
    pup_motor_brake(devptr);
}

/*======================モータを止めて角度を維持する======================*/

void Motor::hold()
{
    pup_motor_hold(devptr);
}

/*======================モータがストールしているか調べる======================*/

bool Motor::isStalled()
{
    return pup_motor_is_stalled(devptr);
}

/*======================モータのデューティー値を下げる======================*/

int32_t Motor::setDutyLimit(int duty_limit)
{
    return pup_motor_set_duty_limit(devptr, duty_limit);
}

/*======================モータのデューティー値を元に戻す======================*/

void Motor::restoreDutyLimit(int old_value)
{
    pup_motor_restore_duty_limit(devptr, old_value);
}
