imagedir = "C:\Users\bty571\OneDrive - Queen Mary, University of London\Documents\alex\bombus_order_scripts-main\test_bee_image\";
% change filepath based on which computer

files = dir(fullfile(imagedir, '*.png'));
% check filetype and make sure the code matches
files = {files.name}

im = imread(imagedir+files(1, 1));
% locateCodes(im, 'vis', 1);

manual_thresh = 0.2;

for i = 1:500;
    try
        locateCodes(im, 'thresh', manual_thresh, 'vis', 1);
        disp(ans.number);

    catch ME
        manual_thresh = manual_thresh + 0.001;
    end
end
