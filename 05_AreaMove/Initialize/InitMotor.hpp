#ifndef ___INIT_MOTOR__CLASS
#define ___INIT_MOTOR__CLASS

#include "SensorMonitor.hpp"
#include "Motor.hpp"

namespace debrisys {

class InitMotor {
public:
    enum class EState { MOTOR_STOP, ENCODER_RESET, FIN, };  // 列挙体クラス

private:
    /* インスタンス */
    SensorMonitor* mLeftCount;  // 左回転角
    SensorMonitor* mRightCount; // 右回転角 
    Motor& mLeftMotor;          // 左モータ
    Motor& mRightMotor;         // 右モータ

    /* 属性 */
    EState  mState;         // 状態
    bool    mStopFlag;      // モータ停止フラグ
    bool    mResetFlag;     // エンコーダリセットフラグ
    float   mOldLeftcount;  // 過去の左回転角
    float   mOldRightcount; // 過去の右回転角

    /* メソッド */
    void stopMotor();       // モータを停止する
    void resetEncoder();    // エンコーダをリセットする
    void switchState(EState state); // 状態を切り替える

public:
    /* コンストラクタ    */
    InitMotor(SensorMonitor* leftcount, SensorMonitor* rightcount,
                                    Motor& leftmotor, Motor& rightmotor)
        : mLeftCount(leftcount), mRightCount(rightcount), mLeftMotor(leftmotor), mRightMotor(rightmotor),
            mState(EState::MOTOR_STOP), mStopFlag(true), mResetFlag(true), mOldLeftcount(0), mOldRightcount(0)
    {
        ;
    }

    void init();    // 初期化する

    /* 状態を確認する */
    bool checkState(EState state) const
    {
        bool result = false;
        if (state == mState)    // 状態が一致するか判定
        {
            result = true;  // 状態が一致した
        }

        return result;  // 結果を返却
    }

};  // class InitMotor

}   // namespace debrisys

#endif // ___INIT_MOTOR__CLASS
