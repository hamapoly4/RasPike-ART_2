#ifndef ___RUN__CLASS
#define ___RUN__CLASS

#include <cstdint>
#include "Control.hpp"
#include "Motor.hpp"

namespace debrisys {

class Run {
protected:
    const Motor& mLeftMotor;
    const Motor& mRightMotor;
    Control* mTuRn;

    int8_t mTurn;

    Run(const Motor& leftmotor, const Motor& rightmotor, Control* turn)
        : mLeftMotor(leftmotor), mRightMotor(rightmotor), mTuRn(turn)
    {
        ;
    }

public:
    virtual void run() = 0;

};  // class Run

}   // namespace debrisys

#endif // ___RUN__CLASS
