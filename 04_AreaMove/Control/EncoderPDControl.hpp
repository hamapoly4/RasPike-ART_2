#ifndef ___ENCODER_PD_CONTROL__CLASS
#define ___ENCODER_PD_CONTROL__CLASS

#include <cstdint>
#include "Control.hpp"
#include "SensorMonitor.hpp"

namespace debrisys {

class EncoderPDControl : public Control {
private:
    /* インスタンス */
    SensorMonitor* mLeftCount;  // 左回転角
    SensorMonitor* mRightCount; // 右回転角

    /* 属性 */
    float mOldDiff;     // 過去の偏差

    static constexpr float mPGAIN = 1.5;    // Pゲイン
    static constexpr float mDGAIN = 1.5;    // Dゲイン

    /* メソッド */
    void calcP();   // P演算をする
    void calcD();   // D演算をする

public:
    /* コンストラクタ */
    EncoderPDControl(SensorMonitor* leftcount, SensorMonitor* rightcount)
        : mLeftCount(leftcount), mRightCount(rightcount), mOldDiff(0)
    {
        ;
    }

    int8_t getTurn();   // 操作量を取得する

};  // class EncoderPDControl

}   // namespace debrisys

#endif // ___ENCODER_PD_CONTROL__CLASS
