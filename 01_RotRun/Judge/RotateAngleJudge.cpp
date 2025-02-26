#include "RotateAngleJudge.hpp"

using namespace debrisys;

bool RotateAngleJudge::judge()
{
    mMeasure = mJudgeAng->detectRotateAngle();
    mMeasure = std::fabs(mMeasure);
    if (mMeasure >= mTarget)
    {
        mResult = true;
    }

    return mResult;
}
