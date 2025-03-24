#include "GyroPControl.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 操作量を取得する */
int8_t GyroPControl::getTurn()
{
    float angle;

    angle = mConAng->detectRotateAngle();   // 旋回角度を検出
    angle = std::fabs(angle);               // 旋回角度の絶対値
    mDiff = mTargetAngle - angle;           // 偏差を求める
    calcP();                                // P演算

    if (mPvalue > mUpperLimit)  // 上限値でサチる
    {
        mTurn = mUpperLimit;    // 操作量は13
    }
    else if (mPvalue <= mUpperLimit)
    {
        mTurn = static_cast<float>(mPvalue);    // 操作量はP制御値
    }

    return mTurn;   // 操作量を返却
}

/* P演算をする */
void GyroPControl::calcP()
{
    mPvalue = mDiff * mPGAIN;   // 偏差とPゲインの乗算
}
