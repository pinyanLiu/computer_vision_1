#include "img_warp.hpp"
img_warp::img_warp(std::string path)
{
    source = cv::imread(path);
}

int img_warp::imageToWorld(cv::Mat input)
{
    //Sinput.at<cv::Vec3b>(i,j)
}
