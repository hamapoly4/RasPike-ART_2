#ifndef ___CAMERA__CLASS
#define ___CAMERA__CLASS

#include <opencv2/opencv.hpp>

namespace debrisys {

class Camera {
private:
	/* インスタンス */
	cv::VideoCapture mCamera;	// 撮影カメラ

	/* 属性 */
	cv::Mat mImage;		// 画像
	bool	mImageFlag;	// 画像取得フラグ

public:
	/* コンストラクタ */
	Camera::Camera()
		: mImageFlag(false)
	{
		mCamera.open(0);	// カメラを開く

		if (!mCamera.isOpened())	// カメラが開けないなら判定
		{
			printf("カメラが開けません\n");
		}
	}

	/* デストラクタ */
	Camera::~Camera()
	{
		mCamera.release();	// 	カメラを解放する
	}

	/* 画像を取得する */
	void getImage()
	{
		mCamera >> mImage;	// カメラで撮る
		if (mImage.empty())	// 撮れなかったら判定
		{
			printf("フレームが空です\n");
			return;
		}
		mImageFlag = true;	// 画像取得フラグを立てる
	}

	/* 画像を読み取る */
	void readImage(cv::Mat& image) const
	{
		mImageFlag = false;	// 画像取得フラグを降ろす
		image = mImage;
	}

	/* 画像取得フラグを確認する */
	bool checkFlag() const
	{
		return mImageFlag;
	}

};  // class Camera

}   // namespace debrisys

#endif // ___CAMERA__CLASS
