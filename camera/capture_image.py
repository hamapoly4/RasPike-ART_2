import cv2

# カメラデバイスの取得（デフォルトでID 0を使用）
cap = cv2.VideoCapture(0)

while(True):
    # フレームの取得
    ret, frame = cap.read()
    
    # フレームが正しく取得できたか確認
    if not ret:
        break

    # フレームを表示
    cv2.imshow('frame', frame)

    # 'q' キーが押されたらループを終了
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# カメラデバイスを解放
cap.release()
cv2.destroyAllWindows()
