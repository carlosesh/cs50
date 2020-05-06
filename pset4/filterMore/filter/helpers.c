#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = 0;

            //compute the average of the 3 pixels (R+G+B)/3
            average = round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtBlue) / 3);

            //Assign the value to each one
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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //get the current position for the pixels and the last element of the array at position width - j -i
            int tempRed = image[i][j].rgbtRed, tempGreen = image[i][j].rgbtGreen, tempBlue = image[i][j].rgbtBlue,
                lastNthPosition = width - j - 1;

            //Assign the value of the lastNthPosition of the array to the  element at the ith position
            //Then assign the lastNthPosition the value of the element at the ith position
            image[i][j].rgbtRed =  image[i][lastNthPosition].rgbtRed;
            image[i][lastNthPosition].rgbtRed = tempRed;

            image[i][j].rgbtGreen =  image[i][lastNthPosition].rgbtGreen;
            image[i][lastNthPosition].rgbtGreen = tempGreen;

            image[i][j].rgbtBlue =  image[i][lastNthPosition].rgbtBlue;
            image[i][lastNthPosition].rgbtBlue = tempBlue;
        }
    }

    return;
}

//check if the value is greater than 255 and if it is then make the value equal to 255, else leave it as is
int pixelCap(int pixelValue)
{
    if (pixelValue > 255)
    {
        pixelValue = 255;
    }
    return pixelValue;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int averageRed = 0, averageGreen = 0, averageBlue = 0;

    RGBTRIPLE imageCopy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            averageRed = 0;
            averageGreen = 0;
            averageBlue = 0;


            //if it's the top left corner, then sum the surrounding to the average
            //include itself
            if (i == 0 && j == 0)
            {
                averageRed = (imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + imageCopy[i + 1][j].rgbtRed +
                              imageCopy[i + 1][j + 1].rgbtRed);
                image[i][j].rgbtRed = pixelCap(round(averageRed / 4.0));

                averageGreen = (imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen +
                                imageCopy[i + 1][j + 1].rgbtGreen);
                image[i][j].rgbtGreen = pixelCap(round(averageGreen / 4.0));

                averageBlue = (imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue +
                               imageCopy[i + 1][j + 1].rgbtBlue);
                image[i][j].rgbtBlue = pixelCap(round(averageBlue / 4.0));
            }

            //if it's the top right corner, then sum the surrounding to the average
            //include itself
            else if (i == 0 && j == width - 1)
            {
                averageRed = (imageCopy[i][j].rgbtRed + imageCopy[i][j - 1].rgbtRed + imageCopy[i + 1][j].rgbtRed +
                              imageCopy[i + 1][j - 1].rgbtRed);
                image[i][j].rgbtRed = pixelCap(round(averageRed / 4.0));

                averageGreen = (imageCopy[i][j].rgbtGreen + imageCopy[i][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen +
                                imageCopy[i + 1][j - 1].rgbtGreen);
                image[i][j].rgbtGreen = pixelCap(round(averageGreen / 4.0));

                averageBlue = (imageCopy[i][j].rgbtBlue + imageCopy[i][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue +
                               imageCopy[i + 1][j - 1].rgbtBlue);
                image[i][j].rgbtBlue = pixelCap(round(averageBlue / 4.0));
            }

            //if it's the lower left corner, then sum the surrounding to the average
            //include itself
            else if (i == height - 1 && j == 0)
            {
                averageRed = (imageCopy[i][j].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i][j + 1].rgbtRed +
                              imageCopy[i - 1][j + 1].rgbtRed);
                image[i][j].rgbtRed = pixelCap(round(averageRed / 4.0));

                averageGreen = (imageCopy[i][j].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen +
                                imageCopy[i - 1][j + 1].rgbtGreen);
                image[i][j].rgbtGreen = pixelCap(round(averageGreen / 4.0));

                averageBlue = (imageCopy[i][j].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue +
                               imageCopy[i - 1][j + 1].rgbtBlue);
                image[i][j].rgbtBlue = pixelCap(round(averageBlue / 4.0));
            }

            //if it's the lower right corner, then sum the surrounding to the average
            //include itself
            else if (i == height - 1 && j == width - 1)
            {
                averageRed = (imageCopy[i][j].rgbtRed + imageCopy[i][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed +
                              imageCopy[i - 1][j - 1].rgbtRed);
                image[i][j].rgbtRed = pixelCap(round(averageRed / 4.0));

                averageGreen = (imageCopy[i][j].rgbtGreen + imageCopy[i][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen +
                                imageCopy[i - 1][j - 1].rgbtGreen);
                image[i][j].rgbtGreen = pixelCap(round(averageGreen / 4.0));

                averageBlue = (imageCopy[i][j].rgbtBlue + imageCopy[i][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue +
                               imageCopy[i - 1][j - 1].rgbtBlue);
                image[i][j].rgbtBlue = pixelCap(round(averageBlue / 4.0));
            }

            //check if you are on the left edge
            else if (j == 0)
            {
                averageRed = (imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed + imageCopy[i][j].rgbtRed +
                              imageCopy[i][j + 1].rgbtRed + imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed);
                image[i][j].rgbtRed = pixelCap(round(averageRed / 6.0));

                averageGreen = (imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen + imageCopy[i][j].rgbtGreen +
                                imageCopy[i][j + 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen);
                image[i][j].rgbtGreen = pixelCap(round(averageGreen / 6.0));

                averageBlue = (imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue + imageCopy[i][j].rgbtBlue +
                               imageCopy[i][j + 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue);
                image[i][j].rgbtBlue = pixelCap(round(averageBlue / 6.0));
            }

            //check if you are on the upper edge
            else if (i == 0)
            {
                averageRed = (imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed +
                              imageCopy[i + 1][j - 1].rgbtRed + imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed);
                image[i][j].rgbtRed = pixelCap(round(averageRed / 6.0));

                averageGreen = (imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen +
                                imageCopy[i + 1][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen);
                image[i][j].rgbtGreen = pixelCap(round(averageGreen / 6.0));

                averageBlue = (imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue +
                               imageCopy[i + 1][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue);
                image[i][j].rgbtBlue = pixelCap(round(averageBlue / 6.0));
            }

            //check if you are on the right edge
            else if (j == width - 1)
            {
                averageRed = (imageCopy[i - 1][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i][j - 1].rgbtRed +
                              imageCopy[i][j].rgbtRed + imageCopy[i + 1][j - 1].rgbtRed + imageCopy[i + 1][j].rgbtRed);
                image[i][j].rgbtRed = pixelCap(round(averageRed / 6.0));

                averageGreen = (imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + averageGreen + imageCopy[i][j - 1].rgbtGreen +
                                imageCopy[i][j].rgbtGreen + imageCopy[i + 1][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen);
                image[i][j].rgbtGreen = pixelCap(round(averageGreen / 6.0));

                averageBlue = (imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i][j - 1].rgbtBlue +
                               imageCopy[i][j].rgbtBlue + imageCopy[i + 1][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue);
                image[i][j].rgbtBlue = pixelCap(round(averageBlue / 6.0));
            }

            //check if you are on the lower edge
            else if (i == height - 1)
            {
                averageRed = (imageCopy[i - 1][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed +
                              imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed);
                image[i][j].rgbtRed = pixelCap(round(averageRed / 6.0));

                averageGreen = (imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen +
                                imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen);
                image[i][j].rgbtGreen = pixelCap(round(averageGreen / 6.0));

                averageBlue = (imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue +
                               imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue);
                image[i][j].rgbtBlue = pixelCap(round(averageBlue / 6.0));
            }

            else
            {
                averageRed = (imageCopy[i - 1][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed +
                              imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + imageCopy[i + 1][j - 1].rgbtRed +
                              imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed);
                image[i][j].rgbtRed = pixelCap(round(averageRed / 9.0));

                averageGreen = (imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen +
                                imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + imageCopy[i + 1][j - 1].rgbtGreen +
                                imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen);
                image[i][j].rgbtGreen = pixelCap(round(averageGreen / 9.0));

                averageBlue = (imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue +
                               imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + imageCopy[i + 1][j - 1].rgbtBlue +
                               imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue);
                image[i][j].rgbtBlue = pixelCap(round(averageBlue / 9.0));
            }
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gxRed = 0, gxGreen = 0, gxBlue = 0, gyRed = 0, gyGreen = 0, gyBlue = 0;

    int gxMatrix[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gyMatrix[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE imageCopy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gxRed = 0, gxGreen = 0, gxBlue = 0;
            gyRed = 0, gyGreen = 0, gyBlue = 0;

            //if it's the top left corner, then sum the surrounding to the average
            //include itself
            if (i == 0 && j == 0)
            {
                gxRed = (0 * gxMatrix[0][0]) + (0 * gxMatrix[0][1]) +
                        (0 * gxMatrix[0][2]) + (0 * gxMatrix[1][0]) +
                        (imageCopy[i][j].rgbtRed * gxMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtRed * gxMatrix[2][2]);

                gyRed = (0 * gyMatrix[0][0]) + (0 * gyMatrix[0][1]) +
                        (0 * gyMatrix[0][2]) + (0 * gyMatrix[1][0]) +
                        (imageCopy[i][j].rgbtRed * gyMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtRed * gyMatrix[2][2]);

                image[i][j].rgbtRed = pixelCap(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));

                gxGreen = (0 * gxMatrix[0][0]) + (0 * gxMatrix[0][1]) +
                          (0 * gxMatrix[0][2]) + (0 * gxMatrix[1][0]) +
                          (imageCopy[i][j].rgbtGreen * gxMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtGreen * gxMatrix[2][2]);

                gyGreen = (0 * gyMatrix[0][0]) + (0 * gyMatrix[0][1]) +
                          (0 * gyMatrix[0][2]) + (0 * gyMatrix[1][0]) +
                          (imageCopy[i][j].rgbtGreen * gyMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtGreen * gyMatrix[2][2]);

                image[i][j].rgbtGreen = pixelCap(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));

                gxBlue = (0 * gxMatrix[0][0]) + (0 * gxMatrix[0][1]) +
                         (0 * gxMatrix[0][2]) + (0 * gxMatrix[1][0]) +
                         (imageCopy[i][j].rgbtRed * gxMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtRed * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtRed * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtRed * gxMatrix[2][2]);

                gyBlue = (0 * gyMatrix[0][0]) + (0 * gyMatrix[0][1]) +
                         (0 * gyMatrix[0][2]) + (0 * gyMatrix[1][0]) +
                         (imageCopy[i][j].rgbtBlue * gyMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtBlue * gyMatrix[2][2]);

                image[i][j].rgbtBlue = pixelCap(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));

            }

            //if it's the top right corner, then sum the surrounding to the average
            //include itself
            else if (i == 0 && j == width - 1)
            {
                gxRed = (0 * gxMatrix[0][0]) + (0 * gxMatrix[0][1]) +
                        (0 * gxMatrix[0][2]) + (imageCopy[i][j - 1].rgbtRed * gxMatrix[1][0]) +
                        (imageCopy[i][j].rgbtRed * gxMatrix[1][1]) + (0 * gxMatrix[1][2]) +
                        (imageCopy[i + 1][j - 1].rgbtRed * gxMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyRed = (0 * gyMatrix[0][0]) + (0 * gyMatrix[0][1]) +
                        (0 * gyMatrix[0][2]) + (imageCopy[i][j - 1].rgbtRed * gyMatrix[1][0]) +
                        (imageCopy[i][j].rgbtRed * gyMatrix[1][1]) + (0 * gyMatrix[1][2]) +
                        (imageCopy[i + 1][j - 1].rgbtRed * gyMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtRed = pixelCap(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));

                gxGreen = (0 * gxMatrix[0][0]) + (0 * gxMatrix[0][1]) +
                          (0 * gxMatrix[0][2]) + (imageCopy[i][j - 1].rgbtGreen * gxMatrix[1][0]) +
                          (imageCopy[i][j].rgbtGreen * gxMatrix[1][1]) + (0 * gxMatrix[1][2]) +
                          (imageCopy[i + 1][j - 1].rgbtGreen * gxMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyGreen = (0 * gyMatrix[0][0]) + (0 * gyMatrix[0][1]) +
                          (0 * gyMatrix[0][2]) + (imageCopy[i][j - 1].rgbtGreen * gyMatrix[1][0]) +
                          (imageCopy[i][j].rgbtGreen * gyMatrix[1][1]) + (0 * gyMatrix[1][2]) +
                          (imageCopy[i + 1][j - 1].rgbtGreen * gyMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtGreen = pixelCap(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));

                gxBlue = (0 * gxMatrix[0][0]) + (0 * gxMatrix[0][1]) +
                         (0 * gxMatrix[0][2]) + (imageCopy[i][j - 1].rgbtBlue * gxMatrix[1][0]) +
                         (imageCopy[i][j].rgbtBlue * gxMatrix[1][1]) + (0 * gxMatrix[1][2]) +
                         (imageCopy[i + 1][j - 1].rgbtBlue * gxMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gxBlue = (0 * gyMatrix[0][0]) + (0 * gyMatrix[0][1]) +
                         (0 * gyMatrix[0][2]) + (imageCopy[i][j - 1].rgbtBlue * gyMatrix[1][0]) +
                         (imageCopy[i][j].rgbtBlue * gyMatrix[1][1]) + (0 * gyMatrix[1][2]) +
                         (imageCopy[i + 1][j - 1].rgbtBlue * gyMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtBlue = pixelCap(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));
            }

            //if it's the lower left corner, then sum the surrounding to the average
            //include itself
            else if (i == height - 1 && j == 0)
            {
                gxRed = (0 * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gxMatrix[0][1]) +
                        (imageCopy[i - 1][j + 1].rgbtRed * gxMatrix[0][2]) +
                        (0 * gxMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gxMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                        (0 * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyRed = (0 * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gyMatrix[0][1]) +
                        (imageCopy[i - 1][j + 1].rgbtRed * gyMatrix[0][2]) +
                        (0 * gyMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gyMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                        (0 * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtRed = pixelCap(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));

                gxGreen = (0 * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gxMatrix[0][1]) +
                          (imageCopy[i - 1][j + 1].rgbtGreen * gxMatrix[0][2]) +
                          (0 * gxMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gxMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                          (0 * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyGreen = (0 * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gyMatrix[0][1]) +
                          (imageCopy[i - 1][j + 1].rgbtGreen * gyMatrix[0][2]) +
                          (0 * gyMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gyMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                          (0 * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtGreen = pixelCap(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));

                gxBlue = (0 * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gxMatrix[0][1]) +
                         (imageCopy[i - 1][j + 1].rgbtBlue * gxMatrix[0][2]) +
                         (0 * gxMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gxMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                         (0 * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyBlue = (0 * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gyMatrix[0][1]) +
                         (imageCopy[i - 1][j + 1].rgbtBlue * gyMatrix[0][2]) +
                         (0 * gyMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gyMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                         (0 * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtBlue = pixelCap(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));
            }

            //if it's the lower right corner, then sum the surrounding to the average
            //include itself
            else if (i == height - 1 && j == width - 1)
            {
                gxRed = (imageCopy[i - 1][j - 1].rgbtRed * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gxMatrix[0][1]) +
                        (0 * gxMatrix[0][2]) + (imageCopy[i][j - 1].rgbtRed * gxMatrix[1][0]) +
                        (imageCopy[i][j].rgbtRed * gxMatrix[1][1]) + (0 * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                        (0 * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyRed = (imageCopy[i - 1][j - 1].rgbtRed * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gyMatrix[0][1]) +
                        (0 * gyMatrix[0][2]) + (imageCopy[i][j - 1].rgbtRed * gyMatrix[1][0]) +
                        (imageCopy[i][j].rgbtRed * gyMatrix[1][1]) + (0 * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                        (0 * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtRed = pixelCap(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));

                gxGreen = (imageCopy[i - 1][j - 1].rgbtGreen * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gxMatrix[0][1]) +
                          (0 * gxMatrix[0][2]) + (imageCopy[i][j - 1].rgbtGreen * gxMatrix[1][0]) +
                          (imageCopy[i][j].rgbtGreen * gxMatrix[1][1]) + (0 * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                          (0 * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyGreen = (imageCopy[i - 1][j - 1].rgbtGreen * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gyMatrix[0][1]) +
                          (0 * gyMatrix[0][2]) + (imageCopy[i][j - 1].rgbtGreen * gyMatrix[1][0]) +
                          (imageCopy[i][j].rgbtGreen * gyMatrix[1][1]) + (0 * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                          (0 * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtGreen = pixelCap(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));

                gxBlue = (imageCopy[i - 1][j - 1].rgbtBlue * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gxMatrix[0][1]) +
                         (0 * gxMatrix[0][2]) + (imageCopy[i][j - 1].rgbtBlue * gxMatrix[1][0]) +
                         (imageCopy[i][j].rgbtBlue * gxMatrix[1][1]) + (0 * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                         (0 * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyBlue = (imageCopy[i - 1][j - 1].rgbtBlue * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gyMatrix[0][1]) +
                         (0 * gyMatrix[0][2]) + (imageCopy[i][j - 1].rgbtBlue * gyMatrix[1][0]) +
                         (imageCopy[i][j].rgbtBlue * gyMatrix[1][1]) + (0 * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                         (0 * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtBlue = pixelCap(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));
            }

            //check if you are on the left edge
            else if (j == 0)
            {
                gxRed = (0 * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gxMatrix[0][1]) +
                        (imageCopy[i - 1][j + 1].rgbtRed * gxMatrix[0][2]) +
                        (0 * gxMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gxMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtRed * gxMatrix[2][2]);

                gyRed = (0 * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gyMatrix[0][1]) +
                        (imageCopy[i - 1][j + 1].rgbtRed * gyMatrix[0][2]) +
                        (0 * gyMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gyMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtRed * gyMatrix[2][2]);

                image[i][j].rgbtRed = pixelCap(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));

                gxGreen = (0 * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gxMatrix[0][1]) +
                          (imageCopy[i - 1][j + 1].rgbtGreen * gxMatrix[0][2]) +
                          (0 * gxMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gxMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtGreen * gxMatrix[2][2]);

                gyGreen = (0 * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gyMatrix[0][1]) +
                          (imageCopy[i - 1][j + 1].rgbtGreen * gyMatrix[0][2]) +
                          (0 * gyMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gyMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtGreen * gyMatrix[2][2]);

                image[i][j].rgbtGreen = pixelCap(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));

                gxBlue = (0 * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gxMatrix[0][1]) +
                         (imageCopy[i - 1][j + 1].rgbtBlue * gxMatrix[0][2]) +
                         (0 * gxMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gxMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtBlue * gxMatrix[2][2]);

                gyBlue = (0 * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gyMatrix[0][1]) +
                         (imageCopy[i - 1][j + 1].rgbtBlue * gyMatrix[0][2]) +
                         (0 * gyMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gyMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtBlue * gyMatrix[2][2]);

                image[i][j].rgbtBlue = pixelCap(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));
            }

            //check if you are on the upper edge
            else if (i == 0)
            {
                gxRed = (0 * gxMatrix[0][0]) + (0 * gxMatrix[0][1]) +
                        (0 * gxMatrix[0][2]) +
                        (imageCopy[i][j - 1].rgbtRed * gxMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gxMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gxMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtRed * gxMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtRed * gxMatrix[2][2]);

                gyRed = (0 * gyMatrix[0][0]) + (0 * gyMatrix[0][1]) +
                        (0 * gyMatrix[0][2]) +
                        (imageCopy[i][j - 1].rgbtRed * gyMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gyMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gyMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtRed * gyMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtRed * gyMatrix[2][2]);

                image[i][j].rgbtRed = pixelCap(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));

                gxGreen = (0 * gxMatrix[0][0]) + (0 * gxMatrix[0][1]) +
                          (0 * gxMatrix[0][2]) +
                          (imageCopy[i][j - 1].rgbtGreen * gxMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gxMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gxMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtGreen * gxMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtGreen * gxMatrix[2][2]);

                gyGreen = (0 * gyMatrix[0][0]) + (0 * gyMatrix[0][1]) +
                          (0 * gyMatrix[0][2]) +
                          (imageCopy[i][j - 1].rgbtGreen * gyMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gyMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gyMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtGreen * gyMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtGreen * gyMatrix[2][2]);

                image[i][j].rgbtGreen = pixelCap(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));

                gxBlue = (0 * gxMatrix[0][0]) + (0 * gxMatrix[0][1]) +
                         (0 * gxMatrix[0][2]) +
                         (imageCopy[i][j - 1].rgbtBlue * gxMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gxMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gxMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtBlue * gxMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtBlue * gxMatrix[2][2]);

                gyBlue = (0 * gyMatrix[0][0]) + (0 * gyMatrix[0][1]) +
                         (0 * gyMatrix[0][2]) +
                         (imageCopy[i][j - 1].rgbtBlue * gyMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gyMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gyMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtBlue * gyMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtBlue * gyMatrix[2][2]);

                image[i][j].rgbtBlue = pixelCap(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));
            }

            //check if you are on the right edge
            else if (j == width - 1)
            {
                gxRed = (imageCopy[i - 1][j - 1].rgbtRed * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gxMatrix[0][1]) +
                        (0 * gxMatrix[0][2]) +
                        (imageCopy[i][j - 1].rgbtRed * gxMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gxMatrix[1][1]) +
                        (0 * gxMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtRed * gxMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyRed = (imageCopy[i - 1][j - 1].rgbtRed * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gyMatrix[0][1]) +
                        (0 * gyMatrix[0][2]) +
                        (imageCopy[i][j - 1].rgbtRed * gyMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gyMatrix[1][1]) +
                        (0 * gyMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtRed * gyMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtRed = pixelCap(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));

                gxGreen = (imageCopy[i - 1][j - 1].rgbtGreen * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gxMatrix[0][1]) +
                          (0 * gxMatrix[0][2]) +
                          (imageCopy[i][j - 1].rgbtGreen * gxMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gxMatrix[1][1]) +
                          (0 * gxMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtGreen * gxMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyGreen = (imageCopy[i - 1][j - 1].rgbtGreen * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gyMatrix[0][1]) +
                          (0 * gyMatrix[0][2]) +
                          (imageCopy[i][j - 1].rgbtGreen * gyMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gyMatrix[1][1]) +
                          (0 * gyMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtGreen * gyMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtGreen = pixelCap(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));

                gxBlue = (imageCopy[i - 1][j - 1].rgbtBlue * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gxMatrix[0][1]) +
                         (0 * gxMatrix[0][2]) +
                         (imageCopy[i][j - 1].rgbtBlue * gxMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gxMatrix[1][1]) +
                         (0 * gxMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtBlue * gxMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyBlue = (imageCopy[i - 1][j - 1].rgbtBlue * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gyMatrix[0][1]) +
                         (0 * gyMatrix[0][2]) +
                         (imageCopy[i][j - 1].rgbtBlue * gyMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gyMatrix[1][1]) +
                         (0 * gyMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtBlue * gyMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtBlue = pixelCap(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));
            }

            //check if you are on the lower edge
            else if (i == height - 1)
            {
                gxRed = (imageCopy[i - 1][j - 1].rgbtRed * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gxMatrix[0][1]) +
                        (imageCopy[i - 1][j + 1].rgbtRed * gxMatrix[0][2]) +
                        (imageCopy[i][j - 1].rgbtRed * gxMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gxMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                        (0 * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyRed = (imageCopy[i - 1][j - 1].rgbtRed * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gyMatrix[0][1]) +
                        (imageCopy[i - 1][j + 1].rgbtRed * gyMatrix[0][2]) +
                        (imageCopy[i][j - 1].rgbtRed * gyMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gyMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                        (0 * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtRed = pixelCap(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));

                gxGreen = (imageCopy[i - 1][j - 1].rgbtGreen * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gxMatrix[0][1]) +
                          (imageCopy[i - 1][j + 1].rgbtGreen * gxMatrix[0][2]) +
                          (imageCopy[i][j - 1].rgbtGreen * gxMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gxMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                          (0 * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyGreen = (imageCopy[i - 1][j - 1].rgbtGreen * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gyMatrix[0][1]) +
                          (imageCopy[i - 1][j + 1].rgbtGreen * gyMatrix[0][2]) +
                          (imageCopy[i][j - 1].rgbtGreen * gyMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gyMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                          (0 * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtGreen = pixelCap(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));

                gxBlue = (imageCopy[i - 1][j - 1].rgbtBlue * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gxMatrix[0][1]) +
                         (imageCopy[i - 1][j + 1].rgbtBlue * gxMatrix[0][2]) +
                         (imageCopy[i][j - 1].rgbtBlue * gxMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gxMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gxMatrix[1][2]) + (0 * gxMatrix[2][0]) +
                         (0 * gxMatrix[2][1]) + (0 * gxMatrix[2][2]);

                gyBlue = (imageCopy[i - 1][j - 1].rgbtBlue * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gyMatrix[0][1]) +
                         (imageCopy[i - 1][j + 1].rgbtBlue * gyMatrix[0][2]) +
                         (imageCopy[i][j - 1].rgbtBlue * gyMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gyMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gyMatrix[1][2]) + (0 * gyMatrix[2][0]) +
                         (0 * gyMatrix[2][1]) + (0 * gyMatrix[2][2]);

                image[i][j].rgbtBlue = pixelCap(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));
            }

            else
            {
                gxRed = (imageCopy[i - 1][j - 1].rgbtRed * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gxMatrix[0][1]) +
                        (imageCopy[i - 1][j + 1].rgbtRed * gxMatrix[0][2]) +
                        (imageCopy[i][j - 1].rgbtRed * gxMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gxMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gxMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtRed * gxMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtRed * gxMatrix[2][2]);

                gyRed = (imageCopy[i - 1][j - 1].rgbtRed * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtRed * gyMatrix[0][1]) +
                        (imageCopy[i - 1][j + 1].rgbtRed * gyMatrix[0][2]) +
                        (imageCopy[i][j - 1].rgbtRed * gyMatrix[1][0]) + (imageCopy[i][j].rgbtRed * gyMatrix[1][1]) +
                        (imageCopy[i][j + 1].rgbtRed * gyMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtRed * gyMatrix[2][0]) +
                        (imageCopy[i + 1][j].rgbtRed * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtRed * gyMatrix[2][2]);

                image[i][j].rgbtRed = pixelCap(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));

                gxGreen = (imageCopy[i - 1][j - 1].rgbtGreen * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gxMatrix[0][1]) +
                          (imageCopy[i - 1][j + 1].rgbtGreen * gxMatrix[0][2]) +
                          (imageCopy[i][j - 1].rgbtGreen * gxMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gxMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gxMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtGreen * gxMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtGreen * gxMatrix[2][2]);

                gyGreen = (imageCopy[i - 1][j - 1].rgbtGreen * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtGreen * gyMatrix[0][1]) +
                          (imageCopy[i - 1][j + 1].rgbtGreen * gyMatrix[0][2]) +
                          (imageCopy[i][j - 1].rgbtGreen * gyMatrix[1][0]) + (imageCopy[i][j].rgbtGreen * gyMatrix[1][1]) +
                          (imageCopy[i][j + 1].rgbtGreen * gyMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtGreen * gyMatrix[2][0]) +
                          (imageCopy[i + 1][j].rgbtGreen * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtGreen * gyMatrix[2][2]);

                image[i][j].rgbtGreen = pixelCap(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));

                gxBlue = (imageCopy[i - 1][j - 1].rgbtBlue * gxMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gxMatrix[0][1]) +
                         (imageCopy[i - 1][j + 1].rgbtBlue * gxMatrix[0][2]) +
                         (imageCopy[i][j - 1].rgbtBlue * gxMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gxMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gxMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtBlue * gxMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gxMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtBlue * gxMatrix[2][2]);

                gyBlue = (imageCopy[i - 1][j - 1].rgbtBlue * gyMatrix[0][0]) + (imageCopy[i - 1][j].rgbtBlue * gyMatrix[0][1]) +
                         (imageCopy[i - 1][j + 1].rgbtBlue * gyMatrix[0][2]) +
                         (imageCopy[i][j - 1].rgbtBlue * gyMatrix[1][0]) + (imageCopy[i][j].rgbtBlue * gyMatrix[1][1]) +
                         (imageCopy[i][j + 1].rgbtBlue * gyMatrix[1][2]) + (imageCopy[i + 1][j - 1].rgbtBlue * gyMatrix[2][0]) +
                         (imageCopy[i + 1][j].rgbtBlue * gyMatrix[2][1]) + (imageCopy[i + 1][j + 1].rgbtBlue * gyMatrix[2][2]);

                image[i][j].rgbtBlue = pixelCap(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));
            }
        }
    }

    return;
}
