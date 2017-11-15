#include "interpolation/polygon_interpolation_testing.h"

namespace geometry {

	namespace interpolation {

		namespace polygon_interpolation_testing {

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
	}
}