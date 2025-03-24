#ifndef ___ROTATE_ANGLE_CORRECT__CLASS
#define ___ROTATE_ANGLE_CORRECT__CLASS

namespace debrisys {

class RotateAngleCorrect {
private:
    /* 属性 */
    static constexpr float mOFFSET = 0.00076732;    // オフセット値

public:
    /* コンストラクタ */
    RotateAngleCorrect()
    {
        ;
    }

    /* 誤差を補正する */
    void correct(float& rolla) const
    {
        rolla += mOFFSET;   // ロール角にオフセット値を加算
    }

};  // class RotateAngleCorrect

}   // namespace debrisys

#endif // ___ROTATE_ANGLE_CORRECT__CLASS
