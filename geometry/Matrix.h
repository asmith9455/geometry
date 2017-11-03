#pragma once

#include <vector>

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

	size_t width() {
		return m_width;
	}

	size_t height() {
		return m_height;
	}
};

