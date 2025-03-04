#ifndef ___CIRCLE__CLASS
#define ___CIRCLE__CLASS

#include <cstdint>
#include "enum_class.hpp"
#include "Step.hpp"
#include "ColorDetect.hpp"

namespace debrisys {

class Circle {
public:
    /* 列挙体クラス */
    enum class EState {
        BOTTLE_EXIST,  EXE_STEP1, JUDGE_COLOR,
        EXE_STEP2, EXE_STEP3, EXE_STEP4, FIN,
    };

private:
    /* インスタンス */
    Step*           mStep;          // 手順1~4
    ColorDetect*    mBlueBottle;    // 青ボトル検出

    /* 属性*/
    EState  mState;     // 状態
    bool    mBottle;    // ボトルの有無

    /* メソッド */
    void exeStep(uint8_t num);      // 手順を実行する
    void findBottle();              // ボトルの有無を認識する
    void judgeColor();              // ボトルの色を判定する
    void switchState(EState state)  // 状態を切り替える

public:
    /* コンストラクタ */
    Circle(Step* step, ColorDetect* bluebottle, bool bottle)
        : mStep(step), mBlueBottle(bluebottle),
            mState(BOTTLE_EXIST), mBottle(bottle)
    {
        ;
    }

    void run();     // 走行する

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

};  // class Circle

}   // namespace debrisys

#endif // ___CIRCLE__CLASS
