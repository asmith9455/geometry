#include <iostream>
#include <PolygonMaskInterpolator.h>
#include <Polygon_Interpolation_Testing.h>
#include <GuiInterface.h>
#include <numeric>

typedef polygon_interpolation_testing::polygon_mask_t polygon_mask_t;
typedef int interp_matrix_component_t;
typedef int weight_t;
typedef uchar bool_t;

int main()
{
	//get some test polygons
	auto poly_pair = polygon_interpolation_testing::get_test_polygon(0);
	auto poly2 = poly_pair.first, poly3 = poly_pair.second;

	//set the resolution
	double resolution = 0.1;

	polygon_mask_t pm(poly2, resolution), pm2(poly3, resolution);

	PolygonMaskInterpolator<polygon_mask_t, interp_matrix_component_t, weight_t, bool_t> pmi;

	auto result = pmi.interpolate(pm, pm2, 1, 1);

	GuiInterface::show_image<bool_t>("interpolation result", result, true);

	return 0;
}
