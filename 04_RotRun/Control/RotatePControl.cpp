#include "RotatePControl.hpp"

using namespace debrisys;

int8_t RotatePControl::getTurn()
{
    mAngle = mConAng->detectRotateAngle();
    mAngle = std::fabs(mAngle);
    mDiff = mTargetAngle - mAngle;
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
