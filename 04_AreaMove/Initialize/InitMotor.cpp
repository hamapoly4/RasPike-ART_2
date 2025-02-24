#include "InitMotor.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 初期化する */
void InitMotor::init()
{
    switch (mState)
    {
        case EState::MOTOR_STOP :
            stopMotor();
            break;
        case EState::ENCODER_RESET :
            resetEncoder();
            break;
        default:
            break;
    }
}

/* モータを停止する */
void InitMotor::stopMotor()
{
    float leftcount;
    float rightcount;

    if (mStopFlag)  // モータ停止フラグが立っているか判定
    {
        mStopFlag = false;  // モータ停止フラグを降ろす
        mLeftMotor.stop();  // 左モータを停止
        mRightMotor.stop(); // 右モータを停止
        return;
    }

    leftcount  = mLeftCount->readData();    // 左回転角読み取り
    rightcount = mRightCount->readData();   // 右回転角読み取り
    if (mOldLeftcount == leftcount && mOldRightcount == rightcount) // 左右モータが完全に停止したか判定
    {
        switchState(EState::ENCODER_RESET);     // エンコーダリセット中に遷移
    }

    mOldLeftcount  = leftcount;     // 左回転角を保持
    mOldRightcount = rightcount;    // 右回転角を保持
}

/* エンコーダをリセットする */
void InitMotor::resetEncoder()
{
    float leftcount;
    float rightcount;

    if (mResetFlag) // エンコーダリセットフラグが立っているか判定
    {
        mResetFlag = false;     // エンコーダリセットフラグを降ろす
        mLeftCount->init();     // 左回転角をリセット
        mRightCount->init();    // 右回転角をリセット
        return;
    }

    leftcount  = mLeftCount->readData();    // 左回転角読み取り
    rightcount = mRightCount->readData();   // 右回転角読み取り
    if (leftcount == 0 && rightcount == 0)  // 左右回転角がリセットできたか判定
    {
        switchState(EState::FIN);   // 終了状態に遷移
    }
}

/* 状態を切り替える */
void InitMotor::switchState(EState state)
{
    mState = state;
}

