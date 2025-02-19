#include "RotatePControl.hpp"

using namespace debrisys;

int8_t RotatePControl::getTurn()
{
    mAngle = mConAng->detectRotateAngle();
    mDiff = mTargetAngle - mAngle;
    mDiff = std::fabs(mDiff);
    calcP();
    if (mPvalue > 13)
    {
        mTurn = 13;
    }
    else if (mPvalue <= 13)
    {
        mTurn = static_cast<float>(mPvalue);
    }
    return mTurn;
}

void RotatePControl::calcP()
{
    mPvalue = mDiff * mPGAIN;
}
