#ifndef ___CONTROL__CLASS
#define ___CONTROL__CLASS

#include <cstdint>

namespace debrisys {

class Control {
protected:
    int8_t mTurn;
    float mDiff;

    Control()
    {
        ;
    }

public:
    virtual int8_t getTurn() = 0;

};  // class Control

}   // namespace debrisys

#endif // ___CONTROL__CLASS
