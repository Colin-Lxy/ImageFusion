霓虹是用来描绘出图像的轮廓，勾画颜色变化的边缘，加强其过度效果，使图像产生轮廓发光的效果。

主要原理是：将当前像素与其同列正下方和右方的像素的RGB分量分别做梯度运算（差的平方和的平方根），运算结果作为当前的像素值。为了使图像轮廓边缘发光的效果更明显，可以适当地将运算结果乘以一个常数。 
假设有1,2,3三个像素，1是当前点，2是1同行的下一个像素，3是1同列正下方的像素。三个点的RGB分量分别是（r1,g1,b1），（r2,g2,b2），（r3,g3,b3）,R,G,B为计算后的结果，i 为常数那么转换公式如下：

R = i*sqrt( (r1-r2) * (r1-r2) + (r1-r3) * (r1-r3) )
G = i*sqrt( (g1-g2) * (g1-g2) + (g1-g3) * (g1-g3) )
B = i*sqrt( (b1-b2) * (b1-b2) + (b1-b3) * (b1-b3) )
RGB三个分量的值要控制在0~255之间。 
完整代码如下：




#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//#include "features2d.hpp"
#include<iostream>
using namespace std;
using namespace cv;

void niHongFilter(Mat &srcImage);

int main() {
	Mat srcImage = imread("12.jpg");//图片在工程目录下，否则写绝对路径

	if (!srcImage.data || srcImage.empty()) {
		cout << "读入图片错误！" << endl;
		return -1;
	}

	imshow("原图", srcImage);

	niHongFilter(srcImage);
	waitKey(0);
	return 0;
}

void niHongFilter(Mat &srcImage) {
	int rowNum = srcImage.rows;
	int colNum = srcImage.cols;

	for (int j = 0; j < rowNum - 1; j++) {
		uchar* data = srcImage.ptr<uchar>(j);
		for (int i = 0; i < colNum - 1; i++) {

			//当前像素的RGB分量
			int b1 = data[i * 3];
			int g1 = data[i * 3 + 1];
			int r1 = data[i * 3 + 2];

			//同行下一个像素的RGB分量
			int b2 = data[(i + 1) * 3];
			int g2 = data[(i + 1) * 3 + 1];
			int r2 = data[(i + 1) * 3 + 2];

			//指针移到下一行
			data = srcImage.ptr<uchar>(j + 1);

			//同列正下方的像素的RGB分量
			int b3 = data[i * 3];
			int g3 = data[i * 3 + 1];
			int r3 = data[i * 3 + 2];

			//指针移回来
			data = srcImage.ptr<uchar>(j);

			//计算新的RGB分量的值
			int R = 10 * sqrt((r1 - r2)*(r1 - r2) + (r1 - r3)*(r1 - r3));
			int G = 10 * sqrt((g1 - g2)*(g1 - g2) + (g1 - g3)*(g1 - g3));
			int B = 10 * sqrt((b1 - b2)*(b1 - b2) + (b1 - b3)*(b1 - b3));

			data[i * 3] = max(0, min(B, 255));;
			data[i * 3 + 1] = max(0, min(G, 255));;
			data[i * 3 + 2] = max(0, min(R, 255));;
		}
	}
	imshow("霓虹滤镜", srcImage);
}
