import os
import cv2
import schedule
import time
from pathlib import Path
from datetime import datetime

# Define your save directory
save_dir = Path(r'/Users/alexander/Documents/test_bee_dir/testing_capture')

def capture_job():
    cap = cv2.VideoCapture(0)
    ret, frame = cap.read()

    if ret:
        timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        filename = f"image_{timestamp}.jpg"

        file_path = save_dir / filename

        # Note: cv2.imwrite expects a string, so we convert the Path object
        cv2.imwrite(str(file_path), frame)

    cap.release()

# define how often the camera grabs an image
schedule.every(1).minute.do(capture_job)

# Run the first capture immediately
capture_job()

while True:
    # This checks if any scheduled task is due and runs it
    schedule.run_pending()
    time.sleep(1) # Wait 1 second between checks to save CPU power


