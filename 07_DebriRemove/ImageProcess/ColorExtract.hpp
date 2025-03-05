#ifndef ___COLOR_EXTRACT___CLASS
#define ___COLOR_EXTRACT___CLASS

#include <cstdint>
#include <opencv2/opencv.hpp>

namespace debrisys {

class ColorExtract {
public:
    /* HSV値に関する構造体 */
    struct HSV {
        uint8_t h;  // 色相
        uint8_t s;  // 彩度
        uint8_t v;  // 明度
    };

private:
    /* 属性 */
    cv::Mat     mHsvImage;      // HSV画像
    cv::Scalar  mLowerColor;    // 指定色下限HSV値
    cv::Scalar  mUpperColor;    // 指定色上限HSV値

public:
    /* コンストラクタ */
    ColorExtract(HSV lowercolor, HSV uppercolor)
        : mLowerColor{ static_cast<float>(lowercolor.h), static_cast<float>(lowercolor.s), static_cast<float>(lowercolor.v) },
            mUpperColor{ static_cast<float>(uppercolor.h), static_cast<float>(uppercolor.s), static_cast<float>(uppercolor.v) }
    {
        ;
    }

    /* 抽出画像を取得する */
    void getExtImg(const cv::Mat& img, cv::Mat& ext_img) const
    {
        mHsvImage.create(img.size(), img.type());                   // 初期化
        cv::cvtColor(img, mHsvImage, cv::COLOR_BGR2HSV, 3);         // HSV画像に変換
        cv::inRange(mHsvImage, mLowerColor, mUpperColor, ext_img);  // 指定色を抽出
    }

};  // class ColorExtract

}   // namespace debrisys

#endif // ___COLOR_EXTRACT___CLASS
