#include "helpers.h"
#include "math.h"
#include "stdio.h"


void edge(int height, int width, RGBTRIPLE image[height][width]);
void corner(int height, int width, RGBTRIPLE image[height][width]);
void normal(int height, int width, RGBTRIPLE image[height][width]);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Create loop through all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average
            int k = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            // Change RGB ratio
            image[i][j].rgbtRed = k;
            image[i][j].rgbtBlue = k;
            image[i][j].rgbtGreen = k;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Nest Loop through pixels.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculating sepia colours with given algorithm.
            int sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));
            // Capping RGB values to 255.
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // Changing original values with sepia colours.
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid;
    if (width % 2 == 0)
    {
        mid = width / 2;
    }
    else
    {
        mid = floor(width / 2);
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            RGBTRIPLE temp[height][width];
            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Copy the image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // For loop for taking average
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float averageRed = 0;
            float averageGreen = 0;
            float averageBlue = 0;
            float counter = 0;

            //Corners
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1]
                [j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1]
                [j + 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1]
                [j + 1].rgbtBlue) / 4.0);
            }
            else if (i == 0 && j == width - 1)
            {
                image[i][width - 1].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1]
                [j - 1].rgbtRed) / 4.0);
                image[i][width - 1].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1]
                [j - 1].rgbtGreen) / 4.0);
                image[i][width - 1].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1]
                [j - 1].rgbtBlue) / 4.0);
            }
            else if (i == height -1 && j == 0)
            {
                image[height - 1][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1]
                [j + 1].rgbtRed) / 4.0);
                image[height - 1][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1]
                [j + 1].rgbtGreen) / 4.0);
                image[height - 1][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1]
                [j + 1].rgbtBlue) / 4.0);
            }
            else if (i == height - 1 && j == width - 1)
            {
                image[height - 1][width - 1].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1]
                [j - 1].rgbtRed) / 4.0);
                image[height - 1][width - 1].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1]
                [j - 1].rgbtGreen) / 4.0);
                image[height - 1][width - 1].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1]
                [j - 1].rgbtBlue) / 4.0);
            }
            //Edges
           else if (i == 0 && j > 0 && j < width - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy [i + 1][j - 1].rgbtRed + copy[i + 1]
                [j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy [i + 1][j - 1].rgbtGreen + copy[i + 1]
                [j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy [i + 1][j - 1].rgbtBlue + copy[i + 1]
                [j + 1].rgbtBlue) / 6.0);
            }
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy [i - 1][j - 1].rgbtRed + copy[i - 1]
                [j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy [i - 1][j - 1].rgbtGreen + copy[i - 1]
                [j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy [i - 1][j - 1].rgbtBlue + copy[i - 1]
                [j + 1].rgbtBlue) / 6.0);
            }
            else if (i > 0 && j == 0 && i < height - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy [i - 1][j].rgbtRed + copy[i - 1]
                [j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy [i - 1][j].rgbtGreen + copy[i - 1]
                [j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy [i - 1][j].rgbtBlue + copy[i - 1]
                [j + 1].rgbtBlue) / 6.0);
            }
            else if (i > 0 && j == width - 1 && i < height - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy [i - 1][j - 1].rgbtRed + copy[i - 1]
                [j].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy [i - 1][j - 1].rgbtGreen + copy[i - 1]
                [j].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy [i - 1][j - 1].rgbtBlue + copy[i - 1]
                [j].rgbtBlue) / 6.0);
            }
            //Middle
            else
            {
                for (int h = - 1; h < 2; h++)
                {
                    for (int w = - 1; w < 2; w++)
                    {
                        counter++;
                        averageRed += copy[h+i][w+j].rgbtRed;
                        averageGreen += copy[h+i][w+j].rgbtGreen;
                        averageBlue += copy[h+i][w+j].rgbtBlue;
                        image[i][j].rgbtRed = round((double)averageRed / counter);
                        image[i][j].rgbtGreen = round((double)averageGreen / counter);
                        image[i][j].rgbtBlue = round((double)averageBlue / counter);
                    }
                }
            }
        }
    }
    return;
}