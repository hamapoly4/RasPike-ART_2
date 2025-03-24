#include "Circle.hpp"
#include <stdio.h>

using namespace debrisys;   // 名前空間debrisys

uint32_t Circle::mBluePixels = 0;

/* 走行する */
void Circle::run()
{
    switch (mState)
    {
        case EState::BOTTLE_EXIST :
            findBottle();
            break;
        case EState::EXE_STEP1 :	// 手順1実行
            exeStep(0);
            break;
        case EState::JUDGE_COLOR :
            judgeColor();
            break;
        case EState::EXE_STEP2 :	// 手順2実行
            exeStep(1);
            break;
        case EState::EXE_STEP3 :	// 手順3実行
            exeStep(2);
            break;
        case EState::EXE_STEP4 :	// 手順4実行
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
                printf("JUDGE_COLORに遷移\n");
                break;
            case 1:
                state = EState::EXE_STEP3;
                printf("手順3実行中に遷移\n");
                break;
            case 2:
                state = EState::EXE_STEP4;
                printf("手順4実行中に遷移\n");
                break;
            case 3:
                state = EState::FIN;
                printf("終了状態に遷移\n");
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
        printf("手順1実行中に遷移\n");
    }
    else                    // ボトルがなければ判定
    {
        switchState(EState::FIN);       // 終了状態に遷移
        printf("終了状態に遷移\n");
    }
}

/* ボトルの色を判定する */
void Circle::judgeColor()
{
    if (mBluePixels >= 10000)			// ボトルの色が青なら判定
    {
        switchState(EState::EXE_STEP2); // 手順2実行中に遷移
        printf("手順2実行中に遷移\n");
    }
    else                                // ボトルの色が赤なら判定
    {
        switchState(EState::EXE_STEP4); // 手順4実行中に遷移
        printf("手順4実行中に遷移\n");
    }
}

/* 状態を切り替える */
void Circle::switchState(EState state)
{
    mState = state;
}
