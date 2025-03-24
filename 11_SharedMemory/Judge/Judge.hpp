#ifndef ___JUDGE__CLASS
#define ___JUDGE__CLASS

namespace debrisys {

class Judge {
protected:
    /* 属性 */
    bool mResult;   // 判定結果
    float mTarget;  // 目標値
    float mMeasure; // 検出値

    /* コンストラクタ */
    Judge(float target)
        : mResult(false), mTarget(target)
    {
        ;
    }

public:
    virtual bool judge() = 0;   // 判定する

};  // class Judge

}   // namespace debrisys

#endif // ___JUDGE__CLASS
