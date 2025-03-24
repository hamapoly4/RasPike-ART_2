#ifndef ___STRAIGHT_RUN__CLASS
#define ___STRAIGHT_RUN__CLASS

#include <cmath>
#include "enum_class.hpp"
#include "SubRun.hpp"
#include "Control.hpp"
#include "Motor.hpp"

namespace debrisys {

class StraightRun : public SubRun {
private:
    /* インスタンス */
    Control* mEncoderTurn;  // エンコーダ操作量

    /* 属性 */
    static const int8_t mPOWER = 45;    // 既定のパワー値
    EStraDire mDirection;               // 直進方向

    /* メソッド */
    void runFront();    // 前進する
    void runBehind();   // 後退する

public:
    /* コンストラクタ */
    StraightRun(Motor& leftmotor, Motor& rightmotor, Control* encoderturn, EStraDire direction)
        : SubRun(leftmotor, rightmotor), mEncoderTurn(encoderturn), mDirection(direction)
    {
        ;
    }

    void run();     // 走行する

};  // class StraightRun

}   // namespace debrisys

#endif // ___STRAIGHT_RUN__CLASS
