#include "Polygon3D.h"

Polygon3D::Polygon3D()
{

}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
}

Polygon3D::~Polygon3D()
{

}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	_indices[0] = p.GetIndex(0);
	_indices[1] = p.GetIndex(1);
	_indices[2] = p.GetIndex(2);
}

//RETURNS INDEX//
int Polygon3D::GetIndex(int x) const
{
	return _indices[x];
}



Polygon3D& Polygon3D::operator= (const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		_indices[0] = rhs.GetIndex(0);
		_indices[1] = rhs.GetIndex(1);
		_indices[2] = rhs.GetIndex(2);
	}
	return *this;
}

