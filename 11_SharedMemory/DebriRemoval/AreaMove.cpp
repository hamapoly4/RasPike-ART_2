#include "AreaMove.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 走行する */
void AreaMove::run()
{
    switch (mState)
    {
        case EState::EXE_STEP1 :
            exeStep(0);
            break;
        case EState::EXE_STEP2 :
            exeStep(1);
            break;
        default :
            break;
    }
}

/* 手順を実行する */
void AreaMove::exeStep(uint8_t num)
{
    EState state;
    mStep[num].execute(); // 手順を実行

    if (mStep[num].checkState(Step::EState::FIN)) // 手順が終了したら判定
    {
        switch (num)
        {
            case 0:
                state = EState::EXE_STEP2;
                break;
            case 1:
                state = EState::FIN;
                break;
            default:
                break;
        }
        switchState(state); // 指定した状態に遷移
    }
}
