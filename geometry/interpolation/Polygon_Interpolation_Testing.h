#pragma once
#include "primitives/point_n.h"
#include "primitives/polygon.h"
#include "primitives/polygon_mask.h"

namespace geometry {

	namespace interpolation {

		namespace polygon_interpolation_testing {

			using namespace geometry::primitives;
			using bool_t = uchar;
			using component_t = double;
			using point_t = point_n<component_t, 2>;

			using poly_t_2d = polygon<point_t>;
			using polygon_mask_t = polygon_mask<poly_t_2d, component_t, bool_t>;

			std::pair<poly_t_2d, poly_t_2d> get_test_polygon(size_t index);

		}
	}
}