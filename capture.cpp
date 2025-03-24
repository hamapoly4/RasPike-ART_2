#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap(0); // カメラデバイスを開く
    if (!cap.isOpened()) {
        std::cerr << "カメラが開けません" << std::endl;
        return -1;
    }

    cv::Mat frame;
    cap >> frame; // フレームをキャプチャ

    if (frame.empty()) {
        std::cerr << "フレームが空です" << std::endl;
        return -1;
    }

    cv::imwrite("captured_image.jpg", frame); // 画像を保存
    std::cout << "画像を保存しました: captured_image.jpg" << std::endl;

    return 0;
}
