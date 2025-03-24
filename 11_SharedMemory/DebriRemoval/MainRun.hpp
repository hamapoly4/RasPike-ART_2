#ifndef ___MAIN_RUN__CLASS
#define ___MAIN_RUN__CLASS

namespace debrisys {

class MainRun {
public:
    /* 列挙体クラス */
    enum class EState {
        EXE_STEP1, EXE_STEP2,
        CIRCLE1_RUN, CIRCLE2_RUN, CIRCLE3_RUN, CIRCLE4_RUN, FIN,
    };

protected:
    /* 属性 */
    EState mState;

    /* コンストラクタ */
    MainRun(EState state)
        : mState(state)
    {
        ;
    }

    /* 状態を切り替える */
    void switchState(EState state)
    {
        mState = state;
    }

public:
    virtual void run() = 0;     // 走行する

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

};  // class MainRun

}   // namespace debrisys

#endif // ___MAIN_RUN__CLASS
