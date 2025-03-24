#include "Step.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 実行する */
void Step::execute()
{
    do {
        mOldState = mState; // 状態を保持
        switch (mState)
        {
            case EState::RUN :
                run();
                break;
            case EState::INIT :
                init();
                break;
            default :
                break;
        }
    } while (mOldState != mState);  // 状態が切り替わったら繰り返す
}

/* 走行する */
void Step::run()
{
    if (mJudge->judge())    // 終了条件を満たしたか判定
    {
        switchState(EState::INIT);  // 初期化中に遷移
    }
    else
    {
        mSubRun->run();     // サブ走行をする
    }
}

/* 初期化する */
void Step::init()
{
    if (mInit->checkState(InitMotor::EState::FIN))  // 初期化が終了したか判定
    {
        switchState(EState::FIN);   // 終了状態に遷移
    }
    else
    {
        mInit->init();  // 初期化する
    }
}

/* 状態を切り替える */
void Step::switchState(EState state)
{
    mState = state;
}
