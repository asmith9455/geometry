#include <iostream>
#include <PolygonMaskInterpolator.h>
#include <Polygon_Interpolation_Testing.h>
//#include <GuiInterface.h>

using polygon_mask_t = typename polygon_interpolation_testing::polygon_mask_t;
using interp_matrix_component_t = int;
using weight_t = int;
using bool_t = uchar;
using dist_map_component_t = int;
using poly_mask_interp_t = PolygonMaskInterpolator<polygon_mask_t, weight_t, dist_map_component_t>;
using interp_result_t = typename poly_mask_interp_t::result_mat_t;

int main()
{
	//get some test polygons
	auto poly_pair = polygon_interpolation_testing::get_test_polygon(3);
	auto poly2 = poly_pair.first, poly3 = poly_pair.second;

	//set the resolution
	double resolution = 0.05;

	polygon_mask_t pm(poly2, resolution), pm2(poly3, resolution), pm1_matched, pm2_matched;

	poly_mask_interp_t pmi;

	pmi.get_matched_poly_masks(pm, pm2, pm1_matched, pm2_matched);

	std::vector<interp_result_t> results;
	std::vector<std::string> names;

	size_t num_interps = 1;


	for (size_t i = 1; i <= num_interps; ++i) {

		int
			weight_2 = static_cast<int>(i), 
			weight_1 = static_cast<int>(num_interps - i + 1);

		std::cout << "normalized weight 1: " << static_cast<double>(weight_1) / (weight_1 + weight_2) << std::endl;
		std::cout << "weight 1 : weight 2: " << weight_1 << " : " << weight_2 << std::endl;
		std::cout << "normalized weight 2: " << static_cast<double>(weight_2) / (weight_1 + weight_2) << std::endl << std::endl;

		results.push_back(pmi.interpolate_via_matched_masks(pm1_matched, pm2_matched, weight_1, weight_2));
		names.push_back("result" + std::to_string(i));
	
	}


	GuiInterface::show_images_animation<bool_t, polygon_mask_t>(names, results, pm1_matched, pm2_matched, true);

	return 0;
}
