#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{

    if (argc < 4)
    {
        cout << "please enter the 1.path of video 2.start frame 3.end frame" << endl;
        cout << "for example: ./with_lib ../Video.avi 1 300" << endl;
        return 0;
    }
    VideoCapture capture(argv[1]);
    if (!capture.isOpened())
        cout << "fail to open " << argv[1] << endl;
    //count total frames
    long totalFrameNumber = capture.get(CAP_PROP_FRAME_COUNT);
    cout << "total " << totalFrameNumber << " frames in this video" << endl;

    //set start frame
    int frameToStart = atoi(argv[2]);
    capture.set(CAP_PROP_POS_FRAMES, frameToStart);
    //set finish frame
    int frameToStop = atoi(argv[3]);
    if (frameToStop < frameToStart)
    {
        cout << "ERROR : frameToStop less than frameToStart" << endl;
    }
    else
    {
        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
    }
    // get FPS
    double rate = capture.get(CAP_PROP_FPS);
    cout << "FPS: " << rate << endl;
    //for the while loop
    bool stop = false;
    Mat frame;
    long currentFrame = frameToStart;
    //                             done pre setting                                //

    while (!stop)
    {
        if (!capture.read(frame))
        {
            cout << "fail to read frame" << endl;
            return -1;
        }
    }

    //close video
    capture.release();
    waitKey(0);

    return 0;
}
