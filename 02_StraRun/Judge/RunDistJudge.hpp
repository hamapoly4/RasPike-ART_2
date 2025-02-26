#ifndef ___RUN_DIST_JUDGE__CLASS
#define ___RUN_DIST_JUDGE__CLASS

#include <cmath>
#include "Judge.hpp"
#include "RunDistDetect.hpp"

namespace debrisys {

class RunDistJudge : public Judge {
private:
    RunDistDetect* mRunDist;

public:
    RunDistJudge(RunDistDetect* rundist, float target)
        : mRunDist(rundist), Judge(target)
    {
        ;
    }

    bool judge()
    {
        mMeasure = mRunDist->detectRunDist();
        mMeasure = std::fabs(mMeasure);
        if (mMeasure >= mTarget)
        {
            mResult = true;
        }

        return mResult;
    }

};  // class RunDistJudge

}   // namespace debrisys

#endif // ___RUN_DIST_JUDGE__CLASS
