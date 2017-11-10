#pragma once
#include <vector>
#include "PointN.h"
#include <initializer_list>
#include "Rectangle.h"
#include <algorithm>
#include <assert.h>

template<class TPoint>
//template < class point_t>
class Polygon {

public:
	using point_t = TPoint;
	using component_t = typename point_t::component_t;
	
	static const auto dimension = point_t::dimension;

	static_assert(dimension == 2 || dimension == 3, "The dimension of the points in the polygon must be 2 or 3");

	using points_t = std::vector<point_t>;

private:
	points_t m_points;

public:

	Polygon(points_t points): m_points(points) {}
	
	Polygon() {}

	Polygon(std::initializer_list<point_t> points){
		for (auto p : points)
			m_points.push_back(p);
	}

	bool empty() {
		return m_points.size() == 0;
	}

	void add_point(point_t pnt) {
		m_points.push_back(pnt);
	}

	Rectangle<component_t> get_bounding_box()
	{
		assert(!empty());

		const component_t min_x = std::min_element(m_points.begin(), m_points.end(), point_t::x_less_than)->x();
		const component_t min_y = std::min_element(m_points.begin(), m_points.end(), point_t::y_less_than)->y();
		const component_t max_x = std::max_element(m_points.begin(), m_points.end(), point_t::x_less_than)->x();
		const component_t max_y = std::max_element(m_points.begin(), m_points.end(), point_t::y_less_than)->y();


		//return Rectangle<component_t>(lower_left, upper_right);
		return Rectangle<component_t>({ min_x, min_y }, { max_x, max_y });
	}

	bool contains_xy(point_t p){
		size_t windings = wn_PnPoly(p);

		if (windings == 0)
			return false;
		else
			return true;
	}

	size_t size() {
		return m_points.size();
	}

private:
	size_t wn_PnPoly(point_t p)
	{
		size_t wn = 0;    // the  winding number counter

					   // loop through all edges of the polygon
		for (size_t i = 0; i < this->size() - 1; i++)
		{   // edge from V[i] to  V[i+1]
			if (m_points[i].y() <= p.y())
			{          // start y <= P.y
				if (m_points[i + 1].y() > p.y())      // an upward crossing
					if (isLeft(m_points[i], m_points[i + 1], p) > 0)  // P left of  edge
						++wn;            // have  a valid up intersect
			}
			else
			{                        // start y > P.y (no test needed)
				if (m_points[i + 1].y() <= p.y())     // a downward crossing
					if (isLeft(m_points[i], m_points[i + 1], p) < 0)  // P right of  edge
						--wn;            // have  a valid down intersect
			}
		}
		return wn;
	}

	double isLeft(point_t P0, point_t P1, point_t P2)
	{
		return ((P1.x() - P0.x()) * (P2.y() - P0.y())
			- (P2.x() - P0.x()) * (P1.y() - P0.y()));
	}

};