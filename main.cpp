#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


Mat image, image1, image2;
char* windowName = "Image Fusion";
char* trackBarName = "TrackBar";
int trackBarValue = 0;
int trackBarMax = 100;

//控制条回调函数  
void TrackBarFunc(int, void(*));
int main(int argc, char *argv[])
{
	image1 = imread("1.jpg");
	image2 = imread("2.jpg");
	//判断读入是否成功  
	if (!image1.data | !image2.data)
	{
		std::cout << "打开图片失败，请检查路径！" << std::endl;
		return 0;
	}
	//调整image2的大小与image1的大小一致，融合函数addWeighted()要求输入的两个图形尺寸相同  
	resize(image2, image2, Size(image1.cols, image1.rows));
	//建立显示窗口  
	namedWindow(windowName);
	//在图像窗口上创建控制条  
	createTrackbar(trackBarName, windowName, &trackBarValue, trackBarMax, TrackBarFunc);
	TrackBarFunc(0, 0);
	waitKey();
	return 0;
}
void TrackBarFunc(int, void(*))
{
	//转换成融合比例  
	float rate = (float)trackBarValue / trackBarMax;
	addWeighted(image1, rate, image2, 1 - rate, 0, image);
	imshow(windowName, image);
}
