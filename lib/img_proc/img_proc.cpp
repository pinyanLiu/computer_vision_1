#include "img_proc.hpp"

IMG_PROC::IMG_PROC(char *path)
{
    fpin = fopen(path, "rb");
    if (NULL == fpin)
    {
        printf("\7\n Cannot Open file: %s \n", path);
        exit(1);
    }
    fpout = fopen("output.bmp", "wb");
    if (NULL == fpout)
    {
        printf("\7\n Cannot Open file: %s \n", "output.bmp");
        exit(1);
    }
    green = fopen("green.bmp", "wb");
    if (NULL == green)
    {
        printf("\7\n Cannot Open file: %s \n", "green.bmp");
        exit(1);
    }
    red = fopen("red.bmp", "wb");
    if (NULL == red)
    {
        printf("\7\n Cannot Open file: %s \n", "red.bmp");
        exit(1);
    }
    blue = fopen("blue.bmp", "wb");
    if (NULL == blue)
    {
        printf("\7\n Cannot Open file: %s \n", "blue.bmp");
        exit(1);
    }
}

IMG_PROC::~IMG_PROC()
{
    fclose(fpin);
    fclose(fpout);
    fclose(red);
    fclose(green);
    fclose(blue);
}

void IMG_PROC::read_img(FILE *input, FILE *output)
{
    fseek(input, 0, SEEK_END);
    length = ftell(input);
    buffer = (unsigned char *)malloc(length * sizeof(unsigned char));
    fseek(input, 0, SEEK_SET);
    while (0 != fread(buffer, sizeof(unsigned char), length, input))
    {
        fwrite(buffer, sizeof(unsigned char), length, output);
    }

    free(buffer);
}

void IMG_PROC::channel_separation(FILE *input, int mode)
{

    pixel = (PIXEL **)malloc(sizeof(PIXEL *) * height);
    for (size_t i = 0; i < height; i++)
    {
        *(pixel + i) = (PIXEL *)malloc(sizeof(PIXEL) * width);
    }

    fread(header, sizeof(unsigned char), 54, input);
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            fread(&pixel[i][j].b, 1, 1, input);
            fread(&pixel[i][j].g, 1, 1, input);
            fread(&pixel[i][j].r, 1, 1, input);
        }
    }

    if (mode == BLUE)
    {
        fwrite(header, sizeof(unsigned char), 54, blue);

        for (size_t i = 0; i < width; i++)
        {
            for (size_t j = 0; j < height; j++)
            {
                pixel[i][j].g = 0;
                pixel[i][j].r = 0;
                fwrite(*(pixel + i) + j, sizeof(PIXEL), 1, blue);
            }
        }
    }

    else if (mode == GREEN)
    {
        fwrite(header, sizeof(unsigned char), 54, green);

        for (size_t i = 0; i < width; i++)
        {
            for (size_t j = 0; j < height; j++)
            {
                pixel[i][j].b = 0;
                pixel[i][j].r = 0;
                fwrite(*(pixel + i) + j, sizeof(PIXEL), 1, green);
            }
        }
    }
    else if (mode == RED)
    {
        fwrite(header, sizeof(unsigned char), 54, red);

        for (size_t i = 0; i < width; i++)
        {
            for (size_t j = 0; j < height; j++)
            {
                pixel[i][j].g = 0;
                pixel[i][j].b = 0;
                fwrite(*(pixel + i) + j, sizeof(PIXEL), 1, red);
            }
        }
    }
    fseek(fpin, 0, SEEK_SET);
    free(pixel);
}
