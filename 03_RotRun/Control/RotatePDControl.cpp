#include "RotatePDControl.hpp"

using namespace debrisys;

int8_t RotatePDControl::getTurn()
{
    float leftcount;
    float rightcount;
    leftcount  = mLeftCount->readData();
    rightcount = mRightCount->readData();
    mDiff      = leftcount + rightcount;
    calcP();
    calcD();
    mTurn      = static_cast<int8_t>(mPvalue + mDvalue);
    return mTurn;
}

void RotatePDControl::calcP()
{
    mPvalue = mDiff * mPGAIN;
}

void RotatePDControl::calcD()
{
    mDvalue  = (mOldDiff - mDiff) * mDGAIN;
    mOldDiff = mDiff;
}
