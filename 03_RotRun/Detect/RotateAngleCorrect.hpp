#ifndef ___ROTATE_ANGLE_CORRECT__CLASS
#define ___ROTATE_ANGLE_CORRECT__CLASS

namespace debrisys {

class RotateAngleCorrect {
private:
    static constexpr float mOFFSET = 0.00076732;

public:
    RotateAngleCorrect()
    {
        ;
    }

    void correct(float& rolla) const
    {
        rolla += mOFFSET;
    }

};  // class RotateAngleCorrect

}   // namespace debrisys

#endif // ___ROTATE_ANGLE_CORRECT__CLASS
