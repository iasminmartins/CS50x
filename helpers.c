#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
     // Iterate through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average
            average =
                 round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Assign average to color channels
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
    // Iterates through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Reflect image using a temporary variable
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    // Copy original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;

            // Iterates through 3x3 grid
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int ni = i + k; // Row
                    int nj = j + l; // Column

                    // Check bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Calculate sums
                        sumRed += copy[ni][nj].rgbtRed;
                        sumGreen += copy[ni][nj].rgbtGreen;
                        sumBlue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate new values
            image[i][j].rgbtRed = round((float) sumRed / count);
            image[i][j].rgbtGreen = round((float) sumGreen / count);
            image[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Kernels
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // Copy original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterates through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRedX = 0, sumRedY = 0, sumGreenX = 0, sumGreenY = 0, sumBlueX = 0, sumBlueY = 0;

            // Iterates through 3x3 grid
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int ni = i + k;
                    int nj = j + l;

                    // Check bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Get RGB values
                        int red = copy[ni][nj].rgbtRed;
                        int green = copy[ni][nj].rgbtGreen;
                        int blue = copy[ni][nj].rgbtBlue;

                        // Apply Sobel kernels
                        sumRedX += red * Gx[k + 1][l + 1];
                        sumRedY += red * Gy[k + 1][l + 1];
                        sumGreenX += green * Gx[k + 1][l + 1];
                        sumGreenY += green * Gy[k + 1][l + 1];
                        sumBlueX += blue * Gx[k + 1][l + 1];
                        sumBlueY += blue * Gy[k + 1][l + 1];
                    }
                }
            }

            // Calculate Sobel value
            int finalRed = round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY));
            int finalGreen = round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY));
            int finalBlue = round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY));

            // Cap values at 255
            image[i][j].rgbtRed = (int)fmin(finalRed, 255);
            image[i][j].rgbtGreen = (int)fmin(finalGreen, 255);
            image[i][j].rgbtBlue = (int)fmin(finalBlue, 255);
        }
    }
    
    return;
}
