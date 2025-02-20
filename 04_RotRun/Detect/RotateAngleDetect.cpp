#include "RotateAngleDetect.hpp"

using namespace debrisys;

float RotateAngleDetect::detectRotateAngle()
{
    mRollv = mRollV->readData();
    integrate();
    mAngCorr->correct(mRolla);
    calcRotateAngle();
    return mRotateAngle;
}

void RotateAngleDetect::integrate()
{
    mRolla = mRollv * mTIME;
}

void RotateAngleDetect::calcRotateAngle()
{
    mRotateAngle += mRolla * mCOFF;
}
