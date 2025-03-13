#include "DebriRemove.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 走行する */
void DebriRemove::run()
{
    switch (mState)
    {
        case EState::CIRCLE1_RUN :
            circleRun(0);
            break;
        case EState::CIRCLE2_RUN :
            circleRun(1);
            break;
        case EState::CIRCLE3_RUN :
            circleRun(2);
            break;
        case EState::CIRCLE4_RUN :
            circleRun(3);
            break;
        default :
            break;
    }
}

/* サークル走行をする */
void DebriRemove::circleRun(uint8_t num)
{
    EState state;
    mCircle[num].run();     // サークルに応じた走行

    if (mCircle[num].checkState(Circle::EState::FIN))   // サークル走行が終了したら判定
    {
        switch (num)
        {
            case 0:
                state = EState::CIRCLE2_RUN;
                break;
            case 1:
                state = EState::CIRCLE3_RUN;
                break;
            case 2:
                state = EState::CIRCLE4_RUN;
                break;
            case 3:
                state = EState::FIN;
                break;
            default:
                break;
        }
        switchState(state); // 指定した状態に遷移
    }
}
