#include "Circle.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 走行する */
void Circle::run()
{
    switch (mState)
    {
        case EState::BOTTLE_EXIST :
            findBottle();
            break;
        case EState::EXE_STEP1 :
            exeStep(0);
            break;
        case EState::JUDGE_COLOR :
            judgeColor();
            break;
        case EState::EXE_STEP2 :
            exeStep(1);
            break;
        case EState::EXE_STEP3 :
            exeStep(2);
            break;
        case EState::EXE_STEP4 :
            exeStep(3);
            break;
        default :
            break;
    }
}

/* 手順を実行する */
void Circle::exeStep(uint8_t num)
{
    EState state;
    mStep[num].execute(); // 手順を実行

    if (mStep[num].checkState(Step::EState::FIN)) // 手順が終了したら判定
    {
        switch (num)
        {
            case 0:
                state = EState::JUDGE_COLOR;
                break;
            case 1:
                state = EState::EXE_STEP3;
                break;
            case 2:
                state = EState::EXE_STEP4;
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


/* ボトルの有無を認識する */
void Circle::findBottle()
{
    if (mBottle == true)    // ボトルがあれば判定
    {
        switchState(EState::EXE_STEP1); // 手順1実行中に遷移
    }
    else                    // ボトルがなければ判定
    {
        switchState(EState::FIN);       // 終了状態に遷移
    }
}

/* ボトルの色を判定する */
void Circle::judgeColor()
{
    EColor color;

    color = mBlueBottle->detectColor(); // ボトルの色を検出
    if (color == EColor::BLUE)          // ボトルの色が青なら判定
    {
        switchState(EState::EXE_STEP2); // 手順2実行中に遷移
    }
    else if (color == EColor::RED)      // ボトルの色が赤なら判定
    {
        switchState(EState::EXE_STEP4); // 手順4実行中に遷移
    }
}

/* 状態を切り替える */
void Circle::switchState(EState state)
{
    mState = state;
}
