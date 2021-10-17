#include "img_proc.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "please enter the path of picture " << endl;
        return 0;
    }
    IMG_PROC img(argv[1]);
    //img.read_img(img.fpin, img.fpout);
    //printf("heehee");
    //img.channel_separation(img.fpin, RED);
    //img.channel_separation(img.fpin, GREEN);
    img.channel_separation(img.fpin, BLUE);
    return 0;
}