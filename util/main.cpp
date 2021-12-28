#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/types_c.h>
using namespace cv;
using namespace std;
#define WIDTH 1280
#define HEIGHT 720
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
    //double delay = rate / 1000;
    //for the while loop
    bool stop = false;
    Mat frame, preFrame(WIDTH, HEIGHT, CV_8UC1), curFrame(WIDTH, HEIGHT, CV_8UC1), result(WIDTH, HEIGHT, CV_8UC1);
    Mat composeFrame(1500, 1000, CV_8UC1), ROI;
    long currentFrame = frameToStart;
    vector<Mat> Template;
    double minValue, maxValue;
    Point minLocP, maxLocP;

    //                             done pre setting                                //
    while (!stop)
    {

        if (!capture.read(frame))
        {
            cout << "fail to read frame" << endl;
            return -1;
        }

        if (int(currentFrame) == 1)
        {
            cvtColor(frame, curFrame, CV_RGB2GRAY);
        }
        if (currentFrame % 30 == 0) //do per 30 frame
        {

            preFrame = curFrame;
            cvtColor(frame, curFrame, CV_RGB2GRAY);
            for (size_t x = 0; x < (WIDTH / 40); x++)
            {
                for (size_t y = 0; y < (HEIGHT / 40); y++)
                {
                    Rect rect(x * 40, y * 40, 40, 40);
                    Template.push_back(preFrame(rect));
                    //imwrite(to_string(x) + "," + to_string(y) + ".png", Template.back());
                }
            }

            for (size_t i = 0; i < Template.size(); i++)
            {
                matchTemplate(curFrame, Template[i], result, TM_SQDIFF_NORMED);
                normalize(result, result, 0, 255, NORM_MINMAX, CV_8UC1);
                minMaxLoc(result, &minValue, &maxValue, &minLocP, &maxLocP, Mat());
                ROI = composeFrame(Rect(minLocP.x, minLocP.y, Template[i].cols, Template[i].rows));
                addWeighted(ROI, 0.5, Template[i], 0.5, 0, ROI);
                //cout << minLocP.x << "," << minLocP.y << endl;
            }

            cout << "working on frame " << currentFrame << endl;
            stringstream str;
            str << currentFrame << ".png";
            imwrite(str.str(), composeFrame);
        }
        //int c = waitKey(delay);
        if (currentFrame > frameToStop)
        {
            stop = true;
        }
        currentFrame++;
    }

    //close video
    capture.release();
    waitKey(0);

    return 0;
}
