#ifndef ___CIRCLE__CLASS
#define ___CIRCLE__CLASS

#include <cstdint>
#include "Step.hpp"

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

    /* 属性*/
    EState  mState;     // 状態
    bool    mBottle;    // ボトルの有無
    static uint32_t mBluePixels;

    /* メソッド */
    void exeStep(uint8_t num);      // 手順を実行する
    void findBottle();              // ボトルの有無を認識する
    void judgeColor();              // ボトルの色を判定する
    void switchState(EState state); // 状態を切り替える

public:
    /* コンストラクタ */
    Circle(Step* step, bool bottle)
        : mStep(step), mState(EState::BOTTLE_EXIST), mBottle(bottle)
    {
        ;
    }

    void run();     // 走行する
    
    static void setBluePixels(uint32_t blue_pixels)
    {
		mBluePixels = blue_pixels;
	}

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
