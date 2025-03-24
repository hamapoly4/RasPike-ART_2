#include "ColorSensor.hpp"

/*======================コンストラクタ======================*/

ColorSensor::ColorSensor(pbio_port_id_t colorsensor_port)
{
    devptr = pup_color_sensor_get_device(colorsensor_port);
}

/*======================環境光の強さを測定する======================*/

int32_t ColorSensor::getAmbient()
{
    return pup_color_sensor_ambient(devptr);
}

/*======================反射光の強さを測定する======================*/

int32_t ColorSensor::getBrightness()
{
    return pup_color_sensor_reflection(devptr);
}

/*======================RGB値を測定する======================*/

pup_color_rgb_t ColorSensor::getRGB()
{
    return pup_color_sensor_rgb(devptr);
}

/*======================HSV値を測定する======================*/

pup_color_hsv_t ColorSensor::getHSV()
{
    return pup_color_sensor_hsv(devptr, true);
}
