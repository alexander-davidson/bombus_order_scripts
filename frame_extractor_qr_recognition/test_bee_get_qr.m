imagedir = "C:\Users\bty571\OneDrive - Queen Mary, University of London\Documents\alex\bombus_order_scripts-main\test_bee_image\";
% change filepath based on which computer

files = dir(fullfile(imagedir, '*.png'));
% check filetype and make sure the code matches
files = {files.name}

im = imread(imagedir+files(1, 1));
locateCodes(im, 'vis', 1);
