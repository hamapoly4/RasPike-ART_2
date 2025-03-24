#ifndef ___AREA_MOVE__CLASS
#define ___AREA_MOVE__CLASS

#include <cstdint>
#include "MainRun.hpp"
#include "Step.hpp"

namespace debrisys {

class AreaMove : public MainRun {
private:
    /* インスタンス */
    Step* mStep;    // 手順1,2

    /* メソッド */
    void exeStep(uint8_t num);  // 手順を実行する

public:
    /* コンストラクタ */
    AreaMove(Step* step)
        : mStep(step), MainRun(EState::EXE_STEP1)
    {
        ;
    }

    void run();     // 走行する

};  // class AreaMove

}   // namespace debrisys

#endif // ___AREA_MOVE__CLASS
