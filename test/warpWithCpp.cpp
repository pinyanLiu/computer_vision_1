#include "img_warp.hpp"
#include <time.h>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    IMG_WARP process(argv[1]);
    //    process.World = process.imageToWorld();
    process.Image = process.worldToImage();
    imwrite("Image.bmp", process.Image);

    return 0;
}
