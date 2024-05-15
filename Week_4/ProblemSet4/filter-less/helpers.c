#include "helpers.h"
#include <stdio.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double average = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0;
            int rounded = (int)(average + 0.5);
            image[i][j].rgbtBlue = rounded;
            image[i][j].rgbtRed = rounded;
            image[i][j].rgbtGreen = rounded;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            double sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            double sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = (int)(sepiaRed+0.5);
            image[i][j].rgbtGreen = (int)(sepiaGreen+0.5);
            image[i][j].rgbtBlue = (int)(sepiaBlue+0.5);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixel values using a temporary variable
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    memcpy(copy, image, sizeof(RGBTRIPLE) * height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int newRed = 0;
            int newGreen = 0;
            int newBlue = 0;
            int count = 0;

            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int newRow = i + row;
                    int newCol = j + col;

                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        newRed += copy[newRow][newCol].rgbtRed;
                        newGreen += copy[newRow][newCol].rgbtGreen;
                        newBlue += copy[newRow][newCol].rgbtBlue;
                        count++;
                    }
                }
            }
            double red = newRed /(double) count;
            double green = newGreen /(double) count;
            double blue = newBlue /(double)count;
            image[i][j].rgbtRed = (int)(red+0.5);
            image[i][j].rgbtGreen = (int)(green+0.5);
            image[i][j].rgbtBlue = (int)(blue+0.5);
        }
    }

    return;
}