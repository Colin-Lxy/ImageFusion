#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//#include "features2d.hpp"
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
	//定义相关变量
	Mat image;
	Mat imageGray;
	Mat imageGreenChannel, imageBlueChannel, imageRedChannel;
	Mat imageBlue, imagePurple, imageGreen, imageYellow, imageRed;
	vector<Mat> channels;

	image = imread("2.jpg");       //读入原图
	imageGray = imread("2.jpg", 0); //读入灰度图

														   /***************得到蓝色通道图和紫色通道图*****************/
	split(image, channels);//分离彩色通道

	imageBlueChannel = channels.at(0); //蓝色通道的引用返回给imagBlueChannel
	addWeighted(imageBlueChannel, 1.0, imageGray, 0.5, 0, imageBlueChannel);//混合后的蓝色通道

	merge(channels, imageBlue);//此时蓝色通道已经变味了，
							   //再通过merge将三个通道重新合并成一个三通道，便得到蓝色通道图

	imageRedChannel = channels.at(2);  //在上面处理后的基础上，分离红色通道，可得到紫色通道图
	addWeighted(imageRedChannel, 1.0, imageGray, 0.5, 0, imageRedChannel);
	merge(channels, imagePurple);

	imshow("blue", imageBlue);
	imshow("purple", imagePurple);

	/***************得到绿色通道图和黄色通道图*****************/
	split(image, channels);//要想出现绿色的图像,需要对原图进行重新分离
	imageGreenChannel = channels.at(1);
	addWeighted(imageGreenChannel, 1.0, imageGray, 0.5, 0, imageGreenChannel);
	merge(channels, imageGreen);

	imageGreenChannel = channels.at(2);
	addWeighted(imageRedChannel, 1.0, imageGray, 0.5, 0, imageRedChannel);
	merge(channels, imageYellow);

	imshow("green", imageGreen);
	imshow("yellow", imageYellow);

	/***************得到红色通道图*****************/
	split(image, channels);
	imageRedChannel = channels.at(2);
	addWeighted(imageRedChannel, 1.0, imageGray, 0.5, 0, imageRedChannel);
	merge(channels, imageRed);

	imshow("red", imageRed);
	waitKey(0);
	return 0;
}
