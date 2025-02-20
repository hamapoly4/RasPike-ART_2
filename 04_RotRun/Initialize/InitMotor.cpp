#include "InitMotor.hpp"

using namespace debrisys;

void InitMotor::init()
{
    float leftcount;
    float rightcount;

    if (mStopFlag == true)
    {
        mStopFlag = false;
        mLeftMotor.stop();
        mRightMotor.stop();
        return;
    }

    leftcount = mLeftCount->readData();
    rightcount = mRightCount->readData();
    if (leftcount == 0 && rightcount == 0)
    {
        mFinFlag = true;
    }
    else
    {
        mLeftCount->init();
        mRightCount->init();
    }
}
