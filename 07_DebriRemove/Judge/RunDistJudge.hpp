#ifndef ___RUN_DIST_JUDGE__CLASS
#define ___RUN_DIST_JUDGE__CLASS

#include <cmath>
#include "Judge.hpp"
#include "RunDistDetect.hpp"

namespace debrisys {

class RunDistJudge : public Judge {
private:
    /* インスタンス */
    RunDistDetect* mRunDist;    // 走行距離

public:
    /* コンストラクタ */
    RunDistJudge(RunDistDetect* rundist, float target)
        : mRunDist(rundist), Judge(target)
    {
        ;
    }

    /* 判定する */
    bool judge()
    {
        mMeasure = mRunDist->detectRunDist();   // 走行距離を検出
        mMeasure = std::fabs(mMeasure);         // 走行距離の絶対値を求める
        if (mMeasure >= mTarget)                // 目標値を満たしたか判定
        {
            mResult = true;     // 終了条件を満たした
        }

        return mResult;     // 判定結果を返却
    }

};  // class RunDistJudge

}   // namespace debrisys

#endif // ___RUN_DIST_JUDGE__CLASS
