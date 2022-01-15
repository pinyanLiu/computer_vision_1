#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
//#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
//#include <opencv4/opencv2/imgproc/types_c.h>
#include <opencv4/opencv2/tracking/tracker.hpp>
#include <opencv4/opencv2/core/utility.hpp>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        cout << "please enter the path of video" << endl;
        cout << "and the level  " << endl;
        cout << "for example: ./with_lib ../Video.avi 1" << endl;
        return 0;
    }
    VideoCapture capture(argv[1]);
    if (!capture.isOpened())
        cout << "fail to open " << argv[1] << endl;
    //count total frames
    long totalFrameNumber = capture.get(CAP_PROP_FRAME_COUNT);
    cout << "total " << totalFrameNumber << " frames in this video" << endl;

    int frameToStart, frameToStop;
    fstream fs;
    vector<int> Frame;
    vector<int> IDnumber;
    vector<int> Xmin;
    vector<int> Ymin;
    vector<int> Width;
    vector<int> Hight;
    if (argv[2] == "1")
    {
        //set start frame
        frameToStart = 68;
        capture.set(CAP_PROP_POS_FRAMES, frameToStart);
        //set finish frame
        frameToStop = 146;
        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;

        //read txt file
        fs.open("Level.txt", ios::in);
        if (!fs.is_open())
        {
            cout << "Failed to open file.\n";
        }
        else
        {
            int frame;
            int iDnumber;
            int xmin;
            int ymin;
            int width;
            int hight;
            while (fs >> frame >> iDnumber >> xmin >> ymin >> width >> hight)
            {
                Frame.push_back(frame);
                IDnumber.push_back(iDnumber);
                Xmin.push_back(xmin);
                Ymin.push_back(ymin);
                Width.push_back(width);
                Hight.push_back(hight);
            }
        }
        fs.close();
    }
    else if (argv[2] == "2")
    {
        //set start frame
        frameToStart = 68;
        capture.set(CAP_PROP_POS_FRAMES, frameToStart);
        //set finish frame
        frameToStop = 214;
        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
    }
    else if (argv[2] == "3")
    {
        //set start frame
        frameToStart = 367;
        capture.set(CAP_PROP_POS_FRAMES, frameToStart);
        //set finish frame
        frameToStop = 464;
        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
    }
    else if (argv[2] == "4")
    {
        //set start frame
        frameToStart = 1;
        capture.set(CAP_PROP_POS_FRAMES, frameToStart);
        //set finish frame
        frameToStop = 375;
        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
    }
    else if (argv[2] == "5")
    {
        //set start frame
        frameToStart = 224;
        capture.set(CAP_PROP_POS_FRAMES, frameToStart);
        //set finish frame
        frameToStop = 253;
        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
    }
    else if (argv[2] == "6")
    {
        //set start frame
        frameToStart = 224;
        capture.set(CAP_PROP_POS_FRAMES, frameToStart);
        //set finish frame
        frameToStop = 430;
        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
    }

    // get FPS
    double rate = capture.get(CAP_PROP_FPS);
    cout << "FPS: " << rate << endl;
    //parameters for the while loop
    bool stop = false;
    Mat frame;
    long currentFrame = 0;
    double minValue, maxValue;
    vector<string> str;
    ofstream ofs;

    Ptr<TrackerTLD> tldTracker = TrackerTLD::create();
    Ptr<TrackerKCF> kcfTracker = TrackerKCF::create();
    Ptr<TrackerCSRT> csrtTracker = TrackerCSRT::create();

    //                             done pre setting                                //

    while (!stop)
    {
        capture >> frame;
        if (!capture.read(frame))
        {
            cout << "fail to read frame" << endl;
            return -1;
        }

        //set tracker
        if (currentFrame == frameToStart)
        {
            if (argv[2] == "1")
            {
                Rect2d Rect1(Xmin[0], Ymin[0], Width[0], Hight[0]);
                csrtTracker->init(frame, Rect1);
            }
            // else if (argv[2] == "2")
            // {
            // }
            // else if (argv[2] == "3")
            // {
            // }
            // else if (argv[2] == "4")
            // {
            // }
            // else if (argv[2] == "5")
            // {
            // }
            // else if (argv[2] == "6")
            // {
            // }
            // else if (argv[2] == "All")
            // {
            // }
        }

        //tracker update

        if (argv[2] == "1")
        {
            csrtTracker->update(frame, Rect1);
        }
        // else if (argv[2] == "2")
        // {
        // }
        // else if (argv[2] == "3")
        // {
        // }
        // else if (argv[2] == "4")
        // {
        // }
        // else if (argv[2] == "5")
        // {
        // }
        // else if (argv[2] == "6")
        // {
        // }
        // else if (argv[2] == "All")
        // {
        // }

        //output
        //stringstream str;
        //str << currentFrame << ".jpg";
        //imwrite(str.str(), composeFrame);

        currentFrame++;
        if (currentFrame >= frameToStop)
        {
            stop = true;
        }
    }

    if (argv[2] == "1")
    {
        ofs.open("Tlevel1.txt");
    }
    // else if (argv[2] == "2")
    // {
    //ofs.open("Tlevel2.txt");

    // }
    // else if (argv[2] == "3")
    // {
    //ofs.open("Tlevel3.txt");

    // }
    // else if (argv[2] == "4")
    // {
    //ofs.open("Tlevel4.txt");

    // }
    // else if (argv[2] == "5")
    // {
    //ofs.open("Tlevel5.txt");

    // }
    // else if (argv[2] == "6")
    // {
    //ofs.open("Tlevel6.txt");

    // }
    if (!ofs.is_open())
    {
        cout << "Failed to open file.\n";
    }
    else
    {
        for (auto &s : str)
        {
            ofs << s;
        }
        ofs.close();
    }
    //close video
    capture.release();

    return 0;
}
