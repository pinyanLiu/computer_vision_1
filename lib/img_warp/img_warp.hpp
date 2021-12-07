#ifndef IMG_WARP_HPP
#define IMG_WARP_HPP
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <cmath>

class img_warp
{
public:
    img_warp(std::string path);
    ~img_warp();
    int imageToWorld(cv::Mat input); //return m n
    int worldToImage(cv::Mat input);

private:
    cv::Mat source;
};

#endif