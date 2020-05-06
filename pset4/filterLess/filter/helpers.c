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

//check if the value is greater than 255 and if it is then make the value equal to 255, else leave it as is
int pixelCap(int pixelValue)
{
    if (pixelValue > 255)
    {
        pixelValue = 255;
    }
    return pixelValue;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = 0, sepiaGreen = 0, sepiaBlue = 0, tempRed = image[i][j].rgbtRed, tempGreen = image[i][j].rgbtGreen,
                  tempBlue = image[i][j].rgbtBlue;

            //compute the value for each sepia color
            sepiaRed = pixelCap(round((0.393 * tempRed) + (0.769 * tempGreen) + (0.189 * tempBlue)));
            sepiaGreen = pixelCap(round((0.349 * tempRed) + (0.686 * tempGreen) + (0.168 * tempBlue)));
            sepiaBlue = pixelCap(round((0.272 * tempRed) + (0.534 * tempGreen) + (0.131 * tempBlue)));

            //assign previously calculated values
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
