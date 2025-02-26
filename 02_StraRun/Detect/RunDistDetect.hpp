#ifndef ___RUN_DIST_DETECT__CLASS
#define ___RUN_DIST_DETECT__CLASS

#include "SensorMonitor.hpp"

namespace debrisys {

class RunDistDetect {
private:
    SensorMonitor* mLeftCount;
    SensorMonitor* mRightCount;

    float mRundist;
    static constexpr float mCNT1_DIST = 0.87266;

public:
    RunDistDetect(SensorMonitor* leftcount, SensorMonitor* rightcount)
        : mLeftCount(leftcount), mRightCount(rightcount), mRundist(0)
    {
        ;
    }

    float detectRunDist()
    {
        float leftcount;
        float rightcount;
        leftcount  = mLeftCount->readData();
        rightcount = mRightCount->readData();
        mRundist = (leftcount + rightcount) * mCNT1_DIST / 2.0;
        return mRundist;
    }

};  // class RunDistDetect

}   // namespace debrisys

#endif // ___RUN_DIST_DETECT__CLASS
