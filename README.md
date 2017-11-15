# geometry

This library implements some geometry related functions, and is a work in progress / learning project.

![demo.gif](/animations/animation_poly_test_002.gif)

A library that implements geometry-related functions. Check out some [animations](/animations/) and [pictures](pictures), which show some initial polygon interpolation results so far.

Current features:
* finds triangle connectivities in O(n) on average given a set of triangles (a learning project for templates in C++).
* produces a binary mask (called a polygon mask in geometry) given a simple polygon and a bounding box.

Currently working on "polygon interpolation", which attempts to generate a polygon that is a mix of the features of two separate polygons. This interpolation is currently not well defined.
