#include "img_proc.hpp"

img_proc::img_proc(char *path)
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
    fseek(fpin, 0, SEEK_END);
    length = ftell(fpin);
    buffer = (unsigned char *)malloc(length * sizeof(unsigned char));
    fseek(fpin, 0, SEEK_SET);
}

img_proc::~img_proc()
{
    fclose(fpin);
    fclose(fpout);
    free(buffer);
}

void img_proc::read_img(FILE *input, FILE *output)
{
    while (0 != fread(buffer, sizeof(unsigned char), length, input))
    {
        fwrite(buffer, sizeof(unsigned char), length, output);
    }
}
