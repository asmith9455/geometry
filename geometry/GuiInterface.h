#pragma once
#include <Matrix.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

class GuiInterface {

public:

	GuiInterface() {}
	
	//PolygonMask<PointN, component_t, 2, component_t> pm
	static void show_image() {
		cv::Mat img = cv::imread("test.jpg");
		cv::imshow("test", img);

		cv::waitKey(0);
		cv::destroyAllWindows();
	}

	static void draw_vertical_line(cv::Mat& img, double width_factor) {
		cv::line(img, cv::Point(static_cast<int>(img.cols * width_factor), 0), 
			cv::Point(static_cast<int>(img.cols * width_factor), img.rows - 1), cv::Scalar(0, 0, 255, 255), 1);
	}

	static void draw_horizontal_line(cv::Mat& img, double height_factor) {
		cv::line(img, cv::Point(0, static_cast<int>(img.rows * height_factor)), 
			cv::Point(img.cols - 1, static_cast<int>(img.rows * height_factor)), cv::Scalar(0, 0, 255, 255), 1);
	}

	template<class T>
	static void show_image(std::string name, Matrix<T> m, bool close_all_windows = false) {

		{ //UNCOMMENT TO DISPLAY EACH ITERATION
			int tmp_min = m.min();
			int tmp_max = m.max();

			std::cout << "---------------------------------------------------" << std::endl;
			std::cout << "Name is: " << name << std::endl;
			std::cout << "Original Min -> Max: " << tmp_min << " -> " << tmp_max << std::endl;

			m.subtract(tmp_min);
			double factor = 250.0 / static_cast<double>(tmp_max - tmp_min);
			m.multiply_double(factor);

			std::cout << "Adjusted Min -> Max: " << m.min() << " -> " << m.max() << std::endl;

			std::cout << "dimension: " << m.width() << " x " << m.height() << std::endl;

			std::cout << "---------------------------------------------------" << std::endl;
		}



		cv::Mat img = cv::Mat(static_cast<int>(m.height()), static_cast<int>(m.width()), CV_8U);

		for (int y = 0; y<img.rows; y++)
		{
			for (int x = 0; x<img.cols; x++)
			{
				int adjusted_y = img.rows - 1 - y;

				// get pixel
				//Vec3b color = image.at<Vec3b>(Point(x, y));

				uchar map_col = m(adjusted_y, x);

				// set pixel
				img.at<uchar>(cv::Point(x, y)) = map_col;
			}
		}


		int height = 480;

		double resize_factor = static_cast<double>(height) / img.rows;
		int new_width = static_cast<int>(resize_factor * img.cols);

		cv::resize(img, img, cv::Size(new_width, height), CV_INTER_NN);

		cv::cvtColor(img, img, CV_GRAY2BGR);

		size_t num_vertical_lines = 1;
		size_t num_horizontal_lines = 1;

		for (size_t i = 1; i <= num_vertical_lines; i++) 
			draw_vertical_line(img, static_cast<double>(i)/(num_vertical_lines+1.0));
		
		for (size_t i = 1; i <= num_horizontal_lines; i++)
			draw_horizontal_line(img, static_cast<double>(i) / (num_horizontal_lines + 1.0));

		cv::imshow(name, img);cv::waitKey(100);


		if (close_all_windows) {
			cv::waitKey(0);
			cv::destroyAllWindows();
		}
		
	}
};