#ifndef IMG_PROC_HPP
#define IMG_PROC_HPP
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#define width 512
#define height 512
class img_proc
{
private:
    /* data */
    int length;
    unsigned char *buffer;
    unsigned char fin[width][height];
    unsigned char fout[width][height];

public:
    FILE *fpin;
    FILE *fpout;
    img_proc(char *path);
    ~img_proc();
    void read_img(FILE *input, FILE *output);
};
#endif