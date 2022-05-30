#include "Vertex.h"

Vertex::Vertex(void)
{
	Init(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(float x, float y, float z)
{
	Init(x, y, z);
}

Vertex::Vertex(const Vertex& v)
{
	Copy(v);
}

Vertex::Vertex(Vertex&& v) 
{
	Copy(v);
}

Vertex::~Vertex(void)
{
}

// Accessors and mutators

float Vertex::GetX(void) const
{
	return _x;
}

void Vertex::SetX(float x)
{
	_x = x;
}

float Vertex::GetY(void) const
{
	return _y;
}

void Vertex::SetY(float y)
{
	_y = y;
}

float Vertex::GetZ(void) const
{
	return _z;
}

void Vertex::SetZ(float z)
{
	_z = z;
}

float Vertex::GetW(void) const
{
	return _w;
}

void Vertex::SetW(float w)
{
	_w = w;
}

// Operator overloads

Vertex& Vertex::operator= (const Vertex& rhs) 
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

Vertex& Vertex::operator= (Vertex&& rhs) 
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}


// Private methods

void Vertex::Init(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1;
}

void Vertex::Copy(const Vertex& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_w = v.GetW();
}

//DEHOMOGENIZING A VECTOR//
 Vertex Vertex::Dehomogenize(Vertex& v)
{
	 
	dehomogenizator = _w ;
	v.SetX(v.GetX() / dehomogenizator);
	v.SetY(v.GetY() / dehomogenizator);
	v.SetZ(v.GetZ() / dehomogenizator);
	v.SetW(v.GetW() / dehomogenizator);

	return v;

}


