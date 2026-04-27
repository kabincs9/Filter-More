#include "helpers.h"
#include <math.h>
// as we need grayscale reflect blur and edges and look each section in problems key
// we can use 1 byte(8bits) per color  as 255 is one byte as 2^8−1=255 so 8bits = 1 bytes
// 3 bytes we can use 24 bits per pixel
// Convert image to grayscale
// bmp.h is going to store information about images bit map
// filter.c to run filters
// in bmp.h there is struct defined
// typedef struct
//
//   BYTE  rgbtBlue; store byte which is just 8bits
//  BYTE  rgbtGreen;
// BYTE  rgbtRed;
//
void grayscale(
    int height, int width,
    RGBTRIPLE image[height][width]) // two dimentional array RGBTRIPLE image[height][width]) as
                                    // image [0] zero as first row 1 as second ...coloum..
{
    // to turn black and white

    for (int i = 0; i < height; i++) // i is row and j is coloumn
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) /
                            3.0; // as to calculate average (avg)//
            // and 3.0 like 7/3 = 2 so a float forces floating point 2.3333
            // for average of three
            // round takes float or double and return to average like 2.33 = 2.0  as more accurate
            // or... av....3.0 +0.5 if using round() as math.h we can directly int gray =
            // round(average) and ? can all handle if and else also if need faster way
            int gray = round(average);
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
            // making it to shade of gray // so change colour like is 149 is gray
        }
    }
}

/// so for example to turn red to black image[2][3].rgbtRed = 0;

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // i is row and j is coloumn
    {
        for (int j = 0; j < width / 2;
             j++) // loop over the half of the coloumn to avoid over looping eg width=4 j is o to 1
        {
            RGBTRIPLE temp = image[i][j]; // store  left pixel image [i][j] in temporary rgbttr...
            image[i][j] =
                image[i][width - 1 - j];    // replace left pixel with right pixel j=0, width - 1 -j
            image[i][width - 1 - j] = temp; // place the stored left pixel in the right position
        }
    }
}

// Blur image
//   //average of the values of all of the pixels that are within 1 row and column of the original
//   pixel (forming a 3x3 box)
// each of the color values for pixel 6 would be obtained by averaging the original color values of
// pixels 1, 2, 3, 5, 6, 7, 9, 10, and 11
// (note that pixel 6 itself is included in the average)
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++) // i is row and j is coloumn row to copy image
    {
        for (int j = 0; j < width; j++)

        {
            {
                temp[i][j] = image[i][j]; // copy the pixel RGB value to temp
            }
        }
    }

    for (int i = 0; i < height; i++) // loop rows to complete blur
    {
        for (int j = 0; j < width; j++)

        {
            float sumRed = 0, sumGreen = 0, sumBlue = 0; // float the variable to the sum
            int count = 0;                               // to track the valid for 1 to 9
            for (int bluri = -1; bluri <= 1; bluri++)    // loops over rows offsets(-1,0,1) for 3*3
            {
                for (int blurj = -1; blurj <= 1; blurj++) // ,, coloumn
                {
                    int newI = i + bluri; // to calculate row index
                    int newJ = j + blurj;
                    if (newI >= 0 && newI < height && newJ >= 0 &&
                        newJ < width) // avoid negative or beyond height or width
                    {
                        sumRed += temp[newI][newJ].rgbtRed; // to add red green blue value from temp
                        sumGreen += temp[newI][newJ].rgbtGreen;
                        sumBlue += temp[newI][newJ].rgbtBlue;
                        count++; // increment for each validation
                    }
                }
            }
            image[i][j].rgbtRed =
                round(sumRed / count); // divide sum by count to get the average; using float
            image[i][j].rgbtGreen = round(sumGreen / count); // and round to nearest using round
            image[i][j].rgbtBlue = round(sumBlue / count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Like image blurring, edge detection also works by taking each pixel,
    // and modifying it based on the 3x3 grid of pixels that surrounds that pixel.
    // -1 of i and +1 of i

    RGBTRIPLE temp[height][width]; // not image

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j]; // copies values image to temp like rgbtRed....
        }
    } // 3*3 matrix
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2,
         1}}; // measured horizontal and vertical Gx ans Gy gradient pre defined in code Gx and Gy

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)

        {
            float GxRed = 0, GxGreen = 0, GxBlue = 0;
            float GyRed = 0, GyGreen = 0, GyBlue = 0;

            // Gx for horizontal and Gy for vertical line

            for (int bluri = -1; bluri <= 1; bluri++) // to loop over row offsets(-1,0,1)
            {
                for (int blurj = -1; blurj <= 1; blurj++) // to coloumm ... same

                {
                    int newI = i + bluri; // to calculate row index like i + blur i;
                    int newJ = j + blurj;
                    if (newI >= 0 && newI < height && newJ >= 0 &&
                        newJ < width) // avoid negative or beyond height or width// capital J
                    {
                        int k = bluri + 1;
                        int l = blurj + 1;
                        GxRed += temp[newI][newJ].rgbtRed * Gx[k][l]; // Gx for rgb and Gy for rgb
                        GxGreen += temp[newI][newJ].rgbtGreen * Gx[k][l];
                        GxBlue += temp[newI][newJ].rgbtBlue * Gx[k][l];
                        GyRed += temp[newI][newJ].rgbtRed * Gy[k][l]; // Gx for rgb and Gy for rgb
                        GyGreen += temp[newI][newJ].rgbtGreen * Gy[k][l];
                        GyBlue += temp[newI][newJ].rgbtBlue * Gy[k][l];
                        // for eg multiply the neighbors red value (from temp) by corresponding to
                        // Gx kernel value  Gx[k][l] and adds OxRed
                    }
                }
            }
            // sqrt is square root of

            int red = round(
                sqrt(GxRed * GxRed +
                     GyRed * GyRed)); // computes magnitude for red using sobel formula sqrt(OxRed^2
                                      // + OxGreen^2) and use round for nearest value
            int green =
                round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen)); // same rgb// sqrt from math.h
            int blue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            if (red > 255) // if max rgb or else
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
}

// sets pixel RGB value to computed gradient magnitude ...
