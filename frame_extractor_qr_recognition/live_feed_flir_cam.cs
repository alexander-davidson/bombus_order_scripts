using FlyCapture2Managed;
using System;
using System.IO;
using System.Threading;

class Program
{
    static void Main()
    {
        // Output directory and filename
        string outputDirectory = @"D:\Order_Discrimination_Bombus\live_frame_storage";
        string outputFilename = "latest_image.jpg";
        string fullPath = Path.Combine(outputDirectory, outputFilename);

        if (!Directory.Exists(outputDirectory))
            Directory.CreateDirectory(outputDirectory);

        ManagedBusManager busMgr = new ManagedBusManager();
        ManagedCamera cam = new ManagedCamera();

        try
        {
            // Connect to the first camera
            ManagedPGRGuid guid = busMgr.GetCameraFromIndex(0);
            cam.Connect(guid);
            Console.WriteLine("Camera connected!");

            // Start capture
            cam.StartCapture();
            Console.WriteLine("Capture started!");

            // Create ManagedImage objects once (reuse in loop)
            ManagedImage rawImage = new ManagedImage();
            ManagedImage convertedImage = new ManagedImage();

            Console.WriteLine("Press ESC to stop capturing...");

            // Continuous capture loop
            while (true)
            {
                // Stop if ESC is pressed
                if (Console.KeyAvailable && Console.ReadKey(true).Key == ConsoleKey.Escape)
                    break;

                // Retrieve latest frame
                cam.RetrieveBuffer(rawImage);

                // Convert to RGB (use RGB8)
                rawImage.Convert(PixelFormat.PixelFormatRgb8, convertedImage);

                // Save/overwrite the image
                convertedImage.Save(fullPath);

                Console.WriteLine($"Saved image to {fullPath}");

                // Optional: limit capture rate
                Thread.Sleep(100); // 100 ms = ~10 FPS
            }

            // Cleanup
            rawImage.Dispose();
            convertedImage.Dispose();

            cam.StopCapture();
            cam.Disconnect();
            Console.WriteLine("Capture stopped and camera disconnected.");
        }
        catch (Exception e)
        {
            Console.WriteLine("Error: " + e.Message);
        }

        Console.WriteLine("Program exited. Press any key to close...");
        Console.ReadKey();
    }
}
