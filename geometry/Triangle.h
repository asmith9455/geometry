#pragma once
#include "Point3.h"

template<template<class ComponentT> class PointT, class ComponentT>
class Triangle
{
public:
	
	PointT<ComponentT> p1, p2, p3;

	Triangle()	{}
	Triangle(PointT<ComponentT> _p1, PointT<ComponentT> _p2, PointT<ComponentT> _p3)
	{
		setPoints(_p1, _p2, _p3);
	}

	void setPoints(PointT<ComponentT> _p1, PointT<ComponentT> _p2, PointT<ComponentT> _p3)
	{
		p1 = _p1;
		p2 = _p2;
		p3 = _p3;
	}

	
};