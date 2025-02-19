#include "Robot.hpp"

using namespace debrisys;

void Robot::conquer()
{
    if (mStep->checkState(Step::EState::FIN) == false)
    {
        mRollV->sensing();
        mLeftCount->sensing();
        mRightCount->sensing();
        mStep->execute();
    }
}
