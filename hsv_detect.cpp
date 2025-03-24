#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

// 抽出する画像の輝度値の範囲を指定
#define H_MAX 105
#define H_MIN 95
#define S_MIN 50

void write_file(unsigned int data)
{
	FILE* fp;
	
	fp = fopen("color_data.txt", "w");
	if (fp == NULL)
	{
		return;
	}
	else
	{
		fprintf(fp, "%d\n", data);
		fflush(fp); // バッファをフラッシュしてディスクに書き込む
		fclose(fp);
	}
}

// メイン関数
int main(void)
{
	unsigned char hue;
	unsigned char sat;
	unsigned char val;
	
	unsigned int blue_data = 0;
	
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
	Mat hsv_image;
	cvtColor(input_image_rgb, hsv_image, COLOR_BGR2HSV, 3);

	// HSV変換した画像を表示して確認
	namedWindow("input_HSV");
	imshow("input_HSV", hsv_image);
	imwrite("hsv.jpg", hsv_image);

	for(int y = 0; y < hsv_image.rows; y++) {
		for (int x = 0; x < hsv_image.cols; x++) {
			hue = hsv_image.at<Vec3b>(y, x)[0];
			sat = hsv_image.at<Vec3b>(y, x)[1];
			val = hsv_image.at<Vec3b>(y, x)[2];

			// blue detect
			if ((hue < H_MAX && hue > H_MIN) && sat > 50) {
				blue_data++;
			}
		}
	}
	
	cout << "blue_data : " << blue_data << endl;
	write_file(blue_data);

	return 0;
}
