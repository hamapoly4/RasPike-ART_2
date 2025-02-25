#include "Route.hpp"

using namespace debrisys;   // 名前空間debrisys

/* 走行する */
void Route::run()
{
    mSection->execute();    // 区間を実行
    if (mSection->checkFinFlag())   // 区間が終了したか判定
    {
        switchSect();   // 区間の切り替え
    }
}

/* 区間を切り替える */
void Route::switchSect()
{
    mSectNum++;     // 区間番号をインクリメント
}
