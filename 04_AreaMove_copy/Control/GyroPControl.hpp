#ifndef ___GYRO_P_CONTROL__CLASS
#define ___GYRO_P_CONTROL__CLASS

#include <cstdint>
#include <cmath>
#include "Control.hpp"
#include "RotateAngleDetect.hpp"

namespace debrisys {

class GyroPControl : public Control {
private:
    /* インスタンス */
    RotateAngleDetect* mConAng; // 制御用旋回角度

    /* 属性 */
    float  mTargetAngle;    // 目標旋回角度
    int8_t mUpperLimit;     // 操作量上限値

    static constexpr float mPGAIN = 0.15;   // Pゲイン

    /* メソッド */
    void calcP();   // P演算をする

public:
    /* コンストラクタ */
    GyroPControl(RotateAngleDetect* con_ang, float tager_angle, int8_t upperlimit = 13)
        : mConAng(con_ang), mTargetAngle(tager_angle), mUpperLimit(upperlimit)
    {
        ;
    }

    int8_t getTurn();   // 操作量を取得する

};  // class GyroPControl

}   // namespace debrisys

#endif // ___GYRO_P_CONTROL__CLASS
