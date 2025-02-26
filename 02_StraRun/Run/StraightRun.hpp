#ifndef ___STRAIGHT_RUN__CLASS
#define ___STRAIGHT_RUN__CLASS

#include <cmath>
#include "enum_class.hpp"
#include "Run.hpp"
#include "Control.hpp"
#include "Motor.hpp"

namespace debrisys {

class StraightRun : public Run {
private:
    static const int8_t mPOWER = 45;
    EStraDire mDirection;

    void runFront();
    void runBehind();

public:
    StraightRun(Motor& leftmotor, Motor& rightmotor, Control* turn, EStraDire direction)
        : Run(leftmotor, rightmotor, turn), mDirection(direction)
    {
        ;
    }

    void run();

};  // class StraightRun

}   // namespace debrisys

#endif // ___STRAIGHT_RUN__CLASS
