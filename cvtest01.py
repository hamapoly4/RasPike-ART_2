import cv2

cap = cv2.VideoCapture(0)  # カメラを開く
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

while True:
    ret, frame = cap.read()  # フレームを読み込む
    if not ret:
        print("Error: Could not read frame.")
        break

    cv2.imshow('frame', frame)  # フレームを表示する
    if cv2.waitKey(1) & 0xFF == ord('q'):  # 'q'キーが押されたらループを終了
        break

cap.release()
cv2.destroyAllWindows()
