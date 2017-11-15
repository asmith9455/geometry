#pragma once
#include "PointN.h"
#include "Polygon.h"
#include "PolygonMask.h"

namespace polygon_interpolation_testing
{
	using bool_t = uchar;
	using component_t = double;
	using point_t = PointN<component_t, 2>;
	

	using poly_t_2d = Polygon<point_t>;
	using polygon_mask_t = PolygonMask<poly_t_2d, component_t, bool_t>;

	std::pair<poly_t_2d, poly_t_2d> get_test_polygon(size_t index) {

		poly_t_2d p1, p2;

		switch (index) {

		case 0: {
			p1 = poly_t_2d{ { 10.0, 0.0 },{ 20.0, 0.0 },{ 20.0, 10.0 },{ 10.0, 0.0 } };
			p2 = poly_t_2d{ { 0.0, 0.0 },{ 10.0, 0.0 },{ 10.0, 10.0 },{ 0.0, 10.0 },{ 0.0, 0.0 } };
			break;
		}

		case 1: {
			p1 = poly_t_2d{ { 20.0, 20.0 },{ 30.0, 20.0 },{ 30.0, 30.0 },{ 20.0, 30.0 },{ 20.0, 20.0 } };
			p2 = poly_t_2d{ { 0.0, 0.0 },{ 10.0, 0.0 },{ 10.0, 10.0 },{ 0.0, 10.0 },{ 0.0, 0.0 } };
			break;
		}

		case 2: {
			p1 = poly_t_2d{ { 4.0, 4.0 },{ 6.0, 4.0 },{ 6.0, 6.0 },{ 4.0, 6.0 },{ 4.0, 4.0 } };
			p2 = poly_t_2d{ { 0.0, 0.0 },{ 10.0, 0.0 },{ 10.0, 10.0 },{ 0.0, 10.0 },{ 0.0, 0.0 } };
			break;
		}

		case 3: {
			p1 = poly_t_2d{ { 5.0, 5.0 },{ 15.0, 5.0 },{ 15.0, 15.0 },{ 5.0, 15.0 },{ 5.0, 5.0 } };
			p2 = poly_t_2d{ { 0.0, 0.0 },{ 10.0, 0.0 },{ 10.0, 10.0 },{ 0.0, 10.0 },{ 0.0, 0.0 } };
			break;
		}

		}


		return std::pair<poly_t_2d, poly_t_2d>(p1, p2);
	}

}