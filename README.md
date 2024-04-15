# VirtualDraw.cpp
This C++ code is using the OpenCV library to create a simple drawing application. 
Here's a breakdown of what the code does: 
1. The code includes the necessary OpenCV headers: `opencv2/opencv.hpp`, `opencv2/core.hpp`, `opencv2/imgproc.hpp`, and `opencv2/videoio.hpp`.
2. It declares two integer variables, `ix` and `iy`, which will be used to store the initial mouse click coordinates, and `k`, which will be used to track the mouse button state.
3. The `mouse` function is defined as a callback function for handling mouse events. When the left mouse button is clicked, it stores the click coordinates in `ix` and `iy`, and sets `k` to 1.
4. The `main` function is the entry point of the program. It creates a window named "draw" and sets the `mouse` function as the callback for mouse events in that window.
5. The code then opens a video capture device (typically the default webcam) and enters a loop.
6. Inside the loop, it reads a frame from the video capture, flips it horizontally, and displays it in the "draw" window.
7. If the user presses the Esc key (ASCII code 27) or the left mouse button is clicked (indicated by `k == 1`), the loop breaks, and the program saves the current frame as a grayscale image called `old_gray`.
8. After the loop, the program creates a vector of `cv::Point2f` called `old_pts` and initializes it with the coordinates of the initial mouse click.
9. The program then enters another loop, where it continuously reads new frames from the video capture, converts them to grayscale, and uses the OpenCV `calcOpticalFlowPyrLK` function to track the movement of the initial point.
10. Inside this loop, the program handles different key presses: - 'e' clears the drawing mask - 'c' changes the drawing color - 'g' does nothing - Any other key draws a line on the mask from the old position to the new position, and draws a circle on the new position.
11. The program then blends the current frame with the drawing mask and displays the result in the "drawing" window.
12. The program updates the `old_gray` and `old_pts` variables for the next iteration of the loop.
13. The loop continues until the user presses the Esc key. 
14. Finally, the program cleans up by destroying all windows and releasing the video capture device.
