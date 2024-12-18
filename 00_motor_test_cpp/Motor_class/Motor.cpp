#include "Motor.hpp"

/*-------------------------------------------------------------------------------
 *  関数名  ：  コンストラクタ
 *  概要    ：  モータの初期化
 *  引数    ：  ポートID、回転方向（時計回りor反時計回り）、エンコーダ値のリセットの有無
 *  返り値  ：
---------------------------------------------------------------------------------*/
Motor::Motor(pbio_port_id_t motor_port, pup_direction_t positive_direction, bool reset_count)
{
    devptr = pup_motor_get_device(motor_port);

    pup_motor_setup(devptr, positive_direction, reset_count);
}

void Motor::resetCount()
{
    pup_motor_reset_count(devptr);
}

int32_t Motor::getCount()
{
    return pup_motor_get_count(devptr);
}

int32_t Motor::getSpeed()
{
    return pup_motor_get_speed(devptr);
}

void Motor::setSpeed(int speed)
{
    pup_motor_set_speed(devptr, speed);
}

int32_t Motor::getPower()
{
    return pup_motor_get_power(devptr);
}

void Motor::setPower(int power)
{
    pup_motor_set_power(devptr, power);
}

void Motor::stop()
{
    pup_motor_stop(devptr);
}

void Motor::brake()
{
    pup_motor_brake(devptr);
}

void Motor::hold()
{
    pup_motor_hold(devptr);
}
    
bool Motor::isStalled()
{
    return pup_motor_is_stalled(devptr);
}

int32_t Motor::setDutyLimit(int duty_limit)
{
    return pup_motor_set_duty_limit(devptr, duty_limit);
}

void Motor::restoreDutyLimit(int old_value)
{
    pup_motor_restore_duty_limit(devptr, old_value);
}
