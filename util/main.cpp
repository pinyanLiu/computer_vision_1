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

int readGroundtruth(string Filename, vector<int> *Frame, vector<int> *IDnumber, vector<int> *Xmin, vector<int> *Ymin, vector<int> *Width, vector<int> *Hight);
int writeAnswer(string Filename, int FrameSize, int numOfTarget, vector<int> Frame, vector<int> IDnumber, vector<int> TXmin[4], vector<int> TYmin[4], vector<int> TWidth[4], vector<int> THight[4]);

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        cout << "please enter the path of video" << endl;
        cout << "and the level  " << endl;
        cout << "for example: ./with_lib ../Video.avi 1" << endl;
        return 0;
    }
    int Level = atoi(argv[2]);
    VideoCapture capture(argv[1]);
    if (!capture.isOpened())
        cout << "fail to open " << argv[1] << endl;
    //count total frames
    long totalFrameNumber = capture.get(CAP_PROP_FRAME_COUNT);
    cout << "total " << totalFrameNumber << " frames in this video" << endl;

    int frameToStart, frameToStop, frameSize;
    int numOfTarget;
    vector<int> Frame;
    vector<int> IDnumber;
    vector<int> Xmin, TXmin[4];
    vector<int> Ymin, TYmin[4];
    vector<int> Width, TWidth[4];
    vector<int> Hight, THight[4];
    if (Level == 1)
    {
        //set start frame
        frameToStart = 68;

        //set finish frame
        frameToStop = 146;
        frameSize = frameToStop - frameToStart;
        numOfTarget = 1;
        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
        readGroundtruth("Level1.txt", &Frame, &IDnumber, &Xmin, &Ymin, &Width, &Hight);
    }
    else if (Level == 2)
    {
        //set start frame
        frameToStart = 68;
        //set finish frame
        frameToStop = 214;
        frameSize = frameToStop - frameToStart;
        numOfTarget = 1;
        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
        readGroundtruth("Level2.txt", &Frame, &IDnumber, &Xmin, &Ymin, &Width, &Hight);
    }
    else if (Level == 3)
    {
        //set start frame
        frameToStart = 367;
        //set finish frame
        frameToStop = 464;
        frameSize = frameToStop - frameToStart;
        numOfTarget = 2;

        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
        readGroundtruth("Level3.txt", &Frame, &IDnumber, &Xmin, &Ymin, &Width, &Hight);
    }
    else if (Level == 4)
    {
        //set start frame
        frameToStart = 1;
        //set finish frame
        frameToStop = 375;
        frameSize = frameToStop - frameToStart;
        numOfTarget = 2;

        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
        readGroundtruth("Level4.txt", &Frame, &IDnumber, &Xmin, &Ymin, &Width, &Hight);
    }
    else if (Level == 5)
    {
        //set start frame
        frameToStart = 224;
        //set finish frame
        frameToStop = 253;
        frameSize = frameToStop - frameToStart;
        numOfTarget = 4;

        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
        readGroundtruth("Level5.txt", &Frame, &IDnumber, &Xmin, &Ymin, &Width, &Hight);
    }
    else if (Level == 6)
    {
        //set start frame
        frameToStart = 224;
        //set finish frame
        frameToStop = 430;
        frameSize = frameToStop - frameToStart;
        numOfTarget = 4;

        cout << "Start from frame " << frameToStart << " to frame " << frameToStop << endl;
        readGroundtruth("Level6.txt", &Frame, &IDnumber, &Xmin, &Ymin, &Width, &Hight);
    }

    // get FPS
    double rate = capture.get(CAP_PROP_FPS);
    cout << "FPS: " << rate << endl;
    //parameters for the while loop
    bool stop = false;
    Mat frame, originFrame;
    long currentFrame = 1;
    //capture.set(CAP_PROP_POS_FRAMES, currentFrame);
    vector<string> str;
    ofstream ofs;

    Ptr<TrackerCSRT> csrtTracker1 = TrackerCSRT::create();
    Ptr<TrackerCSRT> csrtTracker2 = TrackerCSRT::create();
    Ptr<TrackerCSRT> csrtTracker3 = TrackerCSRT::create();
    Ptr<TrackerCSRT> csrtTracker4 = TrackerCSRT::create();
    Ptr<MultiTracker> multiTracker = MultiTracker::create();
    Rect2d Rect1, Rect2, Rect3, Rect4;

    int index = 0;
    //                             done pre setting                                //

    while (!stop)
    {
        //capture >> originFrame;
        if (!capture.read(originFrame))
        {
            cout << "fail to read frame" << endl;
            return -1;
        }
        resize(originFrame, frame, Size(originFrame.cols * 2, originFrame.rows * 2), INTER_CUBIC);
        //set tracker
        if (currentFrame >= frameToStart)
        {
            index++;
            if (currentFrame == frameToStart)
            {
                if (Level == 1)
                {
                    Rect1.x = Xmin[0];
                    Rect1.y = Ymin[0];
                    Rect1.width = Width[0];
                    Rect1.height = Hight[0];
                    csrtTracker1->init(frame, Rect1);
                }
                else if (Level == 2)
                {
                    Rect1.x = Xmin[0];
                    Rect1.y = Ymin[0];
                    Rect1.width = Width[0];
                    Rect1.height = Hight[0];
                    csrtTracker1->init(frame, Rect1);
                }
                else if (Level == 3)
                { //two target
                    Rect1.x = Xmin[0];
                    Rect1.y = Ymin[0];
                    Rect1.width = Width[0];
                    Rect1.height = Hight[0];
                    Rect2.x = Xmin[frameSize];
                    Rect2.y = Ymin[frameSize];
                    Rect2.width = Width[frameSize];
                    Rect2.height = Hight[frameSize];
                    multiTracker->add(csrtTracker1, frame, Rect1);
                    multiTracker->add(csrtTracker2, frame, Rect2);
                }
                else if (Level == 4)
                { //two target
                    Rect1.x = Xmin[0];
                    Rect1.y = Ymin[0];
                    Rect1.width = Width[0];
                    Rect1.height = Hight[0];
                    Rect2.x = Xmin[frameSize];
                    Rect2.y = Ymin[frameSize];
                    Rect2.width = Width[frameSize];
                    Rect2.height = Hight[frameSize];
                    multiTracker->add(csrtTracker1, frame, Rect1);
                    multiTracker->add(csrtTracker2, frame, Rect2);
                }
                else if (Level == 5)
                { //four target
                    Rect1.x = Xmin[0];
                    Rect1.y = Ymin[0];
                    Rect1.width = Width[0];
                    Rect1.height = Hight[0];
                    Rect2.x = Xmin[frameSize];
                    Rect2.y = Ymin[frameSize];
                    Rect2.width = Width[frameSize];
                    Rect2.height = Hight[frameSize];
                    Rect3.x = Xmin[frameSize * 2];
                    Rect3.y = Ymin[frameSize * 2];
                    Rect3.width = Width[frameSize * 2];
                    Rect3.height = Hight[frameSize * 2];
                    Rect4.x = Xmin[frameSize * 3];
                    Rect4.y = Ymin[frameSize * 3];
                    Rect4.width = Width[frameSize * 3];
                    Rect4.height = Hight[frameSize * 3];
                    multiTracker->add(csrtTracker1, frame, Rect1);
                    multiTracker->add(csrtTracker2, frame, Rect2);
                    multiTracker->add(csrtTracker1, frame, Rect3);
                    multiTracker->add(csrtTracker2, frame, Rect4);
                }
                else if (Level == 6)
                { //four target
                    Rect1.x = Xmin[0];
                    Rect1.y = Ymin[0];
                    Rect1.width = Width[0];
                    Rect1.height = Hight[0];
                    Rect2.x = Xmin[frameSize];
                    Rect2.y = Ymin[frameSize];
                    Rect2.width = Width[frameSize];
                    Rect2.height = Hight[frameSize];
                    Rect3.x = Xmin[frameSize * 2];
                    Rect3.y = Ymin[frameSize * 2];
                    Rect3.width = Width[frameSize * 2];
                    Rect3.height = Hight[frameSize * 2];
                    Rect4.x = Xmin[frameSize * 3];
                    Rect4.y = Ymin[frameSize * 3];
                    Rect4.width = Width[frameSize * 3];
                    Rect4.height = Hight[frameSize * 3];
                    multiTracker->add(csrtTracker1, frame, Rect1);
                    multiTracker->add(csrtTracker2, frame, Rect2);
                    multiTracker->add(csrtTracker1, frame, Rect3);
                    multiTracker->add(csrtTracker2, frame, Rect4);
                }
            }

            //tracker update

            if (Level == 1)
            {
                csrtTracker1->update(frame, Rect1);
                rectangle(frame, Rect1, Scalar(0, 0, 255), 12, 1);
                TXmin[0].push_back(Rect1.x);
                TYmin[0].push_back(Rect1.y);
                TWidth[0].push_back(Rect1.width);
                THight[0].push_back(Rect1.height);
            }
            else if (Level == 2)
            {
                csrtTracker1->update(frame, Rect1);
                rectangle(frame, Rect1, Scalar(0, 0, 255), 12, 1);
                TXmin[0].push_back(Rect1.x);
                TYmin[0].push_back(Rect1.y);
                TWidth[0].push_back(Rect1.width);
                THight[0].push_back(Rect1.height);
            }
            else if (Level == 3)
            {
                multiTracker->update(frame);
                for (int i = 0; i < multiTracker->getObjects().size(); i++)
                {
                    rectangle(frame, multiTracker->getObjects()[i], Scalar(0, 0, 255), 12, 1);
                    TXmin[i].push_back(multiTracker->getObjects()[i].x);
                    TYmin[i].push_back(multiTracker->getObjects()[i].y);
                    TWidth[i].push_back(multiTracker->getObjects()[i].width);
                    THight[i].push_back(multiTracker->getObjects()[i].height);
                }
            }
            /*
            else if (Level == 4)
            {
                csrtTracker->update(frame, Rect1);
                rectangle(frame, Rect1, Scalar(0, 0, 255), 12, 1);
                TXmin.push_back(Rect1.x);
                TYmin.push_back(Rect1.y);
                TWidth.push_back(Rect1.width);
                THight.push_back(Rect1.height);
            }
            else if (Level == 5)
            {
                csrtTracker->update(frame, Rect1);
                rectangle(frame, Rect1, Scalar(0, 0, 255), 12, 1);
                TXmin.push_back(Rect1.x);
                TYmin.push_back(Rect1.y);
                TWidth.push_back(Rect1.width);
                THight.push_back(Rect1.height);
            }
            else if (Level == 6)
            {
                csrtTracker->update(frame, Rect1);
                rectangle(frame, Rect1, Scalar(0, 0, 255), 12, 1);
                TXmin.push_back(Rect1.x);
                TYmin.push_back(Rect1.y);
                TWidth.push_back(Rect1.width);
                THight.push_back(Rect1.height);
            }
            */
            //output
            stringstream str;
            str << currentFrame << ".jpg";
            //imwrite(str.str(), frame);
        }

        currentFrame++;
        if (currentFrame > frameToStop)
        {
            stop = true;
        }
    }
    //output answer
    string Filename = "Tlevel" + to_string(Level) + ".txt";
    writeAnswer(Filename, frameSize, numOfTarget, Frame, IDnumber, TXmin, TYmin, TWidth, THight);

    //close video
    capture.release();

    return 0;
}

int readGroundtruth(string Filename, vector<int> *Frame, vector<int> *IDnumber, vector<int> *Xmin, vector<int> *Ymin, vector<int> *Width, vector<int> *Hight)
{
    ifstream fs;
    //read txt file
    fs.open(Filename, ios::in);
    if (!fs.is_open())
    {
        cout << "Failed to open file " << Filename << endl;
        return -1;
    }
    else
    {
        cout << "success open file " << Filename << endl;
        int frame;
        int iDnumber;
        int xmin;
        int ymin;
        int width;
        int hight;
        char comma;
        int w;
        int t;
        float f;
        while (fs >> frame >> comma >> iDnumber >> comma >> xmin >> comma >> ymin >> comma >> width >> comma >> hight >> comma >> w >> comma >> t >> comma >> f)
        {

            Frame->push_back(frame);
            IDnumber->push_back(iDnumber);
            Xmin->push_back(xmin);
            Ymin->push_back(ymin);
            Width->push_back(width);
            Hight->push_back(hight);
        }
    }
    fs.close();
    return 0;
}

int writeAnswer(string Filename, int FrameSize, int numOfTarget, vector<int> Frame, vector<int> IDnumber, vector<int> TXmin[4], vector<int> TYmin[4], vector<int> TWidth[4], vector<int> THight[4])
{
    ofstream ofs;
    ofs.open(Filename);
    if (!ofs.is_open())
    {
        cout << "Failed to open file " << Filename << endl;
        return -1;
    }
    else
    {
        for (int i = 0; i < numOfTarget; i++)
        {
            for (int j = 0; j <= FrameSize; j++)
            {
                ofs << Frame[j] << ',' << IDnumber[FrameSize * i + j] << ',' << TXmin[i][j] << ',' << TYmin[i][j] << ',' << TWidth[i][j] << ',' << THight[i][j] << "\n";
            }
        }
        ofs.close();
    }
    return 0;
}