import cv2
import numpy as np
import argparse
import time

DEFAULT_SIZE = 10

num = 1
detect = False
x = 0
y = 0
w = 0
h = 0

detect_x = 0
detect_y = 0
detect_w = 0
detect_h = 0

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

#cap = cv2.VideoCapture(0)
cap = cv2.VideoCapture("videos/4.mp4")

while (cap.isOpened()):
    if detect == True :
        _, frame = cap.read()

        crop_frame = frame[(detect_y):(detect_y + detect_h), (detect_x + detect_w):]

        crop_hsv_frame = cv2.cvtColor(crop_frame, cv2.COLOR_BGR2HSV)
        crop_frame_threshed = cv2.inRange(crop_hsv_frame, COLOR_MIN_RED, COLOR_MAX_RED)

        imgray = crop_frame_threshed
        crop_ret, crop_thresh = cv2.threshold(crop_frame_threshed, 127, 255, 0)
        crop_contours, crop_hierarchy = cv2.findContours(crop_thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        print("crop_contours : ", crop_contours)
        cv2.imshow("crop_frame", crop_frame)
        for cnt in crop_contours:
            x2, y2, w2, h2 = cv2.boundingRect(cnt)
            
            if w2 > DEFAULT_SIZE and h2 > DEFAULT_SIZE:
                detect = 0
                cv2.rectangle(crop_frame, (x2, y2), (x2 + w2, y2 + h2), (255, 0, 0), 2)
                print("GREEN!!!!!!!!!!!!")
                detect = False
                break

        if detect == False :
            break

        key = cv2.waitKey(1)
        if key == 27:
            break

    #frame = cv2.bilateralFilter(frame, 9, 75, 75)
    else :
        _, frame = cap.read()
        hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        frame_threshed = cv2.inRange(hsv_frame, COLOR_MIN_RED, COLOR_MAX_RED)

        imgray = frame_threshed
        ret, thresh = cv2.threshold(frame_threshed, 127, 255, 0)
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        for cnt in contours:
            x, y, w, h = cv2.boundingRect(cnt)


            if w > DEFAULT_SIZE and h > DEFAULT_SIZE:
                print(contours)
                detect_x = x
                detect_y = y
                detect_w = w
                detect_h = h
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
                detect = True
                time.sleep(3)

        cv2.imshow("final", frame)

        key = cv2.waitKey(1)
        if key == 27:
            break