#pragma once
#include "interpolation/polygon_mask_interpolator.h"
#include "interpolation/polygon_interpolation_testing.h"


namespace geometry {

	namespace examples {

		using namespace geometry::interpolation::polygon_interpolation_testing;	//need to fix this naming
		using interp_matrix_component_t = int;
		using weight_t = int;
		using bool_t = uchar;
		using dist_map_component_t = int;
		using poly_mask_interp_t = geometry::interpolation::polygon_mask_interpolator<polygon_mask_t, weight_t, dist_map_component_t>;
		using interp_result_t = typename poly_mask_interp_t::result_mat_t;

		void test_polygon_mask_interp();

	}
}