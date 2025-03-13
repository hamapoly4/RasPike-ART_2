#include "StraightRun.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 走行する */
void StraightRun::run()
{
    mEncoderturn = mEncoderTurn->getTurn();    // エンコーダ操作量を取得
    switch (mDirection)
    {
        case EStraDire::FRONT :     // 前方向
            runFront();
            break;
        case EStraDire::BEHIND :    // 後ろ方向
            runBehind();
            break;
        default :
            break;
    }
}

/* 前進する */
void StraightRun::runFront()
{
    mLeftMotor.setPower(mPOWER - mEncoderturn);     // 左モータ回転
    mRightMotor.setPower(mPOWER + mEncoderturn);    // 右モータ回転
}

/* 後退する */
void StraightRun::runBehind()
{
    mLeftMotor.setPower(-mPOWER - mEncoderturn);    // 左モータ回転
    mRightMotor.setPower(-mPOWER + mEncoderturn);   // 右モータ回転
}
