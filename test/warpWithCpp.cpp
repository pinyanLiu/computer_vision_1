#include "img_warp.hpp"
#include <time.h>
using namespace std;
using namespace cv;

int main(int argc, char *argv[]){
    Mat source = cv::imread(argv[1]);
    cout<<"source rows = "<<source.rows<<endl;
    cout<<"source cols= "<<source.cols<<endl;
    return 0;
}