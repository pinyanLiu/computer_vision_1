#include "img_warp.hpp"

IMG_WARP::IMG_WARP(std::string path)
{
    source = cv::imread(path);
    alpha = 15 * PI / 180.0;
    dx = 4;
    dy = -10;
    dz = 5;
    gama = 0;
    theta = 0.025;
    Horizon = (source.rows - 1) / (2 * alpha) * (-theta + alpha);
}

IMG_WARP::~IMG_WARP()
{
}

cv::Mat IMG_WARP::imageToWorld()
{
    cv::Mat output = cv::Mat::zeros(source.rows, source.cols, CV_8UC3);

    for (int u = 0; u < source.rows; u++)
    {
        for (int v = 0; v < source.cols; v++)
        {
            int i = int(X(u, v, source.rows - Horizon, source.cols - 0));
            int j = int(Y(u, v, source.rows - Horizon, source.cols - 0));
            i = i + source.rows / 2;
            //std::cout << "i :" << i << "j :" << j << std::endl;
            if (i >= 0 && i < source.rows && j >= 0 && j < source.cols)
            {
                output.at<cv::Vec3b>(i, j) = source.at<cv::Vec3b>(u, v);
            }
        }
    }
    return output;
}
cv::Mat IMG_WARP::worldToImage()
{
    int i, j, x_, out = 0;
    cv::Mat output = cv::Mat::zeros(source.rows, source.cols, CV_8UC3);
    for (int x = 0; x < source.rows; x++)
    {
        for (int y = 0; y < source.cols; y++)
        {
            x_ = int(x - source.rows / 2);
            i = int(U(x_, y, source.rows));
            j = int(V(x_, y, source.cols));
            if ((i >= 0 && i < source.rows) && (j >= 0 && j < source.cols))
            {
                output.at<cv::Vec3b>(x, y) = source.at<cv::Vec3b>(i, j);
            }
        }
    }

    return output;
}

int IMG_WARP::X(int u, int v, int m, int n)
{
    return (dz * (cot(theta - alpha + u * (2 * alpha / (m - 1))) * sin(gama - alpha + v * (2 * alpha / (n - 1)))) + dx);
}
int IMG_WARP::Y(int u, int v, int m, int n)
{
    return (dz * (cot(theta - alpha + u * (2 * alpha / (m - 1))) * cos(gama - alpha + v * (2 * alpha / (n - 1)))) + dy);
}
int IMG_WARP::U(int x, int y, int m)
{
    return (((m - 1) / (2 * alpha)) * (atan(dz * sin(atan((x - dx) / (y - dy))) / (x - dx)) - theta + alpha));
}
int IMG_WARP::V(int x, int y, int n)
{
    return (((n - 1) / (2 * alpha)) * (atan((x - dx) / (y - dy)) - gama + alpha));
}
double IMG_WARP::cot(double num)
{
    return (1 / tan(num));
}
