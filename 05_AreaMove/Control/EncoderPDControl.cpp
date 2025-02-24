#include "EncoderPDControl.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 操作量を取得する */
int8_t EncoderPDControl::getTurn()
{
    float leftcount;
    float rightcount;

    leftcount  = mLeftCount->readData();    // 左回転角読み取り
    rightcount = mRightCount->readData();   // 右回転角読み取り
    mDiff      = leftcount - rightcount;    // 偏差を求める
    calcP();    // P演算
    calcD();    // D演算
    mTurn = static_cast<int8_t>(mPvalue + mDvalue); // P制御値とD制御値の和

    return mTurn;   // 操作量を返却
}

/* P演算をする */
void EncoderPDControl::calcP()
{
    mPvalue = mDiff * mPGAIN;   // 偏差とPゲインの乗算
}

/* D演算をする */
void EncoderPDControl::calcD()
{
    mDvalue  = (mOldDiff - mDiff) * mDGAIN; // D制御値を求める
    mOldDiff = mDiff;   // 偏差を保持
}
