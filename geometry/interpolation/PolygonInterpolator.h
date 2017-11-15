#pragma once
#include "Polygon.h"

template<class component_t, size_t polygon_dimension>
class PolygonInterpolator
{
	typedef Polygon<component_t, polygon_dimension> polygon_t;

	polygon_t m_p1, m_p2;

public:
	PolygonInterpolator() {}

	void set_polygons(polygon_t p1, polygon_t p2) {
		m_p1 = p1;
		m_p2 = p2;
	}

	void generate_interpolation(){
		//create a binary mask for p1
		//create a binary mask for p2
		//use the binarymaskinterpolator

	}
};