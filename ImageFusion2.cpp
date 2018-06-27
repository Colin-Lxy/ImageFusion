#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include"opencv2/features2d/features2d.hpp"
//#include"opencv2/legacy/legacy.hpp"
//#include"Homography.h"
#include "features2d.hpp"
#include<iostream>
using namespace std;
using namespace cv;


#define WINDOW_NAME "线性混合"

const int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlide;
double g_dAlphaValue;
double g_dBetaValue;

Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void on_Trackbar(int, void*)
{
	g_dAlphaValue = (double)g_nAlphaValueSlide / g_nMaxAlphaValue;
	g_dBetaValue = (1.0 - g_dAlphaValue);
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
	imshow(WINDOW_NAME, g_dstImage);

}
int main(int argc, char** argv)
{
	g_srcImage1 = imread("33.jpg");//尺寸要相同
	g_srcImage2 = imread("44.jpg");
	if (!g_srcImage1.data)
	{
		return -1;
	}
	if (!g_srcImage2.data)
	{
		return -1;
	}

	g_nAlphaValueSlide = 70;
	namedWindow(WINDOW_NAME, 1);
	char TrackbarName[50];
	sprintf_s(TrackbarName, "透明纸%d", g_nMaxAlphaValue);
	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlide, g_nMaxAlphaValue, on_Trackbar);

	on_Trackbar(g_nAlphaValueSlide, 0);

	waitKey();
	return 0;
}
