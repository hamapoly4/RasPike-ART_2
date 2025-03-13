import cv2
from multiprocessing import shared_memory
import numpy as np
import struct

cap = cv2.VideoCapture(0)
if not cap.isOpened():
	print("camera don't open")
	exit()

# データを準備
blue_pixels = 0

# 共有メモリ作成
shm = shared_memory.SharedMemory(name="yuta", create=True, size=struct.calcsize('i'))

while True:
	ret, frame = cap.read()
	if not ret:
		print("image don't get")
		break
		
	x, y, w, h = 185, 100, 200, 210
	roi = frame[y:y+h, x:x+w]

	# convert BGR image to HSV image
	hsv_roi = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
	
	lower_blue = np.array([95, 100, 0])
	upper_blue = np.array([105, 255, 255])
	
	mask = cv2.inRange(hsv_roi, lower_blue, upper_blue)
	
	cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
	
	blue_pixels = cv2.countNonZero(mask)
	
	print(blue_pixels)

	# 共有メモリにデータを書き込み
	buffer = shm.buf
	struct.pack_into('i', buffer, 0, blue_pixels)
	
	cv2.imshow("original", frame)
	cv2.imshow("Blue Extracted", mask)
	
	if cv2.waitKey(30) & 0xFF == ord('q'):
		break

cap.release()
cv2.destroyAllWindows()
shm.close()
shm.unlink()    #memorikaihou
