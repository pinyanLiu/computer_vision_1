#include "img_proc.hpp"
#include <time.h>
using namespace std;

int main(int argc, char *argv[])
{
    clock_t start, end;
    double cpu_time_used;
    if (argc < 2)
    {
        cout << "please enter the path of picture " << endl;
        return 0;
    }
    IMG_PROC img(argv[1]);
    start = clock();
    img.binarize(img.fpin, img.binary);
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Binarizing time:" << cpu_time_used << endl;

    start = clock();
    img.connectedcomponent(img.binary, img.cc);
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "CC time:" << cpu_time_used << endl;

    start = clock();
    img.color(img.cc);
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "drawing time:" << cpu_time_used << endl;

    return 0;
}