#include "RotateRun.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 走行する */
void RotateRun::run()
{
    mGyroturn    = mGyroTurn->getTurn();    // ジャイロ操作量を取得
    mEncoderturn = mEncoderTurn->getTurn(); // エンコーダ操作量を取得
    switch (mDirection)
    {
        case ERotDire::LEFT :   // 左方向
            rotateLeft();
            break;
        case ERotDire::RIGHT :  // 右方向
            rotateRight();
            break;
        default :
            break;
    }
}

/* 左旋回する */
void RotateRun::rotateLeft()
{
    mLeftMotor.setPower(-mPOWER - mGyroturn - mEncoderturn);    // 左モータ回転
    mRightMotor.setPower(mPOWER + mGyroturn - mEncoderturn);    // 右モータ回転
}

/* 右旋回する */
void RotateRun::rotateRight()
{
    mLeftMotor.setPower(mPOWER + mGyroturn - mEncoderturn);     // 左モータ回転
    mRightMotor.setPower(-mPOWER - mGyroturn - mEncoderturn);   // 右モータ回転
}
