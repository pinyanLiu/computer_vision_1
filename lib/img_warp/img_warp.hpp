#ifndef __IMG_WARP_HPP__
#define __IMG_WARP_HPP__
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#define PI 3.14159265

class IMG_WARP
{
private:
    double cot(double num);
    int alpha;
    int dx;
    int dy;
    int dz;
    int gama;
    int theda;
    int Horizon;

public:
    cv::Mat source;
    cv::Mat World;
    cv::Mat Image;
    IMG_WARP(std::string path);
    ~IMG_WARP();
    cv::Mat imageToWorld(); // return size
    cv::Mat worldToImage();
    int X(int u, int v, int m, int n);
    int Y(int u, int v, int m, int n);
    int U(int x, int y, int m, int n);
    int V(int x, int y, int m, int n);
};

#endif