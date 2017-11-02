#pragma once
#include <vector>
#include <initializer_list>
#include <stdexcept>

template<	template<class component_t> class point_t, class component_t>
//template < class point_t>
class Polygon {

	typedef point_t<component_t> point_tt;
	typedef std::vector<point_tt> points_t;


	points_t m_points;

public:
	Polygon(points_t points): m_points(points) {}
	Polygon() {}
	Polygon(std::initializer_list<point_tt> points)
	{
		for (auto p : points)
			m_points.push_back(p);
	}

	bool empty() {
		return m_points.size() == 0;
	}

	void add_point(point_tt pnt) {
		m_points.push_back(pnt);
	}

	point_tt get_lower_left_point()
	{
		assert(this->empty());

		component_t min_x, min_y;
		for(point_tt p : m_points)

	}

	point_tt get_upper_right_point()
	{

	}


};