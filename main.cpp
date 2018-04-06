#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

int main(void) {
	Mat img = imread("baboon.jpg");
	if (img.empty()) {
		std::cout << " not found" << std::endl;
		return -1;
	}
	
	int k;
	std::cout << "配列の数を入力してください" << std::endl;
	std::cin >> k;

	Mat dst = Mat::zeros(img.rows, img.cols, CV_8UC3);

	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			int b = 0, g = 0, r = 0;
			for (int i = (k - 1) / 2; i < ((k - 1) / 2) + k; i++) {
				for (int j = (k - 1) / 2; j < ((k - 1) / 2) + k; j++) {
					int s = y - i;
					int t = x - j;
					if (s < 0) {
						s = 0;
					}
					if (s >= img.rows) {
						s = img.rows - 1;
					}
					if (t < 0) {
						t = 0;
					}
					if (t >= img.cols) {
						t = img.cols - 1;
					}
					Vec3b tmp = img.at<Vec3b>(s, t);
					b += tmp[0];
					g += tmp[1];
					r += tmp[2];
				}
			}
			b = b / (k*k);
			g = g / (k*k);
			r = r / (k*k);
			dst.at<Vec3b>(y, x) = Vec3b(b, g, r);
		}
	}

	imshow("View", img);
	imshow("Filter", dst);
	imwrite("Average_Filter.jpg", dst);
	waitKey();

	return 0;
}