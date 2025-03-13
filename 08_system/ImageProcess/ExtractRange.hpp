#ifndef ___EXTRACT_RANGE__CLASS
#define ___EXTRACT_RANGE__CLASS

#include <opencv2/opencv.hpp>

namespace debrisys {

class ExtractRange {
private:
    /* インスタンス */
    cv::Rect mRoi = cv::Rect(200, 60, 200, 210);    // 関心領域

public:
    /* コンストラクタ */
    ExtractRange()
    {
        ;
    }

    /* 抽出範囲を絞る */
    void narrowRange(const cv::Mat& ext_img, cv::Mat& ext_roi) const
    {
        ext_roi = ext_img(mRoi);
    }

};  // class ExtractRange

}   // namespace debrisys

#endif // ___EXTRACT_RANGE__CLASS
