#pragma once
template<class Y, int x>
class X {
	
	static_assert(x == 1, "x must be 1");

	const int m_const_x = x;

	Y m_ymem;
	int m_x = x;
	int y = 0;
public:
	X() {}
	X(int blah, Y ymem) : y(blah), m_ymem(ymem) {}
};