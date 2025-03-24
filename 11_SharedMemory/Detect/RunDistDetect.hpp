#ifndef ___RUN_DIST_DETECT__CLASS
#define ___RUN_DIST_DETECT__CLASS

#include "SensorMonitor.hpp"

namespace debrisys {

class RunDistDetect {
private:
    /* インスタンス */
    SensorMonitor* mLeftCount;  // 左回転角
    SensorMonitor* mRightCount; // 右回転角

    /* 属性 */
    static constexpr float mCNT1_DIST = 0.87266;    // 単位回転角あたりの走行距離

public:
    /* コンストラクタ */
    RunDistDetect(SensorMonitor* leftcount, SensorMonitor* rightcount)
        : mLeftCount(leftcount), mRightCount(rightcount)
    {
        ;
    }

    /* 走行距離を検出する */
    float detectRunDist()
    {
        float leftcount;
        float rightcount;

        leftcount  = mLeftCount->readData();    // 左回転角の読み取り
        rightcount = mRightCount->readData();   // 右回転角の読み取り

        return (leftcount + rightcount) * mCNT1_DIST / 2.0; // 走行距離を返却
    }

};  // class RunDistDetect

}   // namespace debrisys

#endif // ___RUN_DIST_DETECT__CLASS
