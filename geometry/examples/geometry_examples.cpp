#include "examples/geometry_examples.h"

namespace geometry {

	namespace examples {

		void geometry::examples::test_polygon_mask_interp() {
			//get some test polygons

			auto poly_pair = get_test_polygon(3);
			auto poly2 = poly_pair.first, poly3 = poly_pair.second;

			//set the resolution
			double resolution = 0.04;

			polygon_mask_t pm1(poly2, resolution), pm2(poly3, resolution);

			poly_mask_interp_t pmi;

			auto pair = pmi.interpolate_multi(pm1, pm2, 10);
			auto results = pair.first;
			auto names = pair.second;
		}

	}
}
