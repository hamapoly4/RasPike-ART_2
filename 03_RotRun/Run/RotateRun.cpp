#include "RotateRun.hpp"
#include <stdio.h>

using namespace debrisys;

void RotateRun::run()
{
    mTurn  = mTuRn->getTurn();
    mTurn1 = mTuRn1->getTurn();
    printf("mTurn  : %d\n", mTurn);
    printf("mTurn1 : %d\n", mTurn1);
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
    printf("-------------------\n");
}

void RotateRun::rotateLeft()
{
	printf("result l : %d\n", -(mPOWER + mTurn + mTurn1));
    printf("result r : %d\n", mPOWER + mTurn - mTurn1);
    mLeftMotor.setPower(-(mPOWER + mTurn + mTurn1));
    mRightMotor.setPower(mPOWER + mTurn - mTurn1);
}

void RotateRun::rotateRight()
{
    mLeftMotor.setPower(mPOWER + mTurn - mTurn1);
    mRightMotor.setPower(-(mPOWER + mTurn + mTurn1));
}
