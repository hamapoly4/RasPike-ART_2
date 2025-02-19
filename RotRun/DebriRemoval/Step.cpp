#include "Step.hpp"

using namespace debrisys;

void Step::execute()
{
    do {
        mOldState = mState;
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
    } while (mOldState != mState);
}

void Step::run()
{
    if (mJudge->judge())
    {
        switchState(EState::INIT);
    }
    else
    {
        mRun->run();
    }
}

void Step::init()
{
    if (mInit->checkFinFlag())
    {
        switchState(EState::FIN);
    }
    else
    {
        mInit->init();
    }
}

void Step::switchState(EState state)
{
    mState = state;
}
