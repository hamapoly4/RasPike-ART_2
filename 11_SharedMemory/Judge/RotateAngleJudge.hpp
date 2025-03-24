#ifndef ___ROTATE_ANGLE_JUDGE__CLASS
#define ___ROTATE_ANGLE_JUDGE__CLASS

#include <cmath>
#include "Judge.hpp"
#include "RotateAngleDetect.hpp"

namespace debrisys {

class RotateAngleJudge : public Judge {
private:
    /* インスタンス */
    RotateAngleDetect* mJudgeAng;   // 判定用旋回角度

public:
    /* コンストラクタ */
    RotateAngleJudge(RotateAngleDetect* judge_ang, float target)
        : mJudgeAng(judge_ang), Judge(target)
    {
        ;
    }

    /* 判定する */
    bool judge()
    {
        mMeasure = mJudgeAng->detectRotateAngle();  // 旋回角度を検出
        mMeasure = std::fabs(mMeasure);             // 旋回角度の絶対値を求める
        if (mMeasure >= mTarget || mTarget == 0)    // 目標値を満たしたか目標値が0なら判定
        {
            mResult = true;     // 終了条件を満たした
        }

        return mResult;     // 判定結果を返却
    }


};  // class RotateAngleJudge

}   // namespace debrisys

#endif // ___ROTATE_ANGLE_JUDGE__CLASS
