#include "StraightRun.hpp"

using namespace debrisys;

void StraightRun::run()
{
    mTurn = mTuRn->getTurn();
    switch (mDirection)
    {
        case EStraDire::FRONT :
            runFront();
            break;
        case EStraDire::BEHIND :
            runBehind();
            break;
        default :
            break;
    }
}

void StraightRun::runFront()
{
    mLeftMotor.setPower(mPOWER - mTurn);
    mRightMotor.setPower(mPOWER + mTurn);
}

void StraightRun::runBehind()
{
    mLeftMotor.setPower(-mPOWER - mTurn);
    mRightMotor.setPower(-mPOWER + mTurn);
}
