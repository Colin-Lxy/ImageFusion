#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//#include "features2d.hpp"
#include<iostream>
using namespace std;
using namespace cv;


int main()
{
	Mat image = imread("23.jpg");
	namedWindow("原图");
	namedWindow("高斯滤波");
	imshow("原图", image);
	Mat dstImage;
	GaussianBlur(image, dstImage, Size(3, 3), 0, 0);
	imshow("高斯滤波",dstImage);

	waitKey();
	return 0;

}
