#include "StraPDControl.hpp"

using namespace debrisys;

int8_t StraPDControl::getTurn()
{
    mLeftcount  = mLeftCount->readData();
    mRightcount = mRightCount->readData();
    mDiff       = mLeftcount - mRightcount;
    calcP();
    calcD();
    mTurn       = static_cast<int8_t>(mPvalue + mDvalue);
    return mTurn;
}

void StraPDControl::calcP()
{
    mPvalue = mDiff * mPGAIN;
}

void StraPDControl::calcD()
{
    mDvalue  = (mOldDiff - mDiff) * mDGAIN;
    mOldDiff = mDiff;
}
