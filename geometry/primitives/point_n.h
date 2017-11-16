#pragma once
#include <ostream>

namespace geometry {

	namespace primitives {

		template <class TComponent, size_t Dimension>
		class point_n
		{
		public:

			using component_t = TComponent;

			static const auto dimension = Dimension;

		private:

			static_assert(dimension == 3 || dimension == 2, "point_n must have dimension 2 or 3.");

			component_t m_components[dimension];

		public:



			point_n(component_t x, component_t y) {
				set_components(x, y);
			}
			point_n() {}


			point_n(component_t x, component_t y, component_t z) {
				set_components(x, y, z);
			}

			void set_components(component_t x, component_t y) {
				static_assert(dimension == 2, "This function is valid for dimension 2 points only");
				m_components[0] = x;
				m_components[1] = y;
			}

			void set_components(component_t x, component_t y, component_t z) {
				static_assert(dimension == 3, "This function is valid for dimension 3 points only");
				m_components[0] = x;
				m_components[1] = y;
				m_components[2] = z;
			}

			component_t x() {
				return m_components[0];
			}

			component_t y() {
				return m_components[1];
			}

			component_t z() {
				static_assert(dimension == 3, "Z component is only avaliable for points of dimension 3.");
				return m_components[2];
			}

			static bool x_less_than(point_n& p1, point_n& p2)
			{
				return p1.x() < p2.x();
			}

			static bool y_less_than(point_n& p1, point_n& p2)
			{
				return p1.y() < p2.y();
			}

			template <typename U, size_t D>
			friend std::ostream& operator<<(std::ostream& os, const point_n<U, D>& p);

		};

		template <typename TComponent, size_t Dimension>
		std::ostream& operator<<(std::ostream& os, const point_n<TComponent, Dimension>& p) {
			
			os << "point_" << Dimension;
			os << "{ x = " << p.m_components[0];
			os <<  " y = " << p.m_components[1];
			os << " } ";

			return os;
		}

		/*
		template <class ComponentT>
		inline bool operator==(const point_n<ComponentT>& lhs, const point_n<ComponentT>& rhs)
		{
			return	lhs.components[0] == rhs.components[0] &&
				lhs.components[1] == rhs.components[1] &&
				lhs.components[2] == rhs.components[2];
		}


		//define the hash function for Point3
		namespace std
		{
			template <class ComponentT>
			struct hash<Point3<ComponentT>>
			{
				size_t operator()(Point3<ComponentT> const & p) const noexcept
				{
					//Use extremely large primes to reduce the number of collisions that occur in
					//hash maps with a large number of points (as keys).
					return (
						(10007 + std::hash<ComponentT>()(p.components[0])) * 99991
						+ std::hash<ComponentT>()(p.components[1])
						);
				}
			};
		}*/

	}
}