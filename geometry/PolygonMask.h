#pragma once
#include "Matrix.h"
#include "Polygon.h"
#include "Rectangle.h"

template<template <class component_t, size_t dimension> class point_t, class component_t, size_t dimension, class resolution_t>
class PolygonMask {

	enum mask_category {
		inside,
		outside,
		boundary,
		undeclared
	};

	typedef Polygon<component_t, dimension> poly_t;
	typedef Rectangle<component_t> rectangle_t;
	typedef Matrix<bool> matrix_t1;
	typedef Matrix<component_t> matrix_t2;
	typedef point_t<component_t, dimension> point_tt;

	resolution_t m_resolution;
	matrix_t1 m_matrix;
	matrix_t2 m_coordinates;
	point_t<component_t, dimension> m_lower_left_corner;
	

public:

	PolygonMask(poly_t p, resolution_t resolution) {
		
		//first find the x and y distances
		assert(!p.empty());

		m_resolution = resolution;

		rectangle_t r = p.get_bounding_box();

		m_lower_left_corner = r.get_lower_left_point();

		size_t number_of_columns = static_cast<size_t>(r.width() / m_resolution) + 1;
		size_t number_of_rows = static_cast<size_t>(r.height() / m_resolution) + 1;

		m_matrix = matrix_t1(number_of_rows, number_of_columns, mask_category::undeclared);

		point_tt default_point = point_tt(0.0, 0.0);

		m_coordinates = matrix_t2(number_of_rows, number_of_columns, default_point);

		//now need to fill in the parts of the mask - regions must be marked as inside, outside, and on the boundary

		for (size_t row = 0; row != number_of_rows; row++) {
			for (size_t col = 0; col != number_of_columns; col++) {

				size_t adjusted_row_index = number_of_rows - 1 - row;

				point_tt point = point_tt(
					static_cast<component_t>(col*m_resolution) + m_lower_left_corner.x(), 
					static_cast<component_t>(adjusted_row_index*m_resolution) + m_lower_left_corner.y()
				);

				m_matrix[adjusted_row_index][col] = p.contains_xy(point);



			}
		}

		
	}

	/*BinaryMask(BinaryMask mask1, BinaryMask mask2) {

	}*/
};