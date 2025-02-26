#ifndef ___ENCODER_MONITOR__CLASS
#define ___ENCODER_MONITOR__CLASS

#include <cstdint>
#include "SensorMonitor.hpp"
#include "Motor.hpp"

namespace debrisys {

class EncoderMonitor : public SensorMonitor {
private:
    Motor&  mMotorEncoder;  // モータエンコーダ
    int32_t mCount;         // 回転角

public:
    /* コンストラクタ */
    EncoderMonitor(Motor& motorencoder)
        : mMotorEncoder(motorencoder)
    {
        ;
    }

    /* センシングする */
    void sensing()
    {
        mCount = mMotorEncoder.getCount();  // 回転角を取得
    }

    /* データを読み取る */
    float readData() const
    {
        return mCount;  // 回転角を返却
    }

    /* 初期化する */
    void init() const
    {
        mMotorEncoder.resetCount(); // 回転角をリセット
    }

};  // class EncoderMonitor

}   // namespace debrisys

#endif // ___ENCODER_MONITOR__CLASS
