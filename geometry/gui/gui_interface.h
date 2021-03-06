#pragma once

#include <string>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "primitives/matrix.h"
#include "primitives/polygon_mask.h"

namespace geometry {

	namespace gui {

		using namespace geometry::primitives;

		class matrix_graphics_functions {

		public:

			matrix_graphics_functions() {}

			//PolygonMask<point_n, component_t, 2, component_t> pm
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
			static void show_images(std::vector<std::string> names, std::vector<matrix<T>> mats, bool close_all_windows = false) {

				auto name = names.begin();
				auto mat = mats.begin();

				for (;
					name != names.end() && mat != mats.end();
					name++, mat++)
					show_image<T>(*name, *mat, false);

				if (close_all_windows) {
					cv::waitKey(0);
					cv::destroyAllWindows();
				}

			}

			template<class T, class TPolygonMask>
			static void show_images_animation(std::vector<std::string> names, std::vector<matrix<T>> mats, TPolygonMask pm1_extended, TPolygonMask pm2_extended, bool close_all_windows = false) {

				auto name = names.begin();
				auto mat = mats.begin();

				std::vector<cv::Mat> imgs;

				imgs.push_back(get_cv_img_from_matrix(pm1_extended.get_data_matrix()));

				for (;
					name != names.end() && mat != mats.end();
					++name, ++mat)
				{
					imgs.push_back(get_cv_img_from_matrix(*mat));
					//show_image<T>(*name, *mat);
				}

				imgs.push_back(get_cv_img_from_matrix(pm2_extended.get_data_matrix()));

				//cyle through the images from first to last, then back again from last to first.

				auto img_it = imgs.begin();
				auto r_img_it = imgs.rbegin();
				bool going_forwards = true;

				while ((cv::waitKey(100) & 0xEFFFFF) != 27) {

					if (going_forwards)
						cv::imshow("animation", *img_it);
					else
						cv::imshow("animation", *r_img_it);

					if (going_forwards && (++img_it == imgs.end())) {
						img_it = imgs.begin();
						going_forwards = false;
						cv::waitKey(150);
					}
					else if (!going_forwards && (++r_img_it == imgs.rend())) {
						r_img_it = imgs.rbegin();
						going_forwards = true;
						cv::waitKey(150);
					}

				}


				cv::destroyAllWindows();

			}

			template<class T>
			static cv::Mat get_cv_img_from_matrix(matrix<T> m) {

				{ //UNCOMMENT TO DISPLAY EACH ITERATION
					int tmp_min = m.min();
					int tmp_max = m.max();

					/*std::cout << "---------------------------------------------------" << std::endl;
					std::cout << "Name is: " << name << std::endl;
					std::cout << "Original Min -> Max: " << tmp_min << " -> " << tmp_max << std::endl;*/

					m.subtract(tmp_min);
					double factor = 250.0 / static_cast<double>(tmp_max - tmp_min);
					m.multiply_double(factor);

					/*std::cout << "Adjusted Min -> Max: " << m.min() << " -> " << m.max() << std::endl;

					std::cout << "dimension: " << m.width() << " x " << m.height() << std::endl;

					std::cout << "---------------------------------------------------" << std::endl;*/
				}

				cv::Mat img = cv::Mat(static_cast<int>(m.height()), static_cast<int>(m.width()), CV_8U);

				for (int y = 0; y < img.rows; y++)
				{
					for (int x = 0; x < img.cols; x++)
					{
						int adjusted_y = img.rows - 1 - y;

						// get pixel
						//Vec3b color = image.at<Vec3b>(Point(x, y));

						uchar map_col = m(adjusted_y, x);

						// set pixel
						img.at<uchar>(cv::Point(x, y)) = map_col;
					}
				}

				int height = 360;

				double resize_factor = static_cast<double>(height) / img.rows;
				int new_width = static_cast<int>(resize_factor * img.cols);

				cv::resize(img, img, cv::Size(new_width, height), CV_INTER_NN);

				cv::cvtColor(img, img, CV_GRAY2BGR);

				size_t num_vertical_lines = 1;
				size_t num_horizontal_lines = 1;

				for (size_t i = 1; i <= num_vertical_lines; i++)
					draw_vertical_line(img, static_cast<double>(i) / (num_vertical_lines + 1.0));

				for (size_t i = 1; i <= num_horizontal_lines; i++)
					draw_horizontal_line(img, static_cast<double>(i) / (num_horizontal_lines + 1.0));





				return img;
			}

			template<class T>
			static void show_image(std::string name, matrix<T> m, bool close_all_windows = false) {

				cv::Mat img = get_cv_img_from_matrix(m);

				cv::imshow(name, img); cv::waitKey(100);


				if (close_all_windows) {
					cv::waitKey(0);
					cv::destroyAllWindows();
				}

			}
		};


	}
}