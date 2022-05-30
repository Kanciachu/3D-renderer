#pragma once

// Class representing a 3D vertex (i.e a point in 3 dimensional space)

class Vertex
{
public:
	Vertex(void);
	Vertex(float x, float y, float z);
	Vertex(const Vertex& v);
	Vertex(Vertex&& other);

	~Vertex(void);

	float GetX(void) const;
	void SetX(float x);
	float GetY(void) const;
	void SetY(float y);
	float GetZ(void) const;
	void SetZ(float y);
	float GetW(void) const;
	void SetW(float w);

	Vertex& operator= (const Vertex& rhs);
	Vertex& operator= (Vertex&& rhs);
	Vertex Dehomogenize(Vertex& v);

private:
	float _x;
	float _y;
	float _z;
	float _w;

	void Init(float x, float y, float z);
	void Copy(const Vertex& v);
	float dehomogenizator;
};

