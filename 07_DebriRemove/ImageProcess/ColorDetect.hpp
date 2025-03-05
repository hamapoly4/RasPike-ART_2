#ifndef ___COLOR_DETECT__CLASS
#define ___COLOR_DETECT__CLASS

#include <cstdint>
#include <opencv2/opencv.hpp>
#include "app.h"
#include "enum_class.hpp"
#include "Camera.hpp"
#include "ColorExtract.hpp"
#include "ExtractRange.hpp"

namespace debrisys {

class ColorDetect {
private:
    /* インスタンス */
    Camera*         mBottleImg;     // ボトル画像
    ColorExtract*   mColorExt;      // 色抽出
    ExtractRange*   mBottleLimit;   // ボトル限定

    /* 属性 */
    EColor      mBottleC;   // ボトルの色
    uint16_t    mPixelC;    // 色ピクセル数
    cv::Mat     mCameraImg; // カメラ画像
    cv::Mat     mExtImg;    // 指定色抽出画像
    cv::Mat     mExtRoi;    // 抽出範囲限定画像

public:
    /* コンストラクタ */
    ColorDetect(Camera* bottleimg, ColorExtract* colorext, ExtractRange* bottlelimit)
        : mBottleImg(bottleimg), mColorExt(colorext), mBottleLimit(bottlelimit)
    {
        ;
    }

    /* 色を検出する */
    EColor detectColor()
    {
        while (mBottleImg->checkFlag() == false)    // 画像取得フラグが降りていれば判定
        {
            wup_tsk(MAIN_TASK);     // メインタスクを起動
        }
        mBottleImg->readImage(mCameraImg);              // 画像を読み取る
        mColorExt->getExtImg(mCameraImg, mExtImg);      // 抽出画像を取得
        mBottleLimit->narrowRange(mExtImg, mExtRoi);    // 抽出範囲を絞る

        mPixelC = cv::countNonZero(mExtRoi);    // 色ピクセル数を求める
        if (mPixelC >= 10000)
        {
            mBottleC = EColor::BLUE;    // 青色だと判断
        }
        else
        {
            mBottleC = EColor::RED;     // 赤色だと判断
        }

        return mBottleC;
    }

};  // class ColorDetect

}   // namespace debrisys

#endif // ___COLOR_DETECT__CLASS
