import cv2

#カメラを初期化
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("カメラを開くことができませんでした")
    exit()

ret, frame = cap.read() #カメラから画像を取得
if not ret:
    print("フレームを取得できませんでした")

cv2.imwrite("/home/user/work_RasPike-ART/RasPike/sdk/workspace/image.jpg", frame)	#フレームを保存

#リソースを解放
cap.release()
