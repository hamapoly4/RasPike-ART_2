#ifndef ___ROBOT__CLASS
#define ___ROBOT__CLASS

#include <cstdint>
#include "Step.hpp"
#include "SensorMonitor.hpp"

namespace debrisys {

class Robot {
private:
    /* インスタンス */
    Step*          mStep1;
    SensorMonitor* mRollV;          // ロール角速度
    SensorMonitor* mLeftCount;      // 左回転角
    SensorMonitor* mRightCount;     // 右回転角

    /* 属性 */
    static const uint8_t mFinalSection = 0; // 最終区間番号

public:
    /* コンストラクタ */
    Robot(Step* step1, SensorMonitor* rollv, SensorMonitor* leftcount, SensorMonitor* rightcount)
        : mStep1(step1), mRollV(rollv), mLeftCount(leftcount), mRightCount(rightcount)
    {
        ;
    }

    /* 攻略する */
    void conquer()
    {
        uint8_t sect_num;

        if (mStep1->checkState() != Step::EState::FIN)
        {
            mStep1->execute();
        }
    }

};  // class Robot

}   // namespace debrisys

#endif // ___ROBOT__CLASS
