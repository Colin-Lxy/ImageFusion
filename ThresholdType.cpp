#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//#include "features2d.hpp"
#include<iostream>
using namespace std;
using namespace cv;

//#define WINDOW_NAME"程序窗口"

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage,g_dstImage;

//static void ShowhelpText();
void on_Threshold(int, void*);

int main()
{
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data)
	{
		printf("cuowu");
		return false;
	}
	imshow("原图", g_srcImage);
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
	namedWindow("程序窗口", WINDOW_AUTOSIZE);
	createTrackbar("模式", "程序窗口", &g_nThresholdType, 4, on_Threshold);
	on_Threshold(0, 0);
	while (1)
	{
		int key;
		key = waitKey(20);
		if ((char)key==27)
		{
			break;
		}
	}
	
}
void on_Threshold(int, void*)
{
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
	imshow("程序窗口", g_dstImage);
}
