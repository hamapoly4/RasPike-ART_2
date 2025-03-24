#ifndef ___ROBOT__CLASS
#define ___ROBOT__CLASS

#include <cstdint>
#include "Route.hpp"
#include "SensorMonitor.hpp"

namespace debrisys {

class Robot {
private:
    /* インスタンス */
    Route*         mDebriRemoval;   // デブリリムーバル
    SensorMonitor* mRollV;          // ロール角速度
    SensorMonitor* mLeftCount;      // 左回転角
    SensorMonitor* mRightCount;     // 右回転角

    /* 属性 */
    static const uint8_t mFinalSection = 1; // 最終区間番号

public:
    /* コンストラクタ */
    Robot(Route* debriremoval, SensorMonitor* rollv, SensorMonitor* leftcount, SensorMonitor* rightcount)
        : mDebriRemoval(debriremoval), mRollV(rollv), mLeftCount(leftcount), mRightCount(rightcount)
    {
        ;
    }

    /* 攻略する */
    void conquer()
    {
        uint8_t sect_num;

        sect_num = mDebriRemoval->readSectNum();    // 区間番号読み取り
        if (sect_num <= mFinalSection)  // 最終区間番号以下か判定
        {
            mRollV->sensing();      // ロール角速度をセンシング
            mLeftCount->sensing();  // 左回転角をセンシング
            mRightCount->sensing(); // 右回転角をセンシング
            mDebriRemoval->run();   // デブリリムーバルを走行する
        }
    }

};  // class Robot

}   // namespace debrisys

#endif // ___ROBOT__CLASS
