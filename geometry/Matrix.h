#pragma once

#include <vector>
#include <numeric>
#include <algorithm>

template<class T>
class Matrix
{
	typedef std::vector<T> column;
	typedef std::vector<column> matrix;

	size_t m_width, m_height;

	matrix m_mask;

public:

	Matrix(){}

	Matrix(size_t num_rows, size_t num_cols, T init_value)	{
		m_mask= matrix(num_cols, column(num_rows, init_value));
		m_width = num_cols;
		m_height = num_rows;
	}

	T& operator()(size_t row, size_t col) {
		 return m_mask[col][row];
	}

	T operator()(size_t row, size_t col) const {
		return m_mask[col][row];
	}

	Matrix<T> operator+(const Matrix<T>& m) {
		auto m_cpy = *this;
		m_cpy.add(m);
		return m_cpy;
	}

	void add(T to_add) {
		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {
				m_mask[col][row] += to_add;
			}
		}
	}

	void add(const Matrix<T>& to_add) {
		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {
				m_mask[col][row] += to_add(row, col);
			}
		}
	}

	void subtract(T to_subtract) {
		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {
				m_mask[col][row] -= to_subtract;
			}
		}
	}

	void or(const Matrix<T>& mat) {
		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {
				m_mask[col][row] = m_mask[col][row] | mat(row, col);
			}
		}
	}

	template<class scalar_t>
	void multiply_scalar(scalar_t scalar) {
		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {
				m_mask[col][row] *= static_cast<T>(scalar);
			}
		}
	}

	void multiply_double(double to_multiply) {
		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {
				m_mask[col][row] = static_cast<int>(static_cast<double>(m_mask[col][row]) * to_multiply);
			}
		}
	}

	void set_all(T value) {
		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {
				m_mask[col][row] = value;
			}
		}
	}

	template<class bool_t>
	Matrix<bool_t> filter_gte(T value) {

		auto mask = Matrix<bool_t>(height(), width(), 0);

		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {

				if (m_mask[col][row] >= value) {
					mask(row, col) = 1;
				}
			}
		}

		return mask;
	}

	template<class bool_t>
	Matrix<bool_t> filter_lte(T value) {

		auto mask = Matrix<bool_t>(height(), width(), 0);

		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {

				if (m_mask[col][row] <= value) {
					mask(row, col) = 1;
				}
			}
		}

		return mask;
	}

	//count of non-zero elements
	size_t area() {

		size_t a = 0;

		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {

				if (m_mask[col][row]) {
					a++;
				}
			}
		}

		return a;
	}

	std::vector<T> unique_values() {

		std::vector<T> uvals;
		
		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {
				T value = m_mask[col][row];
				if (std::find(uvals.begin(), uvals.end(), value) == uvals.end()) {
					uvals.push_back(value);
				}
			}
		}

		std::sort(uvals.begin(), uvals.end());

		return uvals;

	}

	T max() {
		T max_value = std::numeric_limits<T>::min();
		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {

				if (m_mask[col][row] > max_value) {
					max_value = m_mask[col][row];
				}
			}
		}

		return max_value;
	}

	T min() {
		T min_value = std::numeric_limits<T>::max();
		for (size_t row = 0; row != height(); row++) {
			for (size_t col = 0; col != width(); col++) {

				if (m_mask[col][row] < min_value) {
					min_value = m_mask[col][row];
				}
			}
		}

		return min_value;
	}

	size_t width() {
		return m_width;
	}

	size_t height() {
		return m_height;
	}
};

