#include "helpers.h"
#include "math.h"
#include "stdio.h"

RGBTRIPLE sepiaFilter(RGBTRIPLE image);
RGBTRIPLE calculateAverageColor(int posX, int posY, int height, int width,
                                RGBTRIPLE tempImage[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over image height
    for (int i = 0; i < height; i++)
    {
        // Iterate over image width
        for (int j = 0; j < width; j++)
        {
            // Get the average of color at current pixel
            // Cast sum of pixels as float to avoid integer truncation
            int colorAverage = round(
                (float) (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);

            // Assign value of average to each color of current pixel
            image[i][j].rgbtRed = colorAverage;
            image[i][j].rgbtGreen = colorAverage;
            image[i][j].rgbtBlue = colorAverage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over image height
    for (int i = 0; i < height; i++)
    {
        // Iterate over image width
        for (int j = 0; j < width; j++)
        {
            // Helper function to assign new value of pixel
            image[i][j] = sepiaFilter(image[i][j]);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over image height
    for (int i = 0; i < height; i++)
    {
        // Iterate over half of image width to avoid double reflection
        for (int j = 0; j < round(width / 2); j++)
        {
            // Initialize placeholder
            RGBTRIPLE tmp = image[i][j];

            // Swap pixels
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp image array for calculation
    RGBTRIPLE tempImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempImage[i][j] = image[i][j];
        }
    }

    // Iterate over image height
    for (int i = 0; i < height; i++)
    {
        // Iterate over image width
        for (int j = 0; j < width; j++)
        {
            // Helper function to avoid nested code
            image[i][j] = calculateAverageColor(i, j, height, width, tempImage);
        }
    }
    return;
}

RGBTRIPLE sepiaFilter(RGBTRIPLE image)
{
    // Initalize value of original colors
    int red = image.rgbtRed;
    int green = image.rgbtGreen;
    int blue = image.rgbtBlue;

    // Create placeholder pixel array
    RGBTRIPLE newPixel;

    // Compute sepia calculation & round to nearest int
    int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
    int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
    int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

    // Cap values to 255
    sepiaRed = sepiaRed > 255 ? 255 : sepiaRed;
    sepiaGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
    sepiaBlue = sepiaBlue > 255 ? 255 : sepiaBlue;

    // Assign values to new pixel
    newPixel.rgbtRed = sepiaRed;
    newPixel.rgbtGreen = sepiaGreen;
    newPixel.rgbtBlue = sepiaBlue;

    return newPixel;
}

RGBTRIPLE calculateAverageColor(int posX, int posY, int height, int width,
                                RGBTRIPLE tempImage[height][width])
{
    // Initialize values
    RGBTRIPLE newPixel;
    int pixelsInBox = 0;
    int rValue = 0;
    int gValue = 0;
    int bValue = 0;

    // Iterate over height of "box"
    for (int i = 0; i < 3; i++)
    {
        // Iterate over width of "box"
        for (int j = 0; j < 3; j++)
        {
            // Calculate current pixel in "box"
            int xCalc = posX + i - 1;
            int yCalc = posY + j - 1;

            // Accounting for pixels in "box" that are not within image
            if ((xCalc >= 0 && xCalc < height) && (yCalc >= 0 && yCalc < width))
            {
                // Adding to count for average & values of RGB
                pixelsInBox++;
                rValue += tempImage[xCalc][yCalc].rgbtRed;
                gValue += tempImage[xCalc][yCalc].rgbtGreen;
                bValue += tempImage[xCalc][yCalc].rgbtBlue;
            }
        }
    }

    // Averaging RGB per number of pixels in "box"
    // Cast colorValue as float to avoid integer truncation before rounding
    newPixel.rgbtRed = round((float) rValue / pixelsInBox);
    newPixel.rgbtGreen = round((float) gValue / pixelsInBox);
    newPixel.rgbtBlue = round((float) bValue / pixelsInBox);

    return newPixel;
}
