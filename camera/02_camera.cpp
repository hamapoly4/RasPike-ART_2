#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    // カメラを起動（カメラ番号0を指定）
    VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "カメラが開けませんでした。" << endl;
        return -1;
    }

    Mat frame;
    // カメラから画像を取得
    capture >> frame;
    if (frame.empty()) {
        cout << "フレームが取得できませんでした。" << endl;
        return -1;
    }

    // 画像を表示
    imshow("カメラ画像", frame);

    // ESCキーが押されたらループを終了
    if (waitKey(1) == 27) {
        cv::destroyWindow("カメラ画像"); //ウィンドウを閉じる
        capture.release();
    }

    return 0;
}
