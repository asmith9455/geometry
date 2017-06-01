#pragma once


template <class ComponentT>
class Point3
{
protected:
	

public:

	ComponentT components[3];

	Point3() {}
	Point3(ComponentT _c1, ComponentT _c2, ComponentT _c3)
	{
		setComponents(_c1, _c2, _c3);
	}
	void setComponents(ComponentT _c1, ComponentT _c2, ComponentT _c3)
	{
		components[0] = _c1;
		components[1] = _c2;
		components[2] = _c3;
	}

	

	
};
template <class ComponentT>
inline bool operator==(const Point3<ComponentT>& lhs, const Point3<ComponentT>& rhs)
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
			return (
				(51 + std::hash<ComponentT>()(p.components[0])) * 51
				+ std::hash<ComponentT>()(p.components[1])
				);
		}
	};
}