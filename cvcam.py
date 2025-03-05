import cv2

#カメラを初期化
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("カメラを開くことができませんでした")
    exit()

while True:
    ret, frame = cap.read() #カメラから画像を取得
    if not ret:
        print("フレームを取得できませんでした")
        break

    cv2.imshow("window", frame)     #フレームを表示
    cv2.imwrite("~/work_RasPike-ART/RasPike/sdk/workspace/image.jpg", frame)    #フレームを保存

    #'q'キーが押されたらループを終了
    if cv2.waitKey(30) & 0xFF == ord('q'):
        break

#リソースを解放
cap.release()
cv2.destroyWindow("window")
