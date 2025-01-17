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
            // Calculate average color value for each pixel
            average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Assign the average to all color channels (RGB)
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
    // Iterate through rows and swap pixels to reflect image horizontally
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Temporary variable for swapping
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
    // Copy original image for reference
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate through pixels and apply averaging for blur effect
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;

            // Iterates through 3x3 grid around current pixel
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int ni = i + k; // Row index
                    int nj = j + l; // Column index

                    // Check bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Accumulate color values for averaging
                        sumRed += copy[ni][nj].rgbtRed;
                        sumGreen += copy[ni][nj].rgbtGreen;
                        sumBlue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Compute the average color values for the pixel
            image[i][j].rgbtRed = round((float) sumRed / count);
            image[i][j].rgbtGreen = round((float) sumGreen / count);
            image[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }
    return;
}

// Detect edges using Sobel operator
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Sobel kernels for edge detection (Gx and Gy)
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Copy original image to maintain original pixel values
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

            // Apply Sobel kernels to the 3x3 grid around the pixel
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int ni = i + k;    // Row index
                    int nj = j + l;    // Column index

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

            // Calculate final edge value by combining Gx and Gy results
            int finalRed = round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY));
            int finalGreen = round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY));
            int finalBlue = round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY));

            // Cap values at 255
            image[i][j].rgbtRed = (int) fmin(finalRed, 255);
            image[i][j].rgbtGreen = (int) fmin(finalGreen, 255);
            image[i][j].rgbtBlue = (int) fmin(finalBlue, 255);
        }
    }

    return;
}
