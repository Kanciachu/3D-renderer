#pragma once
#include "Model.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Framework.h"
#include "MD2Loader.h"
#include "Polygon3D.h"
#include "Camera.h"
#include "Bitmap.h"

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);

private:
	void    DrawWireFrame(const Bitmap& bitmap);
	Matrix	GeneratePerspectiveMatrix(float d, float aspectRatio);
	Matrix  GenerateViewMatrix(float d, int width, int height);
	Matrix  GenerateTranslationMatrix(float x, float y, float z);
	Matrix  GenerateScalingMatrix(float x, float y, float z);
	Matrix  GenerateRotationMatrix(float x, char axis);
	float  _x;
	float  _y;
	int _time;

	Matrix CurrentModelTransformation;
	Matrix PerspectiveMatrix;
	Matrix ViewMatrix;
	Matrix cameraa ;
	Camera camera;
	Model _model;
	Matrix _PerspectiveMatrix;
	bool flag = false;
	float move = 0;
	LPCSTR s;
};

