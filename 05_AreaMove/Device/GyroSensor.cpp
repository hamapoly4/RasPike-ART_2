#include "GyroSensor.hpp"

/*======================コンストラクタ======================*/

GyroSensor::GyroSensor()
{
    hub_imu_init();
}

/*======================角速度を取得する======================*/

void GyroSensor::getAngularVelocity(float angv[3])
{
    hub_imu_get_angular_velocity(angv);
}
