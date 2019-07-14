import cv2
import numpy as np

cap = cv2.VideoCapture('videos/1.mp4')
num = 1

# COLOR_MIN_RED = np.array([161, 155, 84], np.uint8)
# COLOR_MAX_RED = np.array([179, 255, 255], np.uint8)

COLOR_MIN_RED = np.array([170, 120, 70], np.uint8)
COLOR_MAX_RED = np.array([180, 255, 255], np.uint8)

COLOR_MIN_BLUE = np.array([94, 80, 2], np.uint8)
COLOR_MAX_BLUE = np.array([126, 255, 255], np.uint8)

COLOR_MIN_GREEN = np.array([25, 52, 72], np.uint8)
COLOR_MAX_GREEN = np.array([102, 255, 255], np.uint8)

COLOR_MIN_YELLOW = np.array([20, 100, 100], np.uint8)
COLOR_MAX_YELLOW = np.array([30, 255, 255], np.uint8)

while (cap.isOpened()):
    # name = "./test_images/img_" + str(num) + ".jpg"
    # name = "test_images/test.png"
    # frame = cv2.imread(name)
    # frame = cv2.resize(frame, (300,300))
    # frame = cv2.fastNlMeansDenoisingColored(frame, None, 10, 10, 7, 21) # ????? 존나흐려지는
    _, frame = cap.read()
    # frame = cv2.bilateralFilter(frame, 9, 75, 75) # 선명도가 낮아짐...되게 흐려진다. 상대적으로 색은 더 또렷해지는 느낌?

    num += 1

    # _, frame = cap.read()
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    frame_threshed = cv2.inRange(hsv_frame, COLOR_MIN_RED, COLOR_MAX_RED)

    imgray = frame_threshed
    ret, thresh = cv2.threshold(frame_threshed, 127, 255, 0)
    contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for cnt in contours:
        x, y, w, h = cv2.boundingRect(cnt)
        if w > 25 and h > 25:
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
            print(hsv_frame)

    cv2.imshow("final", frame)

    # 빨간색 detection

    """
    # Every color except white
    low = np.array([0, 42, 0])
    high = np.array([179, 255, 255])
    mask = cv2.inRange(hsv_frame, low, high)
    result = cv2.bitwise_and(frame, frame, mask=mask)

    low_red = np.array([161, 155, 84])
    high_red = np.array([179, 255, 255])
    red_mask = cv2.inRange(hsv_frame, low_red, high_red)
    red = cv2.bitwise_and(frame, frame, mask=red_mask)
    """

    # v2.imshow("Red", result)
    # cv2.imshow("red2", frame)
    # cv2.imshow("Red", red)

    key = cv2.waitKey(1)
    if key == 27:
        break