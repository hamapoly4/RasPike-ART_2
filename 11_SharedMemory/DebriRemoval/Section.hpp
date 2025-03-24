#ifndef ___SECTION__CLASS
#define ___SECTION__CLASS

#include "MainRun.hpp"

namespace debrisys {

class Section {
private:
    /* インスタンス */
    MainRun* mMainRun; // 各エリア

    /* 属性 */
    bool mFinFlag;  // 終了フラグ

public:
    /* コンストラクタ */
    Section(MainRun* mainrun)
        : mMainRun(mainrun), mFinFlag(false)
    {
        ;
    }

    /* 実行する */
    void execute()
    {
        mMainRun->run();   // メイン走行をする
        if (mMainRun->checkState(MainRun::EState::FIN))    // メイン走行が終了したか判定
        {
            mFinFlag = true;    // 区間が終了した
        }
    }

    /* 終了フラグを確認する */
    bool checkFinFlag() const
    {
        return mFinFlag;    // 終了フラグを返却
    }

};  // class Section

}   // namespace debrisys

#endif // ___SECTION__CLASS
