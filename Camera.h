#pragma once
#include "Vertex.h"
#include "Matrix.h"
#include <cmath>
class Camera
{
public:

	Camera(void);
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	~Camera(void);

	float GetXRotation(void) const;
	void SetXRotation(float x);
	float GetYRotation(void) const;
	void SetYRotation(float y);
	float GetZRotation(void) const;
	void SetZRotation(float z);
	Vertex GetPosition(void) const;
	void SetPosition(Vertex p);
	Matrix GetCameraMatrix(void) const;

private:
	float _x;
	float _y;
	float _z;
	Vertex _p;
};

