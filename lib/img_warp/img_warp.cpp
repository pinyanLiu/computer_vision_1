#include "img_warp.hpp"

IMG_WARP::IMG_WARP(std::string path)
{
    source = cv::imread(path);
    int alpha = 15 * PI / 180.0;
    int dx = 4;
    int dy = -10;
    int dz = 5;
    int gama = 0;
    int theda = 0.025;
    int Horizon = 307;
}

IMG_WARP::~IMG_WARP()
{
}

cv::Mat IMG_WARP::imageToWorld()
{
    cv::Mat output;
    for (int u = Horizon; u < source.rows; u++)
    {
        for (int v = 0; v < source.cols; v++)
        {
            int i = X(u, v, source.rows - Horizon, source.cols - 0);
            int j = Y(u, v, source.rows - Horizon, source.cols - 0);
            std::cout << "i" << i << "j" << j << std::endl;
            // output.at<cv::Vec3b>(i, j) = source.at<cv::Vec3b>(u, v);
        }
    }
    return output;
}
// cv::Mat IMG_WARP::worldToImage(cv::Mat source)
// {
//     cv::Mat output;
//     for (int x = Horizon; x < source.rows; x++)
//     {
//         for (int y = 0; y < source.cols; y++)
//         {
//             int i = X(u, v);
//             int j = Y(u, v);
//             output.at(i, j) = source.at(u, v);
//         }
//     }
//     return output;
// }

int IMG_WARP::X(int u, int v, int m, int n)
{
    return dz * (cot(theda - alpha + u * (2 * alpha / (m - 1))) * sin(gama - alpha + v * (2 * alpha / (n - 1)))) + dx;
}
int IMG_WARP::Y(int u, int v, int m, int n)
{
    return dz * (cot(theda - alpha + u * (2 * alpha / (m - 1))) * cos(gama - alpha + v * (2 * alpha / (n - 1)))) + dy;
}
int IMG_WARP::U(int x, int y, int m, int n) {}
int IMG_WARP::V(int x, int y, int m, int n) {}
double IMG_WARP::cot(double num)
{
    //Sinput.at<cv::Vec3b>(i,j)
    return (1 / tan(num));
}
