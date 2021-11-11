#ifndef IMG_PROC_HPP
#define IMG_PROC_HPP
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <random>
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
        int label = 0;
    } PIXEL;
    PIXEL **pixel;
    FILE *fpin;
    FILE *fpout;
    FILE *binary;
    FILE *cc;
    // FILE *red;
    // FILE *green;
    // FILE *blue;
    // FILE *rotate;
    unsigned char header[54];
    // void read_img(FILE *input, FILE *output);
    // void channel_separation(FILE *input, int mode);
    // void clock_wise_rotation(FILE *input);
    void binarize(FILE *input, FILE *output);
    typedef struct
    {
        int x_left;
        int x_right;
        int y_top;
        int y_bot;
        int box_width;
        int box_height;
        int area;
        float centroid;
    } bounding_box;
    std::vector<bounding_box> b_box;
    int area(int b_width, int b_height);
    int centroid(int x_left, int y_top, int b_width, int b_height);
    int box_width(int x_left, int x_right);
    int box_height(int y_top, int y_bot);
    void rectangle(int x, int y, int b_width, int b_height);
    int connectedcomponent(FILE *input, FILE *output);
    void color(FILE *output);
};
#endif