#pragma once
#include "BinaryMask.h"

template<class point_t, class component_t>
class BinaryMaskInterpolator {

	BinaryMask m_bm1, m_bm2;

public:
	BinaryMaskInterpolator() {}

	void set_binary_masks(BinaryMask bm1, BinaryMask bm2) {
		m_bm1 = bm1;
		m_bm2 = bm2;
	}

	void generate_interpolation() {

		//create a binary mask for p1 that is the same size as p2
		//create a binary mask for p2 that is the same size as p1

		//create the distance map for each of the extended binary masks

		//filter the distance map until the new binary mask is generated

		//create a new binary mask that 
	}
};