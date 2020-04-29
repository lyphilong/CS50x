#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void swap(BYTE *a, BYTE *b);
int roundIndex(float index);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i =0; i< height; i++){
        for(int j=0; j<width;j++){
            float avg = (float) (image[i][j].rgbtBlue + image[i][j].rgbtRed +image[i][j].rgbtGreen)/3;
            int round_avg = roundIndex(avg);
            image[i][j].rgbtBlue = round_avg;
            image[i][j].rgbtGreen = round_avg;
            image[i][j].rgbtRed = round_avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i =0; i< height; i++){
        for(int j=0; j<width/2;j++){
            swap(&image[i][j].rgbtRed,&image[i][width - j -1].rgbtRed);
            swap(&image[i][j].rgbtGreen,&image[i][width - j -1].rgbtGreen);
            swap(&image[i][j].rgbtBlue,&image[i][width - j-1].rgbtBlue);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE tmp[height][width];


     for(int i =0; i< height; i++){
        for(int j=0; j<width;j++){ //duyệt đến từng điểm pixel

            float count =1.0;
            int sumR =0;
            int sumG =0;
            int sumB =0;

            sumR = image[i][j].rgbtRed;
            sumG = image[i][j].rgbtGreen;
            sumB = image[i][j].rgbtBlue;


            //x o o
            //o + 0
            //o o o
            if(i - 1 >= 0 && j -1 >=0){
                count ++;
                sumR += image[i-1][j-1].rgbtRed;
                sumG += image[i-1][j-1].rgbtGreen;
                sumB += image[i-1][j-1].rgbtBlue;
            }

            //o x o
            //o + 0
            //o o o
            if(i-1>=0){
                count ++;
                sumR += image[i-1][j].rgbtRed;
                sumG += image[i-1][j].rgbtGreen;
                sumB += image[i-1][j].rgbtBlue;
            }

            //o o x
            //o + 0
            //o o o
            if(i-1 >=0  && j + 1 < width){
                count++;
                sumR += image[i-1][j+1].rgbtRed;
                sumG += image[i-1][j+1].rgbtGreen;
                sumB += image[i-1][j+1].rgbtBlue;
            }

            //o o o
            //o + x
            //o o o
            if(j + 1 < width){
                count++;
                sumR += image[i][j+1].rgbtRed;
                sumG += image[i][j+1].rgbtGreen;
                sumB += image[i][j+1].rgbtBlue;
            }

            //o o o
            //o + o
            //o o x
            if(i + 1 < height && j + 1 < width){
                count++;
                sumR += image[i+1][j+1].rgbtRed;
                sumG += image[i+1][j+1].rgbtGreen;
                sumB += image[i+1][j+1].rgbtBlue;
            }

            //o o o
            //o + o
            //o x o
            if(i + 1 < height){
                count++;
                sumR += image[i+1][j].rgbtRed;
                sumG += image[i+1][j].rgbtGreen;
                sumB += image[i+1][j].rgbtBlue;
            }

            //o o o
            //o + o
            //x o o
            if(i + 1 < height && j - 1 >=0){
                count++;
                sumR += image[i+1][j-1].rgbtRed;
                sumG += image[i+1][j-1].rgbtGreen;
                sumB += image[i+1][j-1].rgbtBlue;
            }

            //o o o
            //x + o
            //o o o
            if(j - 1 >=0){
                count++;
                sumR += image[i][j-1].rgbtRed;
                sumG += image[i][j-1].rgbtGreen;
                sumB += image[i][j-1].rgbtBlue;
            }


            tmp[i][j].rgbtRed = roundIndex(sumR/count);
            tmp[i][j].rgbtGreen =  roundIndex(sumG/count);
            tmp[i][j].rgbtBlue =  roundIndex(sumB/count);

        }
    }


     for(int i =0; i< height; i++){
        for(int j=0; j<width;j++){ //duyệt đến từng điểm pixel
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
     }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    RGBTRIPLE coppy[height + 2][width + 2];


    for(int i =0;i<height+2; i++){
        for (int j =0 ; j< width+2; j++){
            if( i == 0 || j == 0 || j == width + 1 || i == height +  1){
                coppy[i][j].rgbtRed =0;
                coppy[i][j].rgbtGreen =0;
                coppy[i][j].rgbtBlue =0;
            }
            else{
                coppy[i][j].rgbtRed = image[i-1][j-1].rgbtRed;
                coppy[i][j].rgbtGreen = image[i-1][j-1].rgbtGreen;
                coppy[i][j].rgbtBlue = image[i-1][j-1].rgbtBlue;
            }
        }
    }

    for(int i=1;i<height-1; i++){
        for(int j=1;j<width-1;j++){

            //TODO:
            //Tính theo hướng x cho 3 chanel
            int Gx_R= -1*coppy[i-1][j-1].rgbtRed -2*coppy[i][j-1].rgbtRed - 1*coppy[i+1][j-1].rgbtRed + 1*coppy[i-1][j+1].rgbtRed + 2*coppy[i][j+1].rgbtRed + 1*coppy[i+1][j+1].rgbtRed;
            int Gx_G = -1*coppy[i-1][j-1].rgbtGreen-2*coppy[i][j-1].rgbtGreen - 1*coppy[i+1][j-1].rgbtGreen + 1*coppy[i-1][j+1].rgbtGreen + 2*coppy[i][j+1].rgbtGreen + 1*coppy[i+1][j+1].rgbtGreen;
            int Gx_B = -1*coppy[i-1][j-1].rgbtBlue -2*coppy[i][j-1].rgbtBlue - 1*coppy[i+1][j-1].rgbtBlue + 1*coppy[i-1][j+1].rgbtBlue + 2*coppy[i][j+1].rgbtBlue + 1*coppy[i+1][j+1].rgbtBlue;

            //Tính theo hướng y cho 3 chanel
            int Gy_R = -1*coppy[i-1][j-1].rgbtRed -2*coppy[i-1][j].rgbtRed - 1*coppy[i-1][j+1].rgbtRed + 1*coppy[i+1][j-1].rgbtRed + 2*coppy[i+1][j].rgbtRed + 1*coppy[i+1][j+1].rgbtRed;
            int Gy_G = -1*coppy[i-1][j-1].rgbtGreen -2*coppy[i-1][j].rgbtGreen - 1*coppy[i-1][j+1].rgbtGreen + 1*coppy[i+1][j-1].rgbtGreen + 2*coppy[i+1][j].rgbtGreen + 1*coppy[i+1][j+1].rgbtGreen;
            int Gy_B = -1*coppy[i-1][j-1].rgbtBlue -2*coppy[i-1][j].rgbtBlue - 1*coppy[i-1][j+1].rgbtBlue + 1*coppy[i+1][j-1].rgbtBlue + 2*coppy[i+1][j].rgbtBlue + 1*coppy[i+1][j+1].rgbtBlue;

            //Tính gradient
            double red = sqrt((double)(Gx_R*Gx_R + Gy_R*Gy_R));
            double green = sqrt((double)(Gx_G*Gx_G + Gy_G*Gy_G));
            double blue = sqrt((double)(Gx_B*Gx_B + Gy_B*Gy_B));


            //Kiểm tra các giá trị của từng chanel trong đoạn [0,255]
            //RED
            if (red > 255)
            {
                red = 255;
            }
            else if (red < 0)
            {
                red = 0;

            }

            //GREEN
            if (green > 255)
            {
                green = 255;
            }
            else if (green < 0)
            {
                green = 0;

            }

            //BLUE
            if (blue > 255)
            {
                blue = 255;
            }
            else if (blue < 0)
            {
                blue = 0;

            }

            tmp[i][j].rgbtRed = (BYTE) red;
            tmp[i][j].rgbtGreen = (BYTE) green;
            tmp[i][j].rgbtBlue = (BYTE) blue;
        }
    }

    for(int i =0; i< height; i++){
        for(int j=0; j<width;j++){ //duyệt đến từng điểm pixel
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
     }


    return;
}


void swap(BYTE *a, BYTE *b){
    BYTE tmp = *a;
    *a = *b;
    *b = tmp;
}

int roundIndex(float index)
{
    int tmp = (int) index;
    float decimal = index - tmp;
    if (decimal >= 0.5)
    {
        return (tmp + 1);
    }
    else
    {
        return tmp;
    }
}