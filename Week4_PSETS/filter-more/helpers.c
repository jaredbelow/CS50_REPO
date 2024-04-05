#include "helpers.h"
#include "math.h"
#include "stdio.h"

RGBTRIPLE calculate_average_color(int array1_index, int array2_index, int height, int width, RGBTRIPLE image[height][width]);
RGBTRIPLE calculate_edge(int array1_index, int array2_index, int height, int width, RGBTRIPLE image[height][width]);

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
            int color_average = round(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;

            // Assign value of average to each color of current pixel
            image[i][j].rgbtRed = color_average;
            image[i][j].rgbtGreen = color_average;
            image[i][j].rgbtBlue = color_average;
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
        // Iterate over half of image width to avoid double reflect
        // Ran into that issue while testing :)
        for (int j = 0; j < width / 2; j++)
        {
            // Initialize placeholder
            RGBTRIPLE tmp = image[i][j];

            // Swap pixels
            image[i][j] = image[i][width - j];
            image[i][width - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over image height
    for (int i = 0; i < height; i++)
    {
        // Iterate over image width
        for (int j = 0; j < width; j++)
        {
            // Helper function to avoid nested code
            image[i][j] = calculate_average_color(i, j, height, width, image);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Iterate over image height
    for (int i = 0; i < height; i++)
    {
        // Iterate over image width
        for (int j = 0; j < width; j++)
        {
            // Helper function to avoid nested code
            image[i][j] = calculate_edge(i, j, height, width, temp);
        }
    }
    return;
}

RGBTRIPLE calculate_average_color(int array1_index, int array2_index, int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize values
    RGBTRIPLE color_average;
    int pixels_in_box = 0;
    int r_value = 0;
    int g_value = 0;
    int b_value = 0;


    // Iterate over height of "box"
    for (int i = 0; i < 3; i++)
    {
        // Iterate over width of "box"
        for (int j = 0; j < 3; j++)
        {
            // Calculate current pixel in "box"
            int array1_calc = array1_index + i - 1;
            int array2_calc = array2_index + j - 1;

            // Accounting for pixels in "box" that are not within height of image
            if (array1_calc >= 0 && array2_calc <= height)
            {
                // Account for pixels in "box" that are not within width of image
                if (array2_calc >= 0 && array2_calc <= width)
                {
                // Adding to count for average & values of RGB
                pixels_in_box++;
                r_value += image[array1_calc][array2_calc].rgbtRed;
                g_value += image[array1_calc][array2_calc].rgbtGreen;
                b_value += image[array1_calc][array2_calc].rgbtBlue;
                }
            }
         }
   }

    // Averaging RGB per number of pixels in "box"
    color_average.rgbtRed = round(r_value / pixels_in_box);
    color_average.rgbtGreen = round(g_value / pixels_in_box);
    color_average.rgbtBlue = round(b_value / pixels_in_box);

    return color_average;
}

RGBTRIPLE calculate_edge(int array1_index, int array2_index, int height, int width, RGBTRIPLE image[height][width])
{
    // Initalize both matrix for later calculation
    RGBTRIPLE edge_pixel;
    int Gx_matrix[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy_matrix[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Initalize values
    float Gx_calc[3] = {0, 0, 0};
    float Gy_calc[3] = {0, 0, 0};

    // Iterate over height of "box"
    for (int i = 0; i < 3; i++)
    {
        // Iterate over width of "box"
        for (int j = 0; j < 3; j++)
        {
            // Calculate current pixel in "box"
            int array1_calc = array1_index + i - 1;
            int array2_calc = array2_index + j - 1;

            // Accounting for pixels in "box" that are not within image
            if ((array2_calc < 0 || array2_calc >= width) || (array1_calc < 0 || array1_calc >= height))
            {
                continue;
            }

            Gx_calc[0] += Gx_matrix[i][j] * image[array1_calc][array2_calc].rgbtRed;
            Gx_calc[1] += Gx_matrix[i][j] * image[array1_calc][array2_calc].rgbtGreen;
            Gx_calc[2] += Gx_matrix[i][j] * image[array1_calc][array2_calc].rgbtBlue;

            Gy_calc[0] += Gy_matrix[i][j] * image[array1_calc][array2_calc].rgbtRed;
            Gy_calc[1] += Gy_matrix[i][j] * image[array1_calc][array2_calc].rgbtGreen;
            Gy_calc[2] += Gy_matrix[i][j] * image[array1_calc][array2_calc].rgbtBlue;

        }
    }

    // Set RGB values to Sobel calculation capped at 255
    edge_pixel.rgbtRed = round(sqrt(Gx_calc[0] * Gx_calc[0] + Gy_calc[0] * Gy_calc[0]));
    edge_pixel.rgbtRed = (edge_pixel.rgbtRed > 255) ? 255 : edge_pixel.rgbtRed;

    edge_pixel.rgbtGreen = round(sqrt(Gx_calc[1] * Gx_calc[1] + Gy_calc[1] * Gy_calc[1]));
    edge_pixel.rgbtGreen = (edge_pixel.rgbtGreen > 255) ? 255 : edge_pixel.rgbtGreen;

    edge_pixel.rgbtBlue = round(sqrt(Gx_calc[2] * Gx_calc[2] + Gy_calc[2] * Gy_calc[2]));
    edge_pixel.rgbtBlue = (edge_pixel.rgbtBlue > 255) ? 255 : edge_pixel.rgbtBlue;

    return edge_pixel;
}
