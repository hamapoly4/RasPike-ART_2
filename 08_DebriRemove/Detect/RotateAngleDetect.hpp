#ifndef ___ROTATE_ANGLE_DETECT__CLASS
#define ___ROTATE_ANGLE_DETECT__CLASS

#include "SensorMonitor.hpp"
#include "RotateAngleCorrect.hpp"

namespace debrisys {

class RotateAngleDetect {
private:
    /* インスタンス */
    const SensorMonitor*      mRollV;   // ロール角速度
    const RotateAngleCorrect* mAngCorr; // 角度補正

    /* 属性 */
    float mRotateAngle; // 旋回角度
    float mRolla;       // ロール角
    float mRollv;       // ロール角速度

    static constexpr float mTIME = 0.01;        // 積分演算用時間
    static constexpr float mCOFF = 1.309324702; // 係数

    /* メソッド */
    void integrate();       // 時間積分をする
    void calcRotateAngle(); // 旋回角度を求める

public:
    /* コンストラクタ */
    RotateAngleDetect(const SensorMonitor* rollv, const RotateAngleCorrect* angcorr)
        : mRollV(rollv), mAngCorr(angcorr), mRotateAngle(0)
    {
        ;
    }

    float detectRotateAngle();  // 旋回角度を検出する

};  // class RotateAngleDetect

}   // namespace debrisys

#endif // ___ROTATE_ANGLE_DETECT__CLASS
