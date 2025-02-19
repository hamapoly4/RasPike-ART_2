#ifndef ___ROTATE_ANGLE_JUDGE__CLASS
#define ___ROTATE_ANGLE_JUDGE__CLASS

#include <cmath>
#include "Judge.hpp"
#include "RotateAngleDetect.hpp"

namespace debrisys {

class RotateAngleJudge : public Judge {
private:
    RotateAngleDetect* mJudgeAng;

public:
    RotateAngleJudge(RotateAngleDetect* judge_ang, float target)
        : mJudgeAng(judge_ang), Judge(target)
    {
        ;
    }

    bool judge()
    {
        mMeasure = mJudgeAng->detectRotateAngle();
        mMeasure = std::fabs(mMeasure);
        if (mMeasure >= mTarget)
        {
            mResult = true;
        }

        return mResult;
    }


};  // class RotateAngleJudge

}   // namespace debrisys

#endif // ___ROTATE_ANGLE_JUDGE__CLASS
