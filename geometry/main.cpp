#include <iostream>
#include "Point3.h"
#include "Polygon.h"
#include "PolygonMask.h"
#include "PointN.h"
#include "Rectangle.h"
#include <initializer_list>
#include <algorithm>
#include <vector>


int main()
{

	try
	{
		typedef double component_t;
		typedef PointN<component_t, 2> point_t;

		Polygon<component_t, 2> poly2{
			{0.0, 0.0},
			{10.0, 0.0},
			{10.0, 10.0},
			{0.0, 10.0}
		};

		PolygonMask<PointN, component_t, 2, component_t> pm(poly2, 0.1);



		//next we need to be able to create a binary representation of the 

		//start
		//specify n1 of polygons
		//call a function that returns n2 polygons, representing the interpolation results
		//done

		//start
		//specify 2 polygons
		//call a function that interpolates between two polygons - returns a third polygon
		//done

		return 0;

	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception Occurred. Message: " << e.what() << std::endl;
		return -1;
	}
}
