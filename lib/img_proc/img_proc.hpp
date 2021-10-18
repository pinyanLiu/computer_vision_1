#ifndef IMG_PROC_HPP
#define IMG_PROC_HPP
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#define width 512
#define height 512
#define BLUE 0
#define GREEN 1
#define RED 2

class IMG_PROC
{
private:
    /* data */
    int length;
    unsigned char *buffer;
    unsigned char fin[width][height];
    unsigned char fout[width][height];

public:
    IMG_PROC(char *path);
    ~IMG_PROC();

    typedef struct
    {
        unsigned char b;
        unsigned char g;
        unsigned char r;
    } PIXEL;
    PIXEL **pixel;
    FILE *fpin;
    FILE *fpout;
    FILE *red;
    FILE *green;
    FILE *blue;
    FILE *rotate;
    unsigned char header[54];
    void read_img(FILE *input, FILE *output);
    void channel_separation(FILE *input, int mode);
    void clock_wise_rotation(FILE *input);
};
#endif