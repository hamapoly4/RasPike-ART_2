#ifndef ___AREA_MOVE__CLASS
#define ___AREA_MOVE__CLASS

#include "MainRun.hpp"
#include "Step.hpp"

namespace debrisys {

class AreaMove : public MainRun {
private:
    /* インスタンス */
    Step* mStep1;   // 手順1
    Step* mStep2;   // 手順2

    /* メソッド */
    void exeStep1();    // 手順1を実行する
    void exeStep2();    // 手順2を実行する

public:
    /* コンストラクタ */
    AreaMove(Step* step1, Step* step2)
        : mStep1(step1), mStep2(step2), MainRun(EState::EXE_STEP1)
    {
        ;
    }

    void run();     // 走行する

};  // class AreaMove

}   // namespace debrisys

#endif // ___AREA_MOVE__CLASS
