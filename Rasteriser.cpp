#include "Rasteriser.h"


Rasteriser app;

bool Rasteriser::Initialise()
{

	if (!MD2Loader::LoadModel("cube.md2", _model,
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}

	cameraa = camera.GetCameraMatrix();
	_x = 0.0f;
	_y = 1.0f;
	_time = 0;

	return true;
}

void Rasteriser::Update(const Bitmap& bitmap)
{
	_x += 1.0f;
	_y += 0.01f;
	_time += 1;
	float d = 1.0f;
	int height = bitmap.GetHeight();
	int width = bitmap.GetWidth();
	float aspectRatio = (float)width/ (float)height;

	//PRESENTATION LOOP//

	if (_time < 60)
	{
		if (move == 0)
		{
			move = 1;
		}
		CurrentModelTransformation = GenerateScalingMatrix(move, move, move);
		move += 0.01f;
		s = { "wireframe & scaling" };
	}
	else if (_time < 120)
	{
		CurrentModelTransformation = GenerateScalingMatrix(move, move, move);
		move -= 0.01f;
		s = { "wireframe & scaling" };
	}
	else if (_time < 210)
	{
		 CurrentModelTransformation = GenerateTranslationMatrix(move, 1, 1);
		 move += 0.3f;
		 s = { "wireframe & translation X" };
	}
	else if (_time < 330)
	{
		 CurrentModelTransformation = GenerateTranslationMatrix(move, 1, 1);
		 move -= 0.3f;
		 s = { "wireframe & translation X" };
	}
	else if (_time < 390)
	{
		 CurrentModelTransformation = GenerateTranslationMatrix(move, 1, 1);
		 move += 0.3f;
		 s = { "wireframe & translation X" };
	}
	else if (_time < 450)
	{
		 CurrentModelTransformation = GenerateTranslationMatrix(1, move, 1);
		 move -= 0.3f;
		 s = { "wireframe & translation Y" };
	}
	else if (_time < 510)
	{
		 CurrentModelTransformation = GenerateTranslationMatrix(1, move, 1);
		 move += 0.3f;
		 s = { "wireframe & translation Y" };
	}
	else if (_time < 570)
	{
		CurrentModelTransformation = GenerateTranslationMatrix(1, 1, move);
		move -= 0.3f;
		s = { "wireframe & translation Z" };
    }
	else if (_time < 630)
	{
		CurrentModelTransformation = GenerateTranslationMatrix(1, 1, move);
		move += 0.3f;
		s = { "wireframe & translation Z" };

	}
	else if (_time < 750)
	{
		CurrentModelTransformation = GenerateRotationMatrix(_x, 'y');
		s = { "wireframe & Rotation     " };
	}
	else
	{ 
		 _time = 0;
		 move = 0;
	}
	PerspectiveMatrix = GeneratePerspectiveMatrix(d, aspectRatio);
	ViewMatrix = GenerateViewMatrix(d, width, height);

}

void Rasteriser::Render(const Bitmap& bitmap)
{
	bitmap.Clear(RGB(255, 255, 255));
	TextOutA(bitmap.GetDC(), 100, 00,s, 25);
	_model.ApplyTransformToLocalVertices(CurrentModelTransformation);
	_model.ApplyTransformToTransformedVertices(cameraa);
	_model.ApplyTransformToTransformedVertices(PerspectiveMatrix);
	_model.DehomogenizeTransformedVertices();
	_model.ApplyTransformToTransformedVertices(ViewMatrix);
	DrawWireFrame(bitmap);
}

Matrix Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	//GENERATING PERSPECTIVE MATRIX//

	Matrix PerspectiveMatrix{ d / aspectRatio, 0.0f , 0.0f , 0.0f,
									     0.0f,  d   , 0.0f , 0.0f,
                                         0.0f, 0.0f ,  d   , 0.0f,
								         0.0f, 0.0f , 1.0f , 0.0f };
	return PerspectiveMatrix ;
}

Matrix Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	//GENERATING VIEW MATRIX//

	Matrix ViewMatrix{ (float)width / 2.0f,				 0.0f      ,  0.0f  ,  (float)width / 2.0f ,
									  0.0f,  (float)height / 2.0f  ,  0.0f  ,  (float)height / 2.0f,
									  0.0f,				 0.0f      , d/2.0f ,        d/2.0f        ,
								      0.0f,				 0.0f      ,  0.0f  ,          1.0f      };
	return ViewMatrix;
}

void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{

	HDC hdc = bitmap.GetDC();
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(0, 0, 255));

	//LOOPS THRU POLYGONS AND DRWAS LINES BETWEEN VERTICES//

	for(Polygon3D polygon : _model.GetPolygons())
	{	

		vector<Vertex> _vertices = _model.GetTransformedVertices();

		MoveToEx(hdc, (int)_vertices[polygon.GetIndex(0)].GetX(), (int)_vertices[polygon.GetIndex(0)].GetY(), NULL);
		LineTo(hdc, (int)_vertices[polygon.GetIndex(1)].GetX(), (int)_vertices[polygon.GetIndex(1)].GetY());
		LineTo(hdc, (int)_vertices[polygon.GetIndex(2)].GetX(), (int)_vertices[polygon.GetIndex(2)].GetY());
		LineTo(hdc, (int)_vertices[polygon.GetIndex(0)].GetX(), (int)_vertices[polygon.GetIndex(0)].GetY());
	}
}

Matrix Rasteriser::GenerateTranslationMatrix(float x, float y, float z)
{
	//GENERATING TRANSLATION MATRIX//

	Matrix translation;
	translation = { 1,0,0,x,
				   0,1,0,y,
				   0,0,1,z,
				   0,0,0,1, };

	return translation;
}
Matrix Rasteriser::GenerateScalingMatrix(float x, float y, float z)
{
	//GENERATING SCALING MATRIX//

	Matrix scaling;
	scaling = { x,0,0,0,
			    0,y,0,0,
			    0,0,z,0,
			    0,0,0,1 };

	return scaling;

}
Matrix Rasteriser::GenerateRotationMatrix(float x, char axis)
{

	//GENERATING ROTATION MATRIX AROUND SPECIFIED MATRIX DEFAULT Z//

	Matrix rotation;
	float radians = (float)(x * 3.14f / 180.0f);

	if (axis == 'x')
	{
		rotation = { 1,		 0	   ,       0       ,0,
					 0,cosf(radians),-sinf(radians),0,
					 0,sinf(radians), cosf(radians),0,
					 0,      0      ,       0      ,1 };

		return rotation;
	}
	else if(axis == 'y')
	{
		rotation = { cosf(radians),0,sinf(radians),0,
					      0       ,1,      0      ,0,
					-sinf(radians),0,cosf(radians),0,
						  0       ,0,       0     ,1 };
	
		return rotation;
	}
	else
	{
		rotation = { cosf(radians),-sinf(radians),0,0,
					 sinf(radians), cosf(radians),0,0,
					       0      ,        0     ,1,0,
					       0      ,        0     ,0,1 };

		return rotation;
	}
}