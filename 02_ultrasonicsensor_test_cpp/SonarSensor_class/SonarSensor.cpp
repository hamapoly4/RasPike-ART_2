#include "SonarSensor.hpp"

/*======================コンストラクタ======================*/
SonarSensor::SonarSensor(pbio_port_id_t sonar_port)
{
    devptr = pup_ultrasonic_sensor_get_device(sonar_port);
}

/*======================距離を測定する======================*/
int32_t SonarSensor::getDistance()
{
    return pup_ultrasonic_sensor_distance(devptr);
}
