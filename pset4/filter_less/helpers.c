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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0;  j < width; j += 1)
        {
            double sepiaRed = (0.393 * image[i][j].rgbtRed
                               + 0.769 * image[i][j].rgbtGreen
                               + 0.189 * image[i][j].rgbtBlue);
            double sepiaGreen = (0.349 * image[i][j].rgbtRed
                               + 0.686 * image[i][j].rgbtGreen
                               + 0.168 * image[i][j].rgbtBlue);
            double sepiaBlue = (0.272 * image[i][j].rgbtRed
                               + 0.534 * image[i][j].rgbtGreen
                               + 0.131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255.0;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255.0;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255.0;
            }
            image[i][j].rgbtRed = (int) round(sepiaRed);
            image[i][j].rgbtGreen = (int) round(sepiaGreen);
            image[i][j].rgbtBlue = (int) round(sepiaBlue);
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
