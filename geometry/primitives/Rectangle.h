#pragma once
#include "primitives/point_n.h"

namespace geometry {
	namespace primitives {


		template <class component_t>
		class rectangle {

			typedef point_n<component_t, 2> point_t;

			point_t m_lower_left_point; //The lower left point from the persepective of a person viewing a projection of the points onto cartesian grid with the +x pointing right and the +y pointing up;
			point_t m_upper_right_point; //The upper right point from the persepective of a person viewing a projection of the points onto cartesian grid with the +x pointing right and the +y pointing up;

		public:

			rectangle() {}

			//Rectangle& operator=(const Rectangle&) = default;

			rectangle<component_t>(point_t lower_left_point, point_t upper_right_point)
				: m_lower_left_point(lower_left_point),
				m_upper_right_point(upper_right_point)
			{}

			point_t get_lower_left_point() { return m_lower_left_point; }

			point_t get_upper_right_point() { return m_upper_right_point; }

			/*Rectangle(component_t lower_left_x, component_t lower_left_y, component_t upper_right_x, component_t upper_right_y) {
				m_lower_left_point = point_t( lower_left_x, lower_left_y );
				m_upper_right_point = point_t(upper_right_x, upper_right_y);
			}*/

			component_t width() {
				return m_upper_right_point.x() - m_lower_left_point.x();
			}

			component_t height() {
				return m_upper_right_point.y() - m_lower_left_point.y();
			}
		};

	}
}