#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#define _CRT_SECURE_NO_DEPRECATE
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "please enter the path of 1.road_map 2.left 3. right " << endl;
        return 0;
    }
    Mat src_Img, gray, canny, cannyBGR, bird, warpMatrix, bird_crop, left, left_gray, right_gray, right, right_warp, stitch;
    src_Img = imread(argv[1]);
    gray = imread(argv[1], COLOR_BGR2GRAY);
    left = imread(argv[2]);
    left_gray = imread(argv[2], COLOR_BGR2GRAY);
    right = imread(argv[3]);
    right_gray = imread(argv[3], COLOR_BGR2GRAY);
    //exception
    if (src_Img.empty() || gray.empty())
    {
        printf(" Error opening image\n");
        return -1;
    }
    Canny(gray, canny, 50, 200, 3);
    cvtColor(canny, cannyBGR, COLOR_GRAY2BGR);
    cannyBGR = src_Img.clone();
    // Probabilistic Line Transform
    vector<Vec4i> linesP;                                    // will hold the results of the detection
    HoughLinesP(canny, linesP, 1, CV_PI / 180, 50, 280, 20); // runs the actual detection
    // Draw the lines
    for (size_t i = 3; i < 6; i++)
    {
        Vec4i l = linesP[i];
        line(cannyBGR, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(i == 3 ? 255 : 0, i == 5 ? 255 : 0, i == 4 ? 255 : 0), 13, LINE_AA);
    }

    imwrite("cannyBGR.bmp", cannyBGR);
    //inverse warping
    Point2f corners[4];
    Point2f corners_trans[4];
    Point2d p1(0, 360);
    Point2d p2(src_Img.cols - 1, 360);
    Point2d p3(0, src_Img.rows - 1);
    Point2d p4(src_Img.cols - 1, src_Img.rows - 1);
    corners[0] = p1;
    corners[1] = p2;
    corners[2] = p3;
    corners[3] = p4;
    bird = Mat::zeros(src_Img.rows, src_Img.cols, CV_8UC3);
    corners_trans[2] = Point2f(0, 384);                //P1
    corners_trans[0] = Point2f(src_Img.cols - 1, 110); //P2
    corners_trans[3] = Point2f(0, 400);                //P3
    corners_trans[1] = Point2f(src_Img.cols - 1, 682); //P4
    warpMatrix = getPerspectiveTransform(corners, corners_trans);
    warpPerspective(cannyBGR, bird, warpMatrix, src_Img.size());
    imwrite("bird.bmp", bird);
    //crop
    Rect rect(0, 350, 110, 85);
    bird_crop = bird(rect);
    imwrite("bird_crop.bmp", bird_crop);
    //bonus
    stitch = Mat::zeros(480, 900, CV_8UC3);
    corners_trans[0] = Point2f(130, 250); //P1
    corners_trans[1] = Point2f(470, 310); //P2
    corners_trans[2] = Point2f(475, 900); //P3
    corners_trans[3] = Point2f(0, 770);   //P4
    warpMatrix = getPerspectiveTransform(corners, corners_trans);
    warpPerspective(right, right_warp, warpMatrix, stitch.size());
    Stitcher::Mode mode = Stitcher::PANORAMA;
    vector<Mat> imgs;
    imgs.push_back(left);
    imgs.push_back(right);
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(imgs, stitch);
    imwrite("stitch.bmp", stitch);
    return 0;
}
