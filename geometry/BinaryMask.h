#pragma once
#include "Matrix.h"
#include "Polygon.h"

template<class point_t, class component_t>
class BinaryMask {

	component_t m_resolution;
	Matrix<bool> m;

public:

	BinaryMask(Polygon<point_t> p, component_t resolution) {
		
		//first find the x and y distances


	}

	/*BinaryMask(BinaryMask mask1, BinaryMask mask2) {

	}*/
};