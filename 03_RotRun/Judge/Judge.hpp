#ifndef ___JUDGE__CLASS
#define ___JUDGE__CLASS

namespace debrisys {

class Judge {
protected:
    bool mResult;
    float mTarget;
    float mMeasure;

    Judge(float target)
        : mResult(false), mTarget(target)
    {
        ;
    }

public:
    virtual bool judge() = 0;

};  // class Judge

}   // namespace debrisys

#endif // ___JUDGE__CLASS
