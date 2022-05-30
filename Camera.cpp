#include "Camera.h"

Camera::Camera(void)
{
	_x = 0;
	_y = 0;
	_z = 0;
	_p = Vertex(0,0,-60);
}


//INITALIZER//
Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_x = xRotation;
	_y = yRotation;
	_z = zRotation;
	_p = position;
}


// Destructor//
Camera::~Camera(void)
{
}

//ACCESORS AND MUTATORS//
float Camera::GetXRotation(void) const
{
	return _x;
}

void Camera::SetXRotation(float x)
{
	_x = x;
}

float Camera::GetYRotation(void) const
{
	return _y;
}

void Camera::SetYRotation(float y)
{
	_y = y;
}

float Camera::GetZRotation(void) const
{
	return _z;
}

void Camera::SetZRotation(float z)
{
	_z = z;
}

Vertex Camera::GetPosition(void) const
{
	return _p;
}

void Camera::SetPosition(Vertex p)
{
	_p = p;
}

//GENERATING CAMERA MATRIX//
Matrix Camera::GetCameraMatrix(void) const
{


	Matrix Final;
	Matrix location{1 , 0 , 0 , -(_p.GetX()),
					0 , 1 , 0 , -(_p.GetY()),
					0 , 0 , 1 , -(_p.GetZ()),
					0 , 0 , 0 ,     1    };
	Matrix xRot	  { 1 ,     0   ,   0    , 0,
					0 ,  cos(_x), sin(_x), 0,
					0 , -sin(_x), cos(_x), 0,
					0 ,     0   ,   0    , 1 };

	Matrix yRot	  { cos(_y), 0 , -sin(_y), 0,
					0	   , 1 ,    0    , 0,
					sin(_y), 0 , cos(_y) , 0,
					0	   , 0 ,    0    , 1 };

	Matrix zRot	  { cos(_z) , sin(_z), 0 , 0,
					-sin(_z), cos(_z), 0 , 0,
					    0   ,    0   , 1 , 0,
					    0   ,    0   , 0 , 1 };

	 Final =  xRot * yRot * zRot * location;

	return Final;
}