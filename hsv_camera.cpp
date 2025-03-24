#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

// 抽出する画像の輝度値の範囲を指定
#define H_MAX 105
#define H_MIN 95
#define S_MAX 255
#define S_MIN 50
#define V_MAX 255
#define V_MIN 50

// メイン関数
int main(void)
{
	// 入力画像名(ファイルパス)
	string input_filename = "captured_image.jpg";

	// 画像を3チャンネル(BGR)で読み込む
	Mat input_image_rgb = imread(input_filename, IMREAD_COLOR);
	if (input_image_rgb.empty()) {
		cerr << "入力画像が見つかりません" << endl;
		return -1;
	}

	// 表示して確認
	namedWindow("input_RGB");
	imshow("input_RGB", input_image_rgb);

	// BGRからHSVへ変換
	Mat hsv_image, mask_image, output_image;
	cvtColor(input_image_rgb, hsv_image, COLOR_BGR2HSV, 3);

	// HSV変換した画像を表示して確認
	namedWindow("input_HSV");
	imshow("input_HSV", hsv_image);
	imwrite("hsv.jpg", hsv_image);

	// inRangeを用いてフィルタリング
	Scalar s_min = Scalar(H_MIN, S_MIN, V_MIN);
	Scalar s_max = Scalar(H_MAX, S_MAX, V_MAX);
	inRange(hsv_image, s_min, s_max, mask_image);

	// マスク画像を表示
	namedWindow("mask");
	imshow("mask", mask_image);
	imwrite("mask.jpg", mask_image);

	// マスクを基に入力画像をフィルタリング
	input_image_rgb.copyTo(output_image, mask_image);
	
	// 結果の表示と保存
	namedWindow("output");
	imshow("output", output_image);
	imwrite("output.jpg", output_image);
	waitKey(0);

	return 0;
}
