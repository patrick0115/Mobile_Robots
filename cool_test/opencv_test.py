import cv2

# 選擇第二隻攝影機
cap = cv2.VideoCapture(2)

while(True):
# 從攝影機擷取一張影像
    ret, frame = cap.read()

# 透過轉換函式轉為灰階影像
    grayImg = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) 

    color = (0, 255, 0)  

# OpenCV 人臉識別分類器
    face_classifier = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")

# 調用偵測識別人臉函式
    faceRects = face_classifier.detectMultiScale(
        grayImg, scaleFactor=1.2, minNeighbors=3, minSize=(32, 32))

# 大於 0 則檢測到人臉
    if len(faceRects):
        # 框出每一張人臉
        for faceRect in faceRects:
            x, y, w, h = faceRect
            cv2.rectangle(frame, (x, y), (x + h, y + w), color, 2)
#顯示圖片
    cv2.imshow('frame', frame)

# 若按下 q 鍵則離開迴圈
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 釋放攝影機
cap.release()

# 關閉所有 OpenCV 視窗
cv2.destroyAllWindows()
