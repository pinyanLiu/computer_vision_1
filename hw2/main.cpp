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
    clock_t start, end;
    double cpu_time_used;
    if (argc < 2)
    {
        cout << "please enter the path of picture " << endl;
        return 0;

    }
    Mat src_Img, gray_scale, binarize, morphology, kernel, connectedComponent;
    Mat labels, stats, centroids;
    src_Img = imread(argv[1]);
    cvtColor(src_Img, gray_scale, COLOR_BGR2GRAY);

    start = clock();
    threshold(gray_scale, binarize, 200, 255, THRESH_BINARY_INV);
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Binarizing time:" << cpu_time_used << endl;

    start = clock();
    kernel = getStructuringElement(MORPH_RECT, Size(4, 4));
    dilate(binarize, morphology, kernel);
    dilate(morphology, morphology, kernel);
    erode(morphology, morphology, kernel);
    erode(morphology, morphology, kernel);
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Morphology time:" << cpu_time_used << endl;

    start = clock();
    end = clock();
    int components = connectedComponentsWithStats(morphology, labels, stats, centroids);
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Connected component time:" << cpu_time_used << endl;

    start = clock();
    morphology.copyTo(connectedComponent);
    for (int i = 1; i < components; i++)
    {
        Vec2d pt = centroids.at<Vec2d>(i, 0);
        int x = stats.at<int>(i, CC_STAT_LEFT);
        int y = stats.at<int>(i, CC_STAT_TOP);
        int width = stats.at<int>(i, CC_STAT_WIDTH);
        int height = stats.at<int>(i, CC_STAT_HEIGHT);
        int area = stats.at<int>(i, CC_STAT_AREA);
        putText(src_Img, "Centroid: " + to_string(int(pt[0])) + "Area: " + to_string(int(area)), Point(x, y + 30), 0, 0.4, Scalar(0, 0, 0), 2);
        rectangle(src_Img, Rect(x, y, width, height), Scalar(0, 0, 255), 1);
        if (width > height)
        {
            printf("box %d orientation: x ,length: %d\n", i, width);

        }
        else
        {
            printf("box %d orientation: y ,length: %d\n", i, height);

        }

    }
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Property analysis time:" << cpu_time_used << endl;

    waitKey(0);

    start = clock();
    imshow("binary_Img", binarize);
    imshow("morph", morphology);
    imshow("bounding box", src_Img);
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "drawing time:" << cpu_time_used << endl;
    waitKey(0);
    return 0;

}

