First ensure the pic_for_seed.jpg file is in an input directory different from the frame capture

Download the BEEtag directory from https://github.com/jamescrall/BEEtag
The .mat files must be copied into the BEEtag-master directory.

Run the make_seed_for_dot_mat_file.mat
This will create a .mat file for the data collection. The function locatecodes() will not work on Windows without a .mat file containing at least one line of data.

You should eventually remove the first line of data from the data file since it is just a placeholder. You can do this easily in R.

WHILE RUNNING THE EXPERIMENT

Run the live_feed_frame_extractor python file to capture frames from the camera. Keep this running in the
background. You can stop running by pressing ‘q’ on the python camera window

To start collecting QR data, run the qr_detect Matlab file. 

Stop running by pressing ‘q’ on the Matlab figure. 

Do not stop the script by clicking stop in Matlab because it can interrupt the loop before data is saved.

