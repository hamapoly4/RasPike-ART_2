#include "RotateRun.hpp"

using namespace debrisys;

void RotateRun::run()
{
    mTurn  = mTuRn->getTurn();
    mTurn1 = mTuRn1->getTurn();
    switch (mDirection)
    {
        case ERotDire::LEFT :
            rotateLeft();
            break;
        case ERotDire::RIGHT :
            rotateRight();
            break;
        default :
            break;
    }
}

void RotateRun::rotateLeft()
{
    mLeftMotor.setPower(-(mPOWER + mTurn + mTurn1));
    mRightMotor.setPower(mPOWER + mTurn - mTurn1);
}

void RotateRun::rotateRight()
{
    mLeftMotor.setPower(mPOWER + mTurn - mTurn1);
    mRightMotor.setPower(-(mPOWER + mTurn + mTurn1));
}
