#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//#include "features2d.hpp"
#include<iostream>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "【程序窗体1】"        //为窗体标题定义的宏  
#define WINDOW_NAME2 "【程序窗体2】"        //为窗体标题定义的宏  

//-----------------------------------【全局变量声明部分】--------------------------------------
//		描写叙述：全局变量声明
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_srcImage1, g_grayImage;
int thresh = 30; //当前阈值
int max_thresh = 175; //最大阈值


					  //-----------------------------------【全局函数声明部分】--------------------------------------
					  //		描写叙述：全局函数声明
					  //-----------------------------------------------------------------------------------------------
void on_CornerHarris(int, void*);//回调函数
static void ShowHelpText();

//-----------------------------------【main( )函数】--------------------------------------------
//		描写叙述：控制台应用程序的入口函数。我们的程序从这里開始执行
//-----------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//【0】改变console字体颜色
	system("color 3F");

	//【0】显示帮助文字
	ShowHelpText();

	//【1】加载原始图并进行克隆保存
	g_srcImage = imread("1.jpg", 1);
	if (!g_srcImage.data) { printf("读取图片错误，请确定文件夹下是否有imread函数指定的图片存在~！ \n"); return false; }
	imshow("原始图", g_srcImage);
	g_srcImage1 = g_srcImage.clone();

	//【2】存留一张灰度图
	cvtColor(g_srcImage1, g_grayImage, CV_BGR2GRAY);

	//【3】创建窗体和滚动栏
	namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
	createTrackbar("阈值: ", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris);

	//【4】调用一次回调函数。进行初始化
	on_CornerHarris(0, 0);

	waitKey(0);
	return(0);
}

//-----------------------------------【on_HoughLines( )函数】--------------------------------
//		描写叙述：回调函数
//----------------------------------------------------------------------------------------------

void on_CornerHarris(int, void*)
{
	//---------------------------【1】定义一些局部变量-----------------------------
	Mat dstImage;//目标图
	Mat normImage;//归一化后的图
	Mat scaledImage;//线性变换后的八位无符号整型的图

					//---------------------------【2】初始化---------------------------------------
					//置零当前须要显示的两幅图，即清除上一次调用此函数时他们的值
	dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage1 = g_srcImage.clone();

	//---------------------------【3】正式检測-------------------------------------
	//进行角点检測
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);

	// 归一化与转换
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//将归一化后的图线性变换成8位无符号整型 

											//---------------------------【4】进行绘制-------------------------------------
											// 将检測到的，且符合阈值条件的角点绘制出来
	for (int j = 0; j < normImage.rows; j++)
	{
		for (int i = 0; i < normImage.cols; i++)
		{
			if ((int)normImage.at<float>(j, i) > thresh + 80)
			{
				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}
	//---------------------------【4】显示终于效果---------------------------------
	imshow(WINDOW_NAME1, g_srcImage1);
	imshow(WINDOW_NAME2, scaledImage);

}

//-----------------------------------【ShowHelpText( )函数】----------------------------------
//		描写叙述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//输出一些帮助信息
	printf("\n\n\n\t\t\t【欢迎来到Harris角点检測演示样例程序~】\n\n");
	printf("\n\n\n\t请调整滚动栏观察图像效果~\n\n");
	printf("\n\n\t\t\t\t\t\t\t\t by浅墨"
	);
}
