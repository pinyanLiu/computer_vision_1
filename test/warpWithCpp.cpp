#include "img_warp.hpp"
#include <time.h>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    IMG_WARP process(argv[1]);
    process.World = process.imageToWorld();
    imshow("World", process.World);
    waitKey(0);
    return 0;
}