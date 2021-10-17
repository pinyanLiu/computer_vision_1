#include "img_proc.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "please enter the path of picture " << endl;
        return 0;
    }
    img_proc img(argv[1]);
    img.read_img(img.fpin, img.fpout);

    return 0;
}