//通过掩膜提高图片对比度
#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;

int main()
{
	Mat dst;
	Mat src = imread("F:/image/1.2.png");//灰度图等价于二值化IMREAD_GRAYSCALE
	if (!src.data)
	{
		printf("can not load the picture\n");
		return 0;
	}
	namedWindow("p1", WINDOW_AUTOSIZE);//显示图像，自动窗口
	imshow("p1", src);


	int cols = (src.cols - 1) * src.channels();
	int offsetx = src.channels();
	int rows = src.rows;
	//掩膜操作后，提高对比度
	dst = Mat::zeros(src.size(), src.type());//关于dat的定义问题，此处是否可以改进
	int row = 0;
	int col = 0;
	for (row = 1; row < (rows - 1); row++)
	{
		const uchar* previous = src.ptr<uchar>(row - 1);
		const uchar* current = src.ptr<uchar>(row);
		const uchar* next = src.ptr<uchar>(row + 1);
		uchar* output = dst.ptr<uchar>(row);
		for (col = offsetx; col < cols; col++)
		{
			output[col] = saturate_cast<uchar>(5 * current[col] - (current[col - offsetx] + current[col + offsetx] + previous[col] + next[col]));
		}
	}
	namedWindow("output", WINDOW_AUTOSIZE);
	imshow("output", dst);
	waitKey(0);
	return 0;
}