#ifndef ___DEBRI_REMOVE__CLASS
#define ___DEBRI_REMOVE__CLASS

#include <cstdint>
#include "MainRun.hpp"
#include "Circle.hpp"

namespace debrisys {

class DebriRemove : public MainRun {
private:
    /* インスタンス */
    Circle* mCircle;    // サークル1~4

    void circleRun(uint8_t num);    // サークル走行をする

public:
    /* コンストラクタ */
    DebriRemove(Circle* circle)
        : mCircle(circle), MainRun(EState::CIRCLE1_RUN)
    {
        ;
    }

    void run();     // 走行する

};  // class DebriRemove

}   // namespace debrisys

#endif // ___DEBRI_REMOVE__CLASS
