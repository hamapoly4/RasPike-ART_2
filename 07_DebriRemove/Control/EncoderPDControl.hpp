#ifndef ___ENCODER_PD_CONTROL__CLASS
#define ___ENCODER_PD_CONTROL__CLASS

#include <cstdint>
#include "Control.hpp"
#include "SensorMonitor.hpp"

namespace debrisys {

class EncoderPDControl : public Control {
public:
    enum class ERun { ROTATE, STRAIGHT, };  // 列挙体クラス

private:
    /* インスタンス */
    SensorMonitor* mLeftCount;  // 左回転角
    SensorMonitor* mRightCount; // 右回転角

    /* 属性 */
    ERun  mRumM;
    float mOldDiff;     // 過去の偏差

    static constexpr float mPGAIN = 1.5;    // Pゲイン
    static constexpr float mDGAIN = 1.5;    // Dゲイン

    /* メソッド */
    void calcP();   // P演算をする
    void calcD();   // D演算をする

public:
    /* コンストラクタ */
    EncoderPDControl(SensorMonitor* leftcount, SensorMonitor* rightcount, ERun runm)
        : mLeftCount(leftcount), mRightCount(rightcount), mRumM(runm), mOldDiff(0)
    {
        ;
    }

    int8_t getTurn();   // 操作量を取得する

};  // class EncoderPDControl

}   // namespace debrisys

#endif // ___ENCODER_PD_CONTROL__CLASS
