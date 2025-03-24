#include "IMU.hpp"

/*======================コンストラクタ======================*/

IMU::IMU()
{
    hub_imu_init();
}

/*======================加速度を取得する======================*/

void IMU::getAcceleration(float accel[3])
{
    hub_imu_get_acceleration(accel);
}

/*======================角速度を取得する======================*/

void IMU::getAngularVelocity(float angv[3])
{
    hub_imu_get_angular_velocity(angv);
}
