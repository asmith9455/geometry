#pragma once
#include <initializer_list>

template <class component_t, int dimension>
class PointN
{
private:

	const int m_dimension = dimension;

	component_t m_components[m_dimension] = {};

public:

	PointN() {}

	PointN(std::initializer_list<component_t> component_list) {
		this->set_components(component_list);
	}

	void setComponents(std::initializer_list<component_t> component_list) {
		
		assert(component_list.size() == m_dimension);

		int i = 0;
		for (component_t& c : component_list) {
			components[i] = c;
			i++;
		}
	}




};

/*
template <class ComponentT>
inline bool operator==(const PointN<ComponentT>& lhs, const PointN<ComponentT>& rhs)
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