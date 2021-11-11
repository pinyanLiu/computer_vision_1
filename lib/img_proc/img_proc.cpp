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
    binary = fopen("binary.bmp", "wb");
    if (NULL == binary)
    {
        printf("\7\n Cannot Open file: %s \n", "output.bmp");
        exit(1);
    }
    cc = fopen("cc.bmp", "wb");
    if (NULL == cc)
    {
        printf("\7\n Cannot Open file: %s \n", "cc.bmp");
        exit(1);
    }
    pixel = (PIXEL **)malloc(sizeof(PIXEL *) * height);
    for (size_t i = 0; i < height; i++)
    {
        *(pixel + i) = (PIXEL *)malloc(sizeof(PIXEL) * width);
    }
    fread(header, sizeof(unsigned char), 54, fpin); // read header
}

IMG_PROC::~IMG_PROC()
{
    fclose(fpin);
    fclose(fpout);
    fclose(binary);
    fclose(cc);

    free(pixel);
}
/*
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
    fseek(input, 0, SEEK_SET);

    free(buffer);
}

void IMG_PROC::channel_separation(FILE *input, int mode)
{
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
    fseek(input, 0, SEEK_SET);
}
void IMG_PROC::clock_wise_rotation(FILE *input)
{
    for (size_t j = width - 1; j != 0; j--)
    {
        for (size_t i = 0; i < height; i++)
        {
            fwrite(&pixel[i][j], sizeof(PIXEL), 1, rotate);
        }
    }
    fseek(input, 0, SEEK_SET);
}
*/
void IMG_PROC::binarize(FILE *input, FILE *output)
{
    // read input
    // fseek(input, 53, SEEK_SET);
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            fread(&pixel[i][j].b, 1, 1, input);
            fread(&pixel[i][j].g, 1, 1, input);
            fread(&pixel[i][j].r, 1, 1, input);
        }
    }
    // binarize
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            // turn white background to black
            if ((pixel[i][j].r + pixel[i][j].g + pixel[i][j].b) < (240 * 3))
            {
                pixel[i][j].r = 255;
                pixel[i][j].g = 255;
                pixel[i][j].b = 255;
            }
            // turn target place to white
            else
            {
                pixel[i][j].r = 0;
                pixel[i][j].g = 0;
                pixel[i][j].b = 0;
            }
        }
    }

    // output
    fwrite(header, sizeof(unsigned char), 54, output);
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            fwrite(*(pixel + i) + j, 3 * sizeof(unsigned char), 1, output);
        }
    }
}
int IMG_PROC::connectedcomponent(FILE *input, FILE *output)
{
    int label = 0;
    bool done = false;
    fseek(input, 54, SEEK_SET);
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            fread(&pixel[i][j].b, 1, 1, input);
            fread(&pixel[i][j].g, 1, 1, input);
            fread(&pixel[i][j].r, 1, 1, input);
        }
    }

    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            if (pixel[i][j].r == 255)
            {
                if (i == 0 && j == 0) // pixel on top left
                {
                    pixel[i][j].label = 1;
                    label = 1;
                    continue;
                }
                else if (i == 0) // pixel on left
                {

                    if (pixel[i][j - 1].r == 255 && pixel[i][j - 1].label != 0) // top neighbor has label
                    {
                        pixel[i][j].label = pixel[i][j - 1].label;
                        continue;
                    }
                    else // no neighbor has label
                    {
                        label += 1;
                        pixel[i][j].label = label;
                        continue;
                    }
                }
                else if (j == 0) // pixel on top
                {

                    if (pixel[i - 1][j].r == 255 && pixel[i - 1][j].label != 0) // left neighbor has label
                    {
                        pixel[i][j].label = pixel[i - 1][j].label;
                        continue;
                    }
                    else // no neighbor has label
                    {
                        label += 1;
                        pixel[i][j].label = label;
                        continue;
                    }
                }
                else // pixel in other place
                {

                    if ((pixel[i][j - 1].r == 255 && pixel[i - 1][j].r == 255) && (pixel[i][j - 1].label != 0 && pixel[i - 1][j].label != 0)) // left and top neighbor has label
                    {
                        if (pixel[i][j - 1].label < pixel[i - 1][j].label) // top label value smaller then left
                        {
                            pixel[i][j].label = pixel[i][j - 1].label;
                            continue;
                        }
                        else
                        {
                            pixel[i][j].label = pixel[i - 1][j].label;
                            continue;
                        }
                    }
                    else if (pixel[i - 1][j].r == 255 && pixel[i - 1][j].label != 0) // left neighbor has label
                    {
                        pixel[i][j].label = pixel[i - 1][j].label;
                        continue;
                    }
                    else if (pixel[i][j - 1].r == 255 && pixel[i][j - 1].label != 0) // top neighbor has label
                    {
                        pixel[i][j].label = pixel[i][j - 1].label;
                        continue;
                    }
                    else // no neighbor has label
                    {
                        label += 1;
                        pixel[i][j].label = label;
                        continue;
                    }
                }
            }
            else
            {
                pixel[i][j].label = 0;
            }
        }
    }
    printf("label = %d\n", label);
    int iterator = 0;
    while (done == false)
    {
        iterator++;
        done = true;
        // inverse direction
        for (size_t i = width - 1; i < -1; i--)
        {
            for (size_t j = height - 1; j < -1; j--)
            {
                if (pixel[i][j].label != 0)
                {
                    if (i == (width - 1) && j == (height - 1))
                    {
                        continue;
                    }
                    else if (i == (width - 1))
                    {
                        if (pixel[i][j + 1].label < pixel[i][j].label && pixel[i][j + 1].label != 0) // left neighbor has label
                        {
                            pixel[i][j].label = pixel[i][j + 1].label;
                            done = false;
                            continue;
                        }
                    }
                    else if (j == (height - 1))
                    {
                        if (pixel[i + 1][j].label < pixel[i][j].label && pixel[i + 1][j].label != 0) // left neighbor has label
                        {
                            pixel[i][j].label = pixel[i + 1][j].label;
                            done = false;
                            continue;
                        }
                    }
                    else
                    {
                        if ((pixel[i][j + 1].label < pixel[i][j].label || pixel[i + 1][j].label < pixel[i][j].label) && (pixel[i][j + 1].label != 0 && pixel[i + 1][j].label != 0)) // left and top neighbor has label
                        {
                            if (pixel[i][j + 1].label < pixel[i + 1][j].label) // top label value smaller then left
                            {
                                pixel[i][j].label = pixel[i][j + 1].label;
                                done = false;
                                continue;
                            }
                            else
                            {
                                pixel[i][j].label = pixel[i + 1][j].label;
                                done = false;
                                continue;
                            }
                        }
                        else if (pixel[i + 1][j].label < pixel[i][j].label && pixel[i + 1][j].label != 0) // left neighbor has label
                        {
                            pixel[i][j].label = pixel[i + 1][j].label;
                            done = false;
                            continue;
                        }
                        else if (pixel[i][j + 1].label < pixel[i][j].label && pixel[i][j + 1].label != 0) // top neighbor has label
                        {
                            pixel[i][j].label = pixel[i][j + 1].label;
                            done = false;
                            continue;
                        }
                    }
                }
            }
        }
        if (done == true)
        {
            break;
        }
        done = true;
        iterator++;
        for (size_t i = 0; i < width; i++)
        {
            for (size_t j = 0; j < height; j++)
            {
                if (pixel[i][j].label != 0)
                {
                    if (i == 0 && j == 0)
                    {
                        continue;
                    }
                    else if (i == 0)
                    {
                        if (pixel[i][j - 1].label < pixel[i][j].label && pixel[i][j - 1].label != 0) // left neighbor has label
                        {
                            pixel[i][j].label = pixel[i][j - 1].label;
                            done = false;
                            continue;
                        }
                    }
                    else if (j == 0)
                    {
                        if (pixel[i - 1][j].label < pixel[i][j].label && pixel[i - 1][j].label != 0) // left neighbor has label
                        {
                            pixel[i][j].label = pixel[i - 1][j].label;
                            done = false;
                            continue;
                        }
                    }
                    else
                    {
                        if ((pixel[i][j - 1].label < pixel[i][j].label || pixel[i - 1][j].label < pixel[i][j].label) && (pixel[i][j - 1].label != 0 && pixel[i - 1][j].label != 0)) // left and top neighbor has label
                        {
                            if (pixel[i][j - 1].label < pixel[i - 1][j].label) // top label value smaller then left
                            {
                                pixel[i][j].label = pixel[i][j - 1].label;
                                done = false;
                                continue;
                            }
                            else
                            {
                                pixel[i][j].label = pixel[i - 1][j].label;
                                done = false;
                                continue;
                            }
                        }
                        else if (pixel[i - 1][j].label < pixel[i][j].label && pixel[i - 1][j].label != 0) // left neighbor has label
                        {
                            pixel[i][j].label = pixel[i - 1][j].label;
                            done = false;
                            continue;
                        }
                        else if (pixel[i][j - 1].label < pixel[i][j].label && pixel[i][j - 1].label != 0) // top neighbor has label
                        {
                            pixel[i][j].label = pixel[i][j - 1].label;
                            done = false;
                            continue;
                        }
                    }
                }
            }
        }
    }
    printf("iterator = %d\n", iterator);
}
void IMG_PROC::color(FILE *output)
{
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {

            if (pixel[i][j].label != 0)
            {
                pixel[i][j].r = pixel[i][j].label * 12 % 256;
                pixel[i][j].g = pixel[i][j].label * 25 % 256;
                pixel[i][j].b = pixel[i][j].label * 37 % 256;
            }
        }
    }
    // output
    fwrite(header, sizeof(unsigned char), 54, output);
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            fwrite(*(pixel + i) + j, 3 * sizeof(unsigned char), 1, output);
        }
    }
}