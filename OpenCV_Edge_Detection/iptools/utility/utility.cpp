#include "utility.h"
#include "../iptools/core.h"
#include "../image/image.h"
#include <string.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <math.h>

#define MAXRGB 255
#define MINRGB 0

using namespace cv;

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
		}
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold)
				tgt.setPixel(i,j,MINRGB);
			else
				tgt.setPixel(i,j,MAXRGB);
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::cv_gray(Mat &src, Mat &tgt)
{
	cvtColor(src, tgt, COLOR_BGR2GRAY);
}

/*-----------------------------------------------------------------------**/
void utility::cv_avgblur(Mat &src, Mat &tgt, int WindowSize)
{
	blur(src,tgt,Size(WindowSize,WindowSize));
}



/*---------------------------------------------------------------------------------------------------------------**
***								PART 1: ADVANCED EDGE DETECTION WITH OPENCV										***
*---------------------------------------------------------------------------------------------------------------**/
// void utility::binaryedge3(Mat &src, Mat &tgt)
// {
// 	int Sx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};    //horizontal sobel operator
//     //apply sobel at x,y in src image
//     int Gx = 0;    //value of estimated gradient

//     // convolution of S & src kernel.
//     for(int i = 0; i < 3; i++){    //for each pixel in the kernel
//         for(int j = 0; j < 3; j++){
//             Gx += S[i][j] * src.getPixel(x-i,y-j,chan);
//         }
//     }


// 	int Sy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};    //vertical sobel operator
//     //apply sobel at x,y in src image
//     int Gy = 0;    //value of estimated gradient
//     for(int i = 0; i < 3; i++){    //for each pixel in the kernel
//         for(int j = 0; j < 3; j++){
//             Gy += S[i][j] * src.getPixel(x-i,y-j,chan);
//         }
//     }




// 	tgt.copyImage(src);
//     float buffer[src.getNumberOfRows()][src.getNumberOfColumns()];// = {0};    //buffer to temporarily store grad values
//     for(int i = 0; i < src.getNumberOfRows(); i++){//for each pixel in roi
//         for(int j = 0; j<src.getNumberOfColumns(); j++){
//             if (roi.InROI(i,j)){
//                 buffer[i][j] = sobelMagnitude(src,chan,i,j);//get gradient magnitudes
//             }else{
//                 buffer[i][j] = 0;
//             }
//         }
//     }
//     //BEGIN thresholdGrad
//     for(int i = 0; i < src.getNumberOfRows(); i++){//for each pixel in roi
//         for(int j = 0; j<src.getNumberOfColumns(); j++){
//             if (roi.InROI(i,j)){
//                 if(buffer[i][j] < thresh){
//                     tgt.setPixel(i,j,chan,0);
//                 }else{    //buffer[i][j] >= thresh
//                     tgt.setPixel(i,j,chan,255);
//                 }
//             }else{//copy pixel
//                 tgt.setPixel(i,j,chan,src.getPixel(i,j,chan));
//             }
//         }
//     }


// }// end binaryedge3() function




/*----------------------- GAUSSIAN SMOOTHING WITH 5X5 KERNEL SIZE -----------------------**/
void utility::gausobel5(Mat &src, Mat &tgt) 
{
	Mat temp;
	// GaussianBlur(src, temp, Size(3, 3), 0, 0);	// output file: jackie_gaus3.ppm	parameter.txt: baboon.pgm baboon_gaus3.ppm opencv gausobel5
	GaussianBlur(src, temp, Size(5, 5), 0, 0);	// output file: jackie_gaus5.ppm	parameter.txt: baboon.pgm baboon_gaus5.ppm opencv gausobel5
	// GaussianBlur(src, temp, Size(9, 9), 0, 0);	// output file: jackie_gaus9.ppm	parameter.txt: baboon.pgm baboon_gaus9.ppm opencv gausobel5
	Sobel(temp, tgt, CV_32F, 1, 1, 5);
}



/*---------------------------------------------------------------------------------------------------------------**
***								PART 2: ADVANCED EDGE DETECTION WITH OPENCV										***
*---------------------------------------------------------------------------------------------------------------**/

/*---------------------------------------------------------------------------------------------------------------**
***									PART A: SOBEL OPERATOR USING OPENCV											***
*---------------------------------------------------------------------------------------------------------------**/

// void utility::practice(Mat &src)
// {
// 	Mat image = imread(src, IMREAD_GRAYSCALE);
// 	namedWindow("outputImage");

// 	imshow("outputImage", image);
// 	waitKey(0);
// }

void utility::cv_extraCredit(Mat &src, Mat &tgt) 
{
	Mat temp, converted; 
	GaussianBlur(src, temp, Size(3, 3), 5, 0);
	cvtColor(temp, converted, COLOR_BGR2HSV);


	Mat channel[3];
	split(converted, channel);

	Canny(channel[0], channel[0], 100, 200);
	Canny(channel[1], channel[1], 100, 200);
	Canny(channel[2], channel[2], 100, 200);

	merge(channel, 3, tgt);

}// end cv_extraCredit() function


void utility::cv_sobel3(Mat &src, Mat &tgt)
{
	// Mat temp;
	// GaussianBlur(src, temp, Size(5, 5), 7, 0);
	// Sobel(src, tgt, -1, 1, 0, 3);	// jackie-sobel-2.ppm
	// Sobel(src, tgt, -1, 0, 1, 3);	// jackie-sobel-3.ppm
	// Sobel(src, tgt, -1, 1, 1, 3, 1, 1);	//jackie-sobel-4

	// shrek-gallery-3.ppm shrek-sobel-3.ppm opencv sobel3
	//jackie-chan-confused.jpg jackie-sobel-perfect.pgm opencv sobel3
	Mat srcGrey, temp;
	cvtColor(src, srcGrey, COLOR_BGR2GRAY);
	// Sobel(srcGrey, temp, CV_32F, 1, 1, 3, 4, 1);

	Sobel(srcGrey, temp, CV_32F, 1, 1, 3);

	double min, max;
    minMaxLoc(temp, &min, &max); //find minimum and maximum intensities

    // Mat draw;
    temp.convertTo(tgt, CV_8U, 255.0/(max - min), -min * 255.0/(max - min));

}// end cv_sobel3() function

// void utility::cv_sobel3(Mat &src, Mat &tgt, int XL, int YL, int xLen, int yLen)
// {
// 	Mat image = imread(src);
// 	namedWindow("outputImage");

// 	imshow("outputImage", image);

// }// end cv_sobel3() function



// void utility::cv_sobel5(Mat &src, Mat &tgt, int XL, int YL, int xLen, int yLen)
void utility::cv_sobel5(Mat &src, Mat &tgt)
{
	//Lenna.png Lenna-sobel5-2.pgm opencv sobel5

	Mat srcGrey, temp;
	cvtColor(src, srcGrey, COLOR_BGR2GRAY);
	// Sobel(srcGrey, temp, CV_32F, 1, 1, 3, 4, 1);

	Sobel(srcGrey, temp, CV_32F, 1, 1, 5);

	double min, max;
    minMaxLoc(temp, &min, &max); //find minimum and maximum intensities

    // Mat draw;
    temp.convertTo(tgt, CV_8U, 255.0/(max - min), -min * 255.0/(max - min));
}// end cv_sobel5() function


/*----------------------- OTSU THRESHOLDING -----------------------**/
void utility::cv_otsu(Mat &src, Mat &tgt) 
{
	Mat makeGray, temp;
	cvtColor(src, makeGray, COLOR_BGR2GRAY);
	Sobel(makeGray, temp, -1, 1, 1, 3);
	threshold(temp, tgt, 0, 255, THRESH_OTSU);

}// end cv_otsu() function


/*----------------------- CANNY TECHNIQUE -----------------------**/
void utility::cv_canny(Mat &src, Mat &tgt) 
{
	// variables for dimensions
	// int width = xLen + XL;
	// int height = yLen + YL;

	Mat temp;

	// GaussianBlur(src, temp, Size(5, 5), 5, 0); // JACKIE-CANNY-12
	// GaussianBlur(src, temp, Size(5, 5), 3, 0);	// JACKIE-CANNY-13	jackie-chan-confused.jpg jackie-canny15.pgm opencv canny

	// SHREK
	GaussianBlur(src, temp, Size(5, 5), 7, 0);	//shrek-canny-5		shrek-gallery-3.jpg shrek-canny5.pgm opencv canny
	// GaussianBlur(src, temp, Size(5, 5), 0, 0);	//shrek-canny-6
	// GaussianBlur(src, temp, Size(5, 5), 3, 0);	//shrek-canny-7

	Canny(temp, tgt, 50, 75);

	// #1 = 25 75
	// #2 = 50, 100
	// #3 = 50, 75


}// end cv_canny() function



// void utility::cv_otsu(Mat &src, Mat &tgt, int XL, int YL, int xLen, int yLen)
// {
// 	// variables for dimensions
// 	int width = xLen + XL;
// 	int height = yLen + YL;



// } // end cv_otsu() function



// void utility::cv_canny(Mat &src, Mat &tgt, int XL, int YL, int xLen, int yLen) 
// {
// 	// variables for dimensions
// 	int width = xLen + XL;
// 	int height = yLen + YL;

// 	Mat img = imread(src);

// 	Canny();


// }// end cv_canny() function

// void utility::cv_canny(Mat &src, Mat &tgt) 
// {

// 	Mat img = imread("baboon.pgm");
// 	// Mat blurred; 
// 	GaussianBlur(img, tgt, Size(3,3), 0);

// }

