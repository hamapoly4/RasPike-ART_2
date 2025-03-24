#include "RotateAngleDetect.hpp"

using namespace debrisys;   // 使用する名前空間

/* 旋回角度を検出する */
float RotateAngleDetect::detectRotateAngle()
{
    mRollv = mRollV->readData();    // ロール角速度読み取り
    integrate();                    // 時間で積分
    mAngCorr->correct(mRolla);      // 誤差を補正
    calcRotateAngle();              // 旋回角度を算出
    return mRotateAngle;            // 旋回角度を返却
}

/* 時間積分をする */
void RotateAngleDetect::integrate()
{
    mRolla = mRollv * mTIME;    // ロール角速度と経過時間の乗算
}

/* 旋回角度を求める */
void RotateAngleDetect::calcRotateAngle()
{
    mRotateAngle += mRolla * mCOFF; // 旋回角度を積み上げる
}
