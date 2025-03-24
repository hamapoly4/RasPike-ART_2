#ifndef ___CONTROL__CLASS
#define ___CONTROL__CLASS

#include <cstdint>

namespace debrisys {

class Control {
protected:
    /* 属性 */
    int8_t mTurn;   // 操作量
    float  mDiff;   // 偏差
    float  mPvalue; // P制御値
    float  mDvalue; // D制御値

    /* コンストラクタ */
    Control()
    {
        ;
    }

public:
    virtual int8_t getTurn() = 0;   // 操作量を取得する

};  // class Control

}   // namespace debrisys

#endif // ___CONTROL__CLASS
