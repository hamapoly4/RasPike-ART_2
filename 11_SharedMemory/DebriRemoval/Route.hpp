#ifndef ___ROUTE__CLASS
#define ___ROUTE__CLASS

#include <cstdint>
#include "Section.hpp"

namespace debrisys {

class Route {
private:
    /* インスタンス */
    Section* mSection;  // 各区間

    /* 属性 */
    uint8_t mSectNum;   // 区間番号

    /* メソッド */
    void switchSect();  // 区間を切り替える

public:
    /* コンストラクタ */
    Route(Section* section)
        : mSection(section), mSectNum(0)
    {
        ;
    }

    /* 走行する */
    void run();

    /* 区間を読み取る */
    uint8_t readSectNum()
    {
        return mSectNum;    // 区間番号を返却
    }

};  // class Route

}   // namespace debrisys

#endif // ___ROUTE__CLASS
