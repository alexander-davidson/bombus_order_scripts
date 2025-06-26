import os
import cv2
from datetime import datetime

# path = r'D:\ALEX\2025\pyprojects\get_frames\frames'
path = r'D:\Order_Discrimination_Bombus\live_frame_storage' # 2.07 PC

# checking git from onedrive

os.chdir(path)

i = 1
wait = 0

video = cv2.VideoCapture(0)
video.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
video.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)

while True:
    ret, img = video.read()

    font = cv2.FONT_HERSHEY_PLAIN
    cv2.putText(img, str(datetime.now()), (20, 40),
                font, 2, (255, 255, 255), 2, cv2.LINE_AA)

    # Display the image
    cv2.imshow('live video', img)

    # wait for user to press any key
    key = cv2.waitKey(100)

    # wait variable is to calculate waiting time
    wait = wait + 100

    if key == ord('q'):
        break
    # when it reaches to 5000 milliseconds
    # we will save that frame in given folder
    if wait == 100:
        filename = 'Frame_' + str(i) + '.jpg'

        # Save the images in given path
        cv2.imwrite(filename, img)
        i = i + 1
        #wait = 0
    #if i >= 5:
        #i = 1

# close the camera
video.release()

# close open windows
cv2.destroyAllWindows()