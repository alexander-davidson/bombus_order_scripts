import numpy
import cv2
import os
import gc # garbage collector otherwise not enough memory

gc.enable()

# set the directory containing image files
img_path = "D:\ALEX\\2025\qr_test_videos\close_up_tunnel_test"

# create list containing names of files in the directory
files = os.listdir(img_path)

# make a list containing all the images
frame_list = [cv2.imread(f"{img_path}\{i}") for i in files]

# set parameters for writing to mp4
writer = cv2.VideoWriter("outputvideo.mp4",cv2.VideoWriter_fourcc(*"MP4V"),30,(512,512))

# loop taking images, resizing (to match the writer parameter above) and adding the frames
for i in range(0, len(files)):
    resiz = cv2.resize(frame_list[i], (512, 512))
    writer.write(resiz)
writer.release()