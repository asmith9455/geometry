#pragma once

#include <string>

#include "primitives/matrix.h"
#include "primitives/polygon.h"
#include "primitives/rectangle.h"
#include "gui/gui_interface.h"


namespace geometry {

	namespace primitives {


		template<class TPolygon, class TResolution, class TBool >
		class polygon_mask {

		public:

			using bool_t = TBool;
			using poly_t = TPolygon;
			using resolution_t = TResolution;
			using point_t = typename poly_t::point_t;
			using component_t = typename poly_t::component_t;
			using rectangle_t = rectangle <component_t>;
			using matrix_component_t = bool_t;				//just has to hold 0 or 1, and std vector used in Matrix<T> doesn't play well with bool
			using matrix_t1 = matrix<matrix_component_t>;

			static const auto dimension = poly_t::dimension;

		private:

			resolution_t m_resolution;
			matrix_t1 m_matrix;
			rectangle_t m_bounding_rectangle;
			poly_t m_polygon;

			void allocate_memory() {

				size_t number_of_columns = static_cast<size_t>(m_bounding_rectangle.width() / m_resolution) + 1;
				size_t number_of_rows = static_cast<size_t>(m_bounding_rectangle.height() / m_resolution) + 1;

				m_matrix = matrix_t1(number_of_rows, number_of_columns, false);// mask_category::undeclared);

				for (size_t row = 0; row != number_of_rows; row++) {
					for (size_t col = 0; col != number_of_columns; col++) {

						size_t adjusted_row_index = number_of_rows - 1 - row;

						point_t point = point_t(
							static_cast<component_t>(col*m_resolution) + m_bounding_rectangle.get_lower_left_point().x(),
							static_cast<component_t>(adjusted_row_index*m_resolution) + m_bounding_rectangle.get_lower_left_point().y()
						);

						bool_t val = m_polygon.contains_xy(point) * std::numeric_limits<bool_t>::max();;
						m_matrix(adjusted_row_index, col) = val;


					}
				}
			}

		public:

			polygon_mask() {}

			polygon_mask(poly_t p, resolution_t resolution) {

				//first find the x and y distances
				assert(!p.empty());

				m_bounding_rectangle = p.get_bounding_box();
				m_polygon = p;
				m_resolution = resolution;

				allocate_memory();

			}

			polygon_mask(poly_t p, resolution_t resolution, rectangle_t bounding_box) {

				//first find the x and y distances
				assert(!p.empty());

				m_resolution = resolution;
				m_polygon = p;
				m_bounding_rectangle = bounding_box;

				allocate_memory();

			}

			/*void add(const PolygonMask& pm) {
				m_matrix.add(pm.m_matrix);
			}*/

			size_t width() {
				return m_matrix.width();
			}

			size_t height() {
				return m_matrix.height();
			}

			polygon_mask match_size_to(polygon_mask pm) {
				//must have the same size for each
				component_t x_min = std::min(
					m_bounding_rectangle.get_lower_left_point().x(),
					pm.m_bounding_rectangle.get_lower_left_point().x()
				);

				component_t y_min = std::min(
					m_bounding_rectangle.get_lower_left_point().y(),
					pm.m_bounding_rectangle.get_lower_left_point().y()
				);

				component_t x_max = std::max(
					m_bounding_rectangle.get_upper_right_point().x(),
					pm.m_bounding_rectangle.get_upper_right_point().x()
				);

				component_t y_max = std::max(
					m_bounding_rectangle.get_upper_right_point().y(),
					pm.m_bounding_rectangle.get_upper_right_point().y()
				);

				rectangle_t new_bounding_box({ {x_min, y_min}, {x_max, y_max} });

				auto new_pm = polygon_mask(m_polygon, m_resolution, new_bounding_box);

				return new_pm;
			}

			matrix<bool_t>& get_data_matrix() {
				return m_matrix;
			}

			//count of non-zero elements
			size_t area() {
				return m_matrix.area();
			}

			polygon_mask operator*=(matrix_component_t scalar) {
				m_matrix.multiply_scalar(scalar);
			}

			void show(std::string name, bool close_all = false) {
				geometry::gui::matrix_graphics_functions::show_image<uchar>(name, get_data_matrix(), close_all);
			}

			/*BinaryMask(BinaryMask mask1, BinaryMask mask2) {

			}*/
		};

	}
}