#ifndef ___ROTATE_RUN__CLASS
#define ___ROTATE_RUN__CLASS

#include <cstdint>
#include "enum_class.hpp"
#include "SubRun.hpp"
#include "Control.hpp"
#include "Motor.hpp"

namespace debrisys {

class RotateRun : public SubRun {
private:
    /* インスタンス */
    Control* mGyroTurn;     // ジャイロ操作量
    Control* mEncoderTurn;  // エンコーダ操作量

    /* 属性 */
    static const int8_t mPOWER = 37;    // 既定のパワー値
    ERotDire mDirection;                // 旋回方向

    /* メソッド */
    void rotateLeft();      // 左旋回する
    void rotateRight();     // 右旋回する

public:
    /* コンストラクタ */
    RotateRun(Motor& leftmotor, Motor& rightmotor,
                    Control* gyroturn, Control* encoderturn, ERotDire direction)
        : SubRun(leftmotor, rightmotor), mGyroTurn(gyroturn),
                    mEncoderTurn(encoderturn), mDirection(direction)
    {
        ;
    }

    void run();     // 走行する

};  // class RotateRun

}   // namespace debrisys

#endif // ___ROTATE_RUN__CLASS
