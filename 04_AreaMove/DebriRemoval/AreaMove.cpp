#include "AreaMove.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 走行する */
void AreaMove::run()
{
    switch (mState)
    {
        case EState::EXE_STEP1 :
            exeStep1();
            break;
        case EState::EXE_STEP2 :
            exeStep2();
            break;
        default :
            break;
    }
}

/* 手順1を実行する */
void AreaMove::exeStep1()
{
    mStep1->execute();   // 手順1を実行
    if (mStep1->checkState(Step::EState::FIN))   // 手順1が終了したか判定
    {
        switchState(EState::EXE_STEP2); // 手順2実行中に遷移
    }
}

/* 手順2を実行する */
void AreaMove::exeStep2()
{
    mStep2->execute();   // 手順2を実行
    if (mStep2->checkState(Step::EState::FIN))   // 手順2が終了したか判定
    {
        switchState(EState::FIN);   // 終了状態に遷移
    }
}
