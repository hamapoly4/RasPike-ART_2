import cv2

# カメラデバイスの取得（デフォルトでID 0を使用）
cap = cv2.VideoCapture(0)

def main():
    # フレームの取得
    ret, frame = cap.read()
    
    # フレームが正しく取得できたか確認
    if not ret:
        return

    # フレームを表示
    cv2.imshow('frame', frame)

    # 'q' キーが押されたらループを終了
    if cv2.waitKey(1) & 0xFF == ord('q'):
        return

    # カメラデバイスを解放
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
