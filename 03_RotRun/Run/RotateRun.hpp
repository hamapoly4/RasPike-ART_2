#ifndef ___ROTATE_RUN__CLASS
#define ___ROTATE_RUN__CLASS

#include "enum_class.hpp"
#include "Run.hpp"
#include "Motor.hpp"

namespace debrisys {

class RotateRun : public Run {
private:
    Control* mTuRn1;

    int8_t mTurn1;
    static const int8_t mPOWER = 37;
    ERotDire mDirection;

    void rotateLeft();
    void rotateRight();

public:
    RotateRun(Motor& leftmotor, Motor& rightmotor, Control* turn1, Control* turn2, ERotDire direction)
        : Run(leftmotor, rightmotor, turn1), mTuRn1(turn2), mDirection(direction)
    {
        ;
    }

    void run();

};  // class RotateRun

}   // namespace debrisys

#endif // ___ROTATE_RUN__CLASS
