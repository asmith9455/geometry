#pragma once
#include <PolygonMask.h>
#include <iostream>
#include <Matrix.h>
#include <GuiInterface.h>

template <class polygon_mask_t, class matrix_component_t, class weight_t, class bool_t>
class PolygonMaskInterpolator {

	typedef Matrix<bool_t> result_mat_t;
	typedef Matrix<matrix_component_t> dist_mat_t;

	//assign +1's and -1's to all matrix elements on the edges of the binary mask
	void process_step_1(Matrix<uchar>& m_matrix, Matrix<int>& interp_mat, size_t& made_1, size_t& made_n1) {


		//process initial -1's and +1's - rest of the algo relies on zeros as elements to be assigned values
		for (size_t row = 1; row != interp_mat.height() - 1; row++) {
			for (size_t col = 1; col != interp_mat.width() - 1; col++) {
				int v_C = m_matrix(row, col),
					v_L = m_matrix(row, col - 1),
					v_R = m_matrix(row, col + 1),
					v_T = m_matrix(row + 1, col),
					v_B = m_matrix(row - 1, col);

				if (v_C != v_L || v_C != v_R || v_C != v_T || v_C != v_B) {
					if (v_C) {
						//std::cout << "made " << row << ", " << col << " -1" << std::endl;
						interp_mat(row, col) = -1;
						made_n1++;
					}
					else {
						//std::cout << "made " << row << ", " << col << " +1" << std::endl;
						interp_mat(row, col) = 1;
						made_1++;
					}
				}

			}
		}


	}

	//assign -1's to any points on the boundary (these will not be caught by step 1)
	void process_step_2(Matrix<uchar>& m_matrix, Matrix<int>& interp_mat, size_t& made_1, size_t& made_n1) {


		//go along the upper and lower row
		for (size_t row = 0; row <= interp_mat.height() - 1; row += interp_mat.height() - 1) {
			for (size_t col = 1; col != interp_mat.width() - 1; col++) {
				if (m_matrix(row, col)) {
					interp_mat(row, col) = -1;
					made_n1++;
				}

			}
		}

		//left and right columns
		for (size_t col = 0; col <= interp_mat.width() - 1; col += interp_mat.width() - 1) {
			for (size_t row = 0; row != interp_mat.height(); row++) {
				if (m_matrix(row, col)) {
					interp_mat(row, col) = -1;
					made_n1++;
				}

			}
		}

	}

	//iteratively compute the distance map for the nominal points
	void process_step_3(Matrix<uchar>& m_matrix, Matrix<int>& interp_mat, size_t& modified_from_zero_inside, size_t& modified_from_zero_outside, int& max_value, int& min_value) {

		bool found_zero_element = true;
		auto intermediate_mat = Matrix<int>(m_matrix.height(), m_matrix.width(), 0);	//changes are applied here and then or'ed with the interp mat later
		size_t num_iterations = 0;

		while (found_zero_element) {

			found_zero_element = false;

			for (size_t row = 1; row != interp_mat.height() - 1; row++) {
				for (size_t col = 1; col != interp_mat.width() - 1; col++) {
					int v_C = interp_mat(row, col),
						v_L = interp_mat(row, col - 1),
						v_R = interp_mat(row, col + 1),
						v_T = interp_mat(row + 1, col),
						v_B = interp_mat(row - 1, col);



					int value_array[4];

					if (v_C == 0 && (v_L != 0 || v_R != 0 || v_T != 0 || v_B != 0)) {
						int val;
						found_zero_element = true;

						value_array[0] = v_L;
						value_array[1] = v_R;
						value_array[2] = v_T;
						value_array[3] = v_B;

						std::sort(&value_array[0], &value_array[4]);

						bool is_in = m_matrix(row, col);

						if (is_in) {
							val = value_array[0] - 1;
							modified_from_zero_inside++;
						}
						else {
							val = value_array[3] + 1;
							modified_from_zero_outside++;
						}

						if (val > max_value)
							max_value = val;

						if (val < min_value)
							min_value = val;

						intermediate_mat(row, col) = val;

					}

				}

			}

			interp_mat. or (intermediate_mat);

			intermediate_mat.set_all(0);

			num_iterations++;


			/*{ UNCOMMENT TO DISPLAY EACH ITERATION
			int tmp_min = interp_mat.min();
			int tmp_max = interp_mat.max();

			auto interp_copy = interp_mat;

			interp_copy.subtract(tmp_min);
			double factor = 250.0 / static_cast<double>(tmp_max - tmp_min);
			interp_copy.multiply_double(factor);

			GuiInterface::show_image<int>("interp poly tmp", interp_copy);

			cv::waitKey(100);
			}

			if (num_iterations == iterations_limit)
			break;*/

		}
	}

	//finish the last parts of the 
	void process_step_4(Matrix<uchar>& m_matrix, Matrix<int>& interp_mat, size_t& modified_from_zero_inside, size_t& modified_from_zero_outside) {
		//go along the LOWER row
		for (size_t col = 1; col != interp_mat.width() - 1; col++) {

			if (interp_mat(0, col) != 0)
				continue;

			auto val = interp_mat(1, col);
			if (val < 0) {
				interp_mat(0, col) = val - 1;
				modified_from_zero_inside++;
			}
			else if (val > 0) {
				interp_mat(0, col) = val + 1;
				modified_from_zero_outside++;
			}

		}

		//go along the UPPER row
		for (size_t col = 1; col != interp_mat.width() - 1; col++) {

			if (interp_mat(interp_mat.height() - 1, col) != 0)
				continue;

			auto val = interp_mat(interp_mat.height() - 2, col);
			if (val < 0) {
				interp_mat(interp_mat.height() - 1, col) = val - 1;
				modified_from_zero_inside++;
			}
			else if (val > 0) {
				interp_mat(interp_mat.height() - 1, col) = val + 1;
				modified_from_zero_outside++;
			}

		}


		//left column
		for (size_t row = 0; row != interp_mat.height(); row++) {

			if (interp_mat(row, 0) != 0)
				continue;

			auto val = interp_mat(row, 1);

			if (val < 0) {
				interp_mat(row, 0) = val - 1;
				modified_from_zero_inside++;
			}
			else if (val > 0) {
				interp_mat(row, 0) = val + 1;
				modified_from_zero_outside++;
			}

		}

		//right column
		for (size_t row = 0; row != interp_mat.height(); row++) {

			if (interp_mat(row, interp_mat.width() - 1) != 0)
				continue;

			auto val = interp_mat(row, interp_mat.width() - 2);

			if (val < 0) {
				interp_mat(row, interp_mat.width() - 1) = val - 1;
				modified_from_zero_inside++;
			}
			else if (val > 0) {
				interp_mat(row, interp_mat.width() - 1) = val + 1;
				modified_from_zero_outside++;
			}

		}
	}

	void print_stats(dist_mat_t& interp_mat, size_t& made_1, size_t& made_n1, size_t& modified_from_zero_inside, size_t& modified_from_zero_outside, int& min_value, int& max_value, size_t& total_num_to_change) {
		interp_mat.subtract(min_value);
		double factor = 250.0 / static_cast<double>(max_value - min_value);
		interp_mat.multiply_double(factor);

		std::cout << "-------------------------------------------------" << std::endl;
		std::cout << "Number made +1: " << made_1 << std::endl;
		std::cout << "Number made -1: " << made_n1 << std::endl;

		std::cout << "Processing Step : " << std::endl;
		std::cout << "Number assigned outside: " << modified_from_zero_outside << std::endl;
		std::cout << "Number number assigned inside: " << modified_from_zero_inside << std::endl;
		std::cout << "Total to Process: " << total_num_to_change << std::endl;

		std::cout << "Totals Match? ";
		if (total_num_to_change == (made_1 + made_n1 + modified_from_zero_inside + modified_from_zero_outside))
		std::cout << "Yes";
		else
		std::cout << "No";
		std::cout << std::endl;

		std::cout << "Value Information: " << std::endl;
		std::cout << "Original Min -> Max: " << min_value << " -> " << max_value << std::endl;
		std::cout << "Adjusted Pre Factor Range Min -> Max: " << min_value - min_value << " -> " << max_value - min_value << std::endl;
		std::cout << "factor used to adjust: " << factor << std::endl;

		std::cout << "Adjusted Post Factor New Min -> Max: " << interp_mat.min() << " -> " << interp_mat.max() << std::endl;

		std::cout << "-------------------------------------------------" << std::endl;
	}

	//compute the distance map
	dist_mat_t get_distance_map(polygon_mask_t& pm) {

		auto& m_matrix = pm.get_data_matrix();

		auto interp_mat = dist_mat_t(m_matrix.height(), m_matrix.width(), 0);
		

		//need to add some handling of the sizes here

		//bool do_boundary = true, do_area = true, do_final_edges = true;

		size_t iterations_limit = 100;

		size_t made_1 = 0, made_n1 = 0, modified_from_zero_inside = 0, modified_from_zero_outside = 0,
			total_num_to_change = m_matrix.height() * m_matrix.width();

		int min_value = 0, max_value = 0;

		process_step_1(m_matrix, interp_mat, made_1, made_n1);
		
		process_step_2(m_matrix, interp_mat, made_1, made_n1);

		if (made_1 > 0)
			max_value = 1;
		if (made_n1 > 0)
			min_value = -1;

		process_step_3(m_matrix, interp_mat, modified_from_zero_inside, modified_from_zero_outside, max_value, min_value);
		process_step_4(m_matrix, interp_mat, modified_from_zero_inside, modified_from_zero_outside);
		
		print_stats(interp_mat, made_1, made_n1, modified_from_zero_inside, modified_from_zero_outside, min_value, max_value, total_num_to_change);

		return interp_mat;
	}

	//filter the summed distance map
	result_mat_t get_bool_mat(dist_mat_t& dm, size_t area1, size_t area2) {
		//sorted least to greatest
		auto uvals = dm.unique_values();

		auto avg_area = (area1 + area2) / 2;
		
		result_mat_t result;

		for (auto thres : uvals) {
			result = dm.filter_lte<bool_t>(thres);
			
			auto area = result.area();

			if (area > avg_area)
				break;
			
		}
		
		return result;
	}

	public:
	PolygonMaskInterpolator() {}

	result_mat_t interpolate(polygon_mask_t& pm1, polygon_mask_t& pm2, weight_t pm1_weight = 1.0, weight_t pm2_weight = 1.0) {

		//extend each polygon mask to match the other in size
		auto pm1_matched = pm1.match_size_to(pm2),
			pm2_matched = pm2.match_size_to(pm1);

		//first calculate the distance maps for each
		auto dm1 = get_distance_map(pm1_matched),
			dm2 = get_distance_map(pm2_matched);

		//change interpolation weights
		dm1.multiply_scalar<weight_t>(pm1_weight);
		dm2.multiply_scalar<weight_t>(pm2_weight);

		auto interp_result = dm1 + dm2;

		//("interp poly 1", interp_mat1);
		//GuiInterface::show_image<int>("interp poly 2", interp_mat2);

		pm1_matched.show("poly 1");
		pm2_matched.show("poly 2");
		GuiInterface::show_image<int>("sum of distance maps", interp_result);

		//GuiInterface::show_image();

		auto filtered_result = get_bool_mat(interp_result, pm1.area(), pm2.area());

		return filtered_result;

	}


};