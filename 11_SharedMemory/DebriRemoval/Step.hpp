#ifndef ___STEP__CLASS
#define ___STEP__CLASS

#include "SubRun.hpp"
#include "Judge.hpp"
#include "InitMotor.hpp"

namespace debrisys {

class Step {
public:
    enum class EState { RUN, INIT, FIN, };  // 列挙体クラス

private:
    /* インスタンス */
    SubRun*     mSubRun;    // 各サブ走行
    Judge*      mJudge;     // 各判定
    InitMotor*  mInit;      // 初期化

    /* 属性 */
    EState mState;      // 状態
    EState mOldState;   // 過去の状態

    /* メソッド */
    void run();     // 走行する
    void init();    // 初期化する
    void switchState(EState state); // 状態を切り替える

public:
    /* コンストラクタ */
    Step(SubRun* subrun, Judge* judge, InitMotor* init)
        : mSubRun(subrun), mJudge(judge), mInit(init), mState(EState::RUN), mOldState(EState::RUN)
    {
        ;
    }

    void execute();     // 実行する

    /* 状態を確認する */
    bool checkState(EState state) const
    {
        bool result = false;
        if (state == mState)    // 状態が一致するか判定
        {
            result = true;  // 状態が一致した
        }

        return result;  // 結果を返却
    }

};  // class Step

}   // namespace debrisys

#endif // ___STEP__CLASS
