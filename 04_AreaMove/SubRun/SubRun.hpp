#ifndef ___SUB_RUN__CLASS
#define ___SUB_RUN__CLASS

#include <cstdint>
#include "Motor.hpp"

namespace debrisys {

class SubRun {
protected:
    /* インスタンス */
    Motor& mLeftMotor;      // 左モータ
    Motor& mRightMotor;     // 右モータ

    /* 属性 */
    int8_t mGyroturn;       // ジャイロ操作量
    int8_t mEncoderturn;    // エンコーダ操作量

    /* コンストラクタ */
    SubRun(Motor& leftmotor, Motor& rightmotor)
        : mLeftMotor(leftmotor), mRightMotor(rightmotor)
    {
        ;
    }

public:
    virtual void run() = 0; // 走行する

};  // class SubRun

}   // namespace debrisys

#endif // ___SUB_RUN__CLASS
