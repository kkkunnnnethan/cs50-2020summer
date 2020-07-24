#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0;  j < width; j += 1)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i += 1)
    {
        RGBTRIPLE reflect[width];
        for (int j = 0;  j < width; j += 1)
        {
            reflect[width - j - 1].rgbtRed = image[i][j].rgbtRed;
            reflect[width - j - 1].rgbtBlue = image[i][j].rgbtBlue;
            reflect[width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
        }
        for (int k = 0; k < width; k += 1)
        {
            image[i][k].rgbtRed = reflect[k].rgbtRed;
            image[i][k].rgbtGreen = reflect[k].rgbtGreen;
            image[i][k].rgbtBlue = reflect[k].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Blur[height][width];
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0;  j < width; j += 1)
        {
            int Red = 0;
            int Green = 0;
            int Blue = 0;
            int count = 0;

            for (int m = -1; m < 2; m += 1)
            {
                for (int n = -1; n < 2; n += 1)
                {
                    int x = i + m;
                    int y = j + n;
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        Red += image[x][y].rgbtRed;
                        Green += image[x][y].rgbtGreen;
                        Blue += image[x][y].rgbtBlue;
                        count += 1;
                    }
                }
            }
            Blur[i][j].rgbtRed = round((float) Red / count);
            Blur[i][j].rgbtGreen = round((float) Green / count);
            Blur[i][j].rgbtBlue = round((float) Blue / count);
        }
    }

    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0;  j < width; j += 1)
        {
            image[i][j].rgbtRed = Blur[i][j].rgbtRed;
            image[i][j].rgbtGreen = Blur[i][j].rgbtGreen;
            image[i][j].rgbtBlue = Blur[i][j].rgbtBlue;
        }
    }
    return;
}

// helper function
int cap(rgb)
{
    if (rgb > 255)
    {
        return 255;
    }
    else
    {
        return rgb;
    }
}

// helper function
RGBTRIPLE getRGB(int height, int width, int i, int j, RGBTRIPLE image[height][width])
{
    RGBTRIPLE result;
    int redx = 0;
    int greenx = 0;
    int bluex = 0;
    int redy = 0;
    int greeny = 0;
    int bluey = 0;

    int Gx[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1},
    };
    int Gy[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1},
    };

    for (int m = -1; m < 2; m += 1)
    {
        for (int n = -1; n < 2; n += 1)
        {
            int x = i + m;
            int y = j + n;
            if (x >= 0 && x < height && y >= 0 && y < width)
            {
                int gx = Gx[m + 1][n + 1];
                redx += gx * image[x][y].rgbtRed;
                greenx += gx * image[x][y].rgbtGreen;
                bluex += gx * image[x][y].rgbtBlue;

                int gy = Gy[m + 1][n + 1];
                redy += gy * image[x][y].rgbtRed;
                greeny += gy * image[x][y].rgbtGreen;
                bluey += gy * image[x][y].rgbtBlue;
            }
        }
    }

    result.rgbtRed = cap(round(sqrt(redx * redx + redy * redy)));
    result.rgbtGreen = cap(round(sqrt(greenx * greenx + greeny * greeny)));
    result.rgbtBlue = cap(round(sqrt(bluex * bluex + bluey * bluey)));
    return result;
}

// Detect edge among image
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];

    for (int q = 0; q < height; q += 1)
    {
        for (int r = 0; r < width; r += 1)
        {
            new_image[q][r] = getRGB(height, width, q, r, image);
        }
    }

    for (int q = 0; q < height; q += 1)
    {
        for (int r = 0; r < width; r += 1)
        {
            image[q][r] = new_image[q][r];
        }
    }
    return;
}
