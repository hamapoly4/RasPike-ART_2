#ifndef ___STEP__CLASS
#define ___STEP__CLASS

#include "Run.hpp"
#include "Judge.hpp"
#include "InitMotor.hpp"

namespace debrisys {

class Step {
public:
    enum class EState { RUN, INIT, FIN, };

private:
    Run*        mRun;
    Judge*      mJudge;
    InitMotor*  mInit;

    EState mState;
    EState mOldState;

    void run();
    void init();
    void switchState(EState state);

public:
    Step(Run* run, Judge* judge, InitMotor* init)
        : mRun(run), mJudge(judge), mInit(init), mState(EState::RUN), mOldState(EState::RUN)
    {
        ;
    }

    void execute();

    bool checkState(EState state) const
    {
        bool result = false;
        if (state == mState)
        {
            result = true;
        }
        return result;
    }

};  // class Step

}   // namespace debrisys

#endif // ___STEP__CLASS
