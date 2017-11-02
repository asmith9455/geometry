#pragma once

#include <vector>

template<class T>
class Matrix
{
	typedef std::vector<T> column;
	typedef std::vector<column> matrix;

	matrix m_mask;

public:

	Matrix(size_t num_rows, size_t num_cols, T init_value)	{
		m_mask= matrix(num_cols, column(num_rows, init_value));
	}
};

