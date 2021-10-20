#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#define _CRT_SECURE_NO_DEPRECATE
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "please enter the path of picture " << endl;
        return 0;
    }
    Mat src_Img = imread(argv[1]);
    Mat rotate_Img;
    Mat red_Img = src_Img.clone();
    Mat green_Img = src_Img.clone();
    Mat blue_Img = src_Img.clone();
    Mat double_Img = src_Img.clone();
    Mat half_Img = src_Img.clone();
    //image rotation
    rotate(src_Img, rotate_Img, ROTATE_90_CLOCKWISE);
    //channel separation
    for (size_t i = 0; i < src_Img.rows; i++)
    {
        for (size_t j = 0; j < src_Img.cols; j++)
        {
            red_Img.at<Vec3b>(i, j)[0] = 0;
            red_Img.at<Vec3b>(i, j)[1] = 0;
            green_Img.at<Vec3b>(i, j)[0] = 0;
            green_Img.at<Vec3b>(i, j)[2] = 0;
            blue_Img.at<Vec3b>(i, j)[1] = 0;
            blue_Img.at<Vec3b>(i, j)[2] = 0;
        }
    }
    //resize
    resize(double_Img, double_Img, Size(src_Img.cols * 2, src_Img.rows * 2));
    resize(half_Img, half_Img, Size(src_Img.cols * 0.5, src_Img.rows * 0.5));
    //show result

    imshow("src_Img", src_Img);
    imshow("rotate_Img", rotate_Img);
    imshow("red_Img", red_Img);
    imshow("green_Img", green_Img);
    imshow("blue_Img", blue_Img);
    imshow("double_Img", double_Img);
    imshow("half_Img", half_Img);
    waitKey(0);

    imwrite("src_Img.bmp", src_Img);
    imwrite("rotate_Img.bmp", rotate_Img);
    imwrite("red_Img.bmp", red_Img);
    imwrite("green_Img.bmp", green_Img);
    imwrite("blue_Img.bmp", blue_Img);
    imwrite("double_Img.bmp", double_Img);
    imwrite("half_Img.bmp", half_Img);

    return 0;
}