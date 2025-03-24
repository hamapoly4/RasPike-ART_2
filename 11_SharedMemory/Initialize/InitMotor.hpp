#ifndef ___INIT_MOTOR__CLASS
#define ___INIT_MOTOR__CLASS

#include <cstdint>
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
    static const uint8_t SAMP_MAX = 7;
    
    EState  mState;         		// 状態
    bool    mStopFlag;      		// モータ停止フラグ
    bool    mResetFlag;     		// エンコーダリセットフラグ
    static float sampl[SAMP_MAX];  	// 左回転角サンプリング
    static float sampr[SAMP_MAX];  	// 右回転角サンプリング
    static uint8_t idx;     		// 添字

    /* メソッド */
    void stopMotor();       // モータを停止する
    void resetEncoder();    // エンコーダをリセットする
    void sampDataReset();   // サンプリングデータをリセットする
    void switchState(EState state); // 状態を切り替える

public:
    /* コンストラクタ    */
    InitMotor(SensorMonitor* leftcount, SensorMonitor* rightcount,
                                    Motor& leftmotor, Motor& rightmotor)
        : mLeftCount(leftcount), mRightCount(rightcount), mLeftMotor(leftmotor), mRightMotor(rightmotor),
            mState(EState::MOTOR_STOP), mStopFlag(true), mResetFlag(true)
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
